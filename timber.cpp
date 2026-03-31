#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

/* Branch Stuff Start */
void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];
/* Branch Stuff End */

struct Particle {
    Sprite sprite;
    Vector2f velocity;
    float lifetime;
};

int main() {
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Timber!!!");
	
	bool isPaused = true;
	
	int score = 0;
	
	Text pauseText;
	Text scoreText;
	FloatRect textRect = pauseText.getLocalBounds();
	pauseText.setOrigin(((textRect.left+textRect.width)/2.0f), ((textRect.top+textRect.top)/2.0f));
	
	Font font;
	font.loadFromFile("Timber_/fonts/KOMIKAP_.ttf");
	
	/* Sounds */
	SoundBuffer chopBuffer, deathBuffer, ootBuffer;
	Sound chop, death, outOfTime;
	
	chopBuffer.loadFromFile("Timber_/sound/chop.wav");
	deathBuffer.loadFromFile("Timber_/sound/death.wav");
	ootBuffer.loadFromFile("Timber_/sound/out_of_time.wav");
	
	chop.setBuffer(chopBuffer);
	death.setBuffer(deathBuffer);
	outOfTime.setBuffer(ootBuffer);
	
	/* Time Bar */
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1450/2), 950);
	
	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
	
	/* Score Text */
	scoreText.setFont(font);
	scoreText.setString("Score = 0");
	scoreText.setCharacterSize(75);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(20, 20);
	
	/* Pause Text */
	pauseText.setFont(font);
	pauseText.setString("Press Enter to Start!!");
	pauseText.setCharacterSize(100);
	pauseText.setFillColor(Color::White);
	pauseText.setPosition((700/2.0f), (900/2.0f));
	
	
	/* Loading Textures */
	Texture textureBg, textureTree, textureBee, textureCloud1, textureCloud2, textureCloud3, textureBranch, texturePlayer, textureRIP, textureAxe, textureLog, textureParticle;
	
	textureBg.loadFromFile("Timber_/graphics/background.png");
	textureTree.loadFromFile("Timber_/graphics/tree.png");
	textureBee.loadFromFile("Timber_/graphics/bee.png");
	textureCloud1.loadFromFile("Timber_/graphics/cloud.png");
	textureCloud2.loadFromFile("Timber_/graphics/cloud.png");
	textureCloud3.loadFromFile("Timber_/graphics/cloud.png");
	textureBranch.loadFromFile("Timber_/graphics/branch.png");
	texturePlayer.loadFromFile("Timber_/graphics/player.png");
	textureRIP.loadFromFile("Timber_/graphics/rip.png");
	textureAxe.loadFromFile("Timber_/graphics/axe.png");
	textureLog.loadFromFile("Timber_/graphics/log.png");
	textureParticle.loadFromFile("Timber_/graphics/log.png");
	
	vector<Particle> particles;
	
	Sprite spriteBg, spriteTree, spriteBee, spriteCloud1, spriteCloud2, spriteCloud3, spritePlayer, spriteRIP, spriteAxe, spriteLog;
	
	/* Setting Bg */
        spriteBg.setTexture(textureBg);
        spriteBg.setPosition(0, 0);
        
        /* Setting Tree */
        spriteTree.setTexture(textureTree);
        spriteTree.setPosition(840, -50);
        
        /* Setting Bee */
        spriteBee.setTexture(textureBee);
        spriteBee.setPosition(0, 730);
        
        /* Setting Clouds */
        spriteCloud1.setTexture(textureCloud1);
        spriteCloud1.setPosition(0, 50);
        spriteCloud2.setTexture(textureCloud2);
        spriteCloud2.setPosition(0, 150);
        spriteCloud3.setTexture(textureCloud3);
        spriteCloud3.setPosition(0, 250);
        
        /* Setting Branches */
        for(int i=0; i<NUM_BRANCHES; i++) {
        	branches[i].setTexture(textureBranch);
        	branches[i].setPosition(-2000, -2000);
        	branches[i].setOrigin(220, 20);
        }
        
        /* Setting Player */
        spritePlayer.setTexture(texturePlayer);
        spritePlayer.setPosition(580, 680);
        side playerSide = side::LEFT;
        
        /* Setting RIP */
        spriteRIP.setTexture(textureRIP);
        spriteRIP.setPosition(600, 860);
        
        /* Setting Axe */
        spriteAxe.setTexture(textureAxe);
        spriteAxe.setPosition(700, 800);
        const float AXE_POSITION_LEFT = 700;
        const float AXE_POSITION_RIGHT = 975;
        
        /* Setting Log (When Player Cuts the tree) */
        spriteLog.setTexture(textureLog);
        spriteLog.setPosition(840, 750);
        bool logActive = false;
        float logSpeedX = 1000;
        float logSpeedY = -1500;
        
        /* Scaling Components */
        spriteCloud1.setScale(0.5f, 0.5f);
        spriteCloud2.setScale(0.5f, 0.5f);
        spriteCloud3.setScale(0.5f, 0.5f);
        
        spriteTree.setScale(0.5f, 1.0f);
        spriteLog.setScale(0.5f, 1.0f);
        
        /* Boolean Variables */
        bool beeActive = false;
        bool cloud1Active = false;
        bool cloud2Active = false;
        bool cloud3Active = false;
        
        /* Speeds */
        float beeSpeed = 0.0f;
        float cloud1Speed = 0.0f;
        float cloud2Speed = 0.0f;
        float cloud3Speed = 0.0f;
        
        /* Accept Player input */
        bool acceptInput = false;
        
        /* Cut log 4-5 Components */
        bool specialLogActive = false;
        int specialLogHealth = 0;
        const int SPECIAL_LOG_MAX_HEALTH = 5;
        
        Sprite spriteSpecialLog;
        Texture textureSpecialLog;

	float specialLogGlowTimer = 0.0f;
	bool glowUp = true;
	
	/* Setting Special Log */
	textureSpecialLog.loadFromFile("Timber_/graphics/log.png");
	spriteSpecialLog.setTexture(textureSpecialLog);
	spriteSpecialLog.setPosition(-2000, -2000);
	spriteSpecialLog.setScale(0.6f, 1.2f);
        
        /* Misc */
        Time dt;
        Clock clock;
        
        /* --------- Screen Shake --------- */
	float shakeTime = 0.0f;
	float shakeDuration = 0.2f;
	float shakeMagnitude = 20.0f;
        
        View view(FloatRect(0,0,1920,1080));
       

	window.setView(view);
      
	while(window.isOpen()) {
		/* Restart Clock every single time */
		dt = clock.restart();
		
		float gameDt = dt.asSeconds();
		
	        /* ------------------ Event Polling Start ------------------
	        		(So that game doesn't quit itself)  	    */
	        Event event;
                while (window.pollEvent(event)) {
                  if(event.type == Event::KeyReleased && !isPaused) {
                  	acceptInput = true;
                  	spriteAxe.setPosition(5000, spriteAxe.getPosition().y);
                  }
                
                  if(event.type == event.Closed) {
                    window.close();
                  }
                  
                  if(event.type == event.KeyPressed && event.key.code == Keyboard::Return) {
			isPaused = !isPaused;
			score = 0;
			timeRemaining = 6;
			
			for(int i = 1; i < NUM_BRANCHES; i++) {
				branchPositions[i] = side::NONE;
			}
			
			spriteRIP.setPosition(675, 2000);
			spritePlayer.setPosition(580, 680);
			
			acceptInput = true;
		}
		  
		/* ------------------ Player Right-Left Accept Input ------------------ */
		if (acceptInput) {
		    if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Left)) {
			bool isRight = Keyboard::isKeyPressed(Keyboard::Right);
			
			playerSide = isRight ? side::RIGHT : side::LEFT;
			spriteAxe.setPosition(isRight ? AXE_POSITION_RIGHT : AXE_POSITION_LEFT, spriteAxe.getPosition().y);
			spritePlayer.setPosition(isRight ? 1110 : 580, 690);

			if (specialLogActive) {
				
				/* Special Log Particles */
				Color pColor = (specialLogHealth <= 2) ? Color::Red : Color::Yellow;
				for(int i=0; i<15; i++){
				    Particle p;
				    p.sprite.setTexture(textureParticle);
				    p.sprite.setTextureRect(IntRect(0,0,15,15));
				    p.sprite.setColor(pColor);
				    p.sprite.setPosition(840, 750);
				    p.velocity = Vector2f((rand()%600)-300, (rand()%600)-300);
				    p.lifetime = 0.8f;
				    particles.push_back(p);
				}

				for(int i=0; i<8; i++){
				    Particle p;
				    p.sprite.setTexture(textureParticle);
				    p.sprite.setTextureRect(IntRect(0,0,12,12));
				    p.sprite.setColor(Color(139, 69, 19));
				    p.sprite.setPosition(840, 750);
				    p.velocity = Vector2f((rand()%400)-200, (rand()%400)-200);
				    p.lifetime = 0.5f;
				    particles.push_back(p);
				}
			
			    specialLogHealth--;
			    shakeTime = shakeDuration;
			    chop.play();

			    if (specialLogHealth <= 0) {
				specialLogActive = false;
				spriteSpecialLog.setPosition(-2000, -2000);
				score += 10;
				shakeTime = 0;
			    }
			} else {
			    score++;
			    timeRemaining += (2.0f / score) + .15f;
			    updateBranches(score);
			    
			    spriteLog.setPosition(840, 750); 
			    logSpeedX = isRight ? -5000 : 5000; 
			    logActive = true; 
			    
			    chop.play();
			}
			
			acceptInput = false;
		    }
		}
		  
		  if((Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::Left)) ) {
			score++;
		  } 
		  
		/* Cheat code for speed */
                if(Keyboard::isKeyPressed(Keyboard::Space)) {
			gameDt *= 18.0f;
		  }
                }
                
                /* Window Shake */
		if (shakeTime > 0) {
		    shakeTime -= dt.asSeconds();

		    float offsetX = (rand() % (int)(shakeMagnitude * 2)) - shakeMagnitude;
		    float offsetY = (rand() % (int)(shakeMagnitude * 2)) - shakeMagnitude;

		    View shakenView = view;
		    shakenView.move(offsetX, offsetY);
		    window.setView(shakenView);
		} else {
		    shakeTime = 0; 
		    window.setView(view);
		}
                
                /* Updating Branches */
                if(event.type == event.KeyPressed && event.key.code == Keyboard::A) {
      			updateBranches(1);
      			updateBranches(2);
      			updateBranches(3);
      			updateBranches(4);
      			updateBranches(5);
                }
                
                /* ------------------ Event Polling End ------------------ */
                
 		if(Keyboard::isKeyPressed(Keyboard::Escape)){
 			window.close();
 		}
		
		/* Pause Mechanism with all moving objects */		
		if(!isPaused) {
			/* ----------------- Particle System for Special Log -----------------*/
			for (int i = 0; i < (int)particles.size(); ) {
			    particles[i].lifetime -= gameDt;
			    particles[i].sprite.move(particles[i].velocity * gameDt);
			    if (particles[i].lifetime <= 0) particles.erase(particles.begin() + i);
			    else i++;
			}
		
			/* ------------------ Time Bar Mechanism ------------------ */
			timeRemaining -= gameDt;
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
			
			if(timeRemaining <= 0.0f) {
				isPaused = true;
				pauseText.setString("Out of Time!");
				
				FloatRect textRect = pauseText.getLocalBounds();
				pauseText.setOrigin(
					(textRect.left + textRect.width/2.0f), 
					(textRect.top + textRect.height/2.0f)
				);
				pauseText.setPosition(1900/2.0f, 900/2.0f);
				
				outOfTime.play();
			} 
			
			/* else if(isPaused = true && timeRemaining <= 0.0f) {
				isPaused = !isPaused;
				pauseText.setString("Press Enter to Start!!");
				score = 0;
				timeRemaining = 6;
			} */
			
			/* ------------------ Score Mechanism ------------------ */
			stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());
			
			/* ------------------ Branch Mechanism ------------------ */
			for(int i=0; i<NUM_BRANCHES; i++) {
				float height = i * 150;
				
				if(branchPositions[i] == side::LEFT) {
					branches[i].setPosition(620, height);
					branches[i].setRotation(180);
				} else if(branchPositions[i] == side::RIGHT) {
					branches[i].setPosition(1210, height);
					branches[i].setRotation(0);
				} else {
					branches[i].setPosition(3000, height);
				}
			}
			
			/* --------- Spawn Special Log Randomly --------- */
			if (!specialLogActive) {
			    if ((rand() % 1000) == 1) { 
				specialLogActive = true;
				specialLogHealth = SPECIAL_LOG_MAX_HEALTH;
				
				spriteSpecialLog.setPosition(810, 720); 
				spriteSpecialLog.setColor(Color::White);
			    }
			}
			
			/* --------- Glow Animation --------- */
			if (specialLogActive) {
			    if (glowUp) {
				specialLogGlowTimer += 200 * gameDt;
				if (specialLogGlowTimer >= 255) {
				    specialLogGlowTimer = 255;
				    glowUp = false;
				}
			    } else {
				specialLogGlowTimer -= 200 * gameDt;
				if (specialLogGlowTimer <= 100) {
				    specialLogGlowTimer = 100;
				    glowUp = true;
				}
			    }

			    spriteSpecialLog.setColor(Color(255, 255, 255, (Uint8)specialLogGlowTimer));
			}
			
			
			/* ------------------ Log Flying Mechanism ------------------ */
			if(logActive) {
				spriteLog.setPosition(
					spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
					spriteLog.getPosition().y + (logSpeedY * dt.asSeconds())
				);
				
				if(spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000) {
					logActive = false;
					spriteLog.setPosition(840, 750);
				}
			}
			
			/* ------------------ Player Death Mechanism ------------------ */
			if(branchPositions[5] == playerSide) {
				isPaused = true;
				acceptInput = false;
				
				spriteRIP.setPosition(580, 680);
				
				spritePlayer.setPosition(2000, 600);
				
				pauseText.setString("SQUISHED!!!");
				
				FloatRect textRect = pauseText.getLocalBounds();
				
				pauseText.setOrigin(
					textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f
				);
				
				pauseText.setPosition(1920 / 2.0f, 1080 / 2.0f);
				
				death.play();
			}
		
			/* ------------------ Moving Bee ------------------ */
			if(!beeActive) {
				srand((int)time(0) * 10);
				beeSpeed = (rand() % 200) + 300;
				// cout << "beeSpeed is = " << beeSpeed << endl;
				
				float height = (rand() % 500) + 300;
				// cout << "beeHeight is = " << height << endl;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			} else {
				spriteBee.setPosition(
					spriteBee.getPosition().x - (beeSpeed * gameDt),
					spriteBee.getPosition().y				
				);
				if(spriteBee.getPosition().x < -100) {
					beeActive = false;
				}
			}
			
			/* ------------------ Moving Clouds ------------------ */
			if (!cloud1Active) {
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);
				
				srand((int)time(0) * 10);
				float height = (rand() % 50);
				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;
			} else {
				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x + (cloud1Speed * gameDt),
					spriteCloud1.getPosition().y
				);
				if(spriteCloud1.getPosition().x > 1920) {
					cloud1Active = false;
				}
			}
			
			if (!cloud2Active) {
				srand((int)time(0) * 10);
				cloud2Speed = (rand() % 250) + 50;
				
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;
			} else {
				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x + (cloud2Speed * gameDt),
					spriteCloud2.getPosition().y
				);
				if(spriteCloud2.getPosition().x > 1920) {
					cloud2Active = false;
				}
			}
			
			if (!cloud3Active) {
				srand((int)time(0) * 10);
				cloud3Speed = (rand() % 300) + 100;
				
				srand((int)time(0) * 10);
				float height = (rand() % 250);
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			} else {
				spriteCloud3.setPosition(
					spriteCloud3.getPosition().x + (cloud3Speed * gameDt),
					spriteCloud3.getPosition().y
				);
				if(spriteCloud3.getPosition().x > 1920) {
					cloud3Active = false;
				}
			}
		}
 	  
 		window.clear();
 		
 		/* Drawing Sprites on Window */
 		window.draw(spriteBg);
 		window.draw(spriteTree);
 		window.draw(spriteBee);
 		window.draw(spriteCloud1);
 		window.draw(spriteCloud2);
 		window.draw(spriteCloud3);
 		for(int i=0; i<NUM_BRANCHES; i++) {
 			window.draw(branches[i]);
 		}
 		window.draw(scoreText);
 		window.draw(timeBar);
 		

 		
 		
 		
 		window.draw(spritePlayer);
 		
 		window.draw(spriteLog);
 		
 		if (specialLogActive) {
    			window.draw(spriteSpecialLog);
		}
 		
 		window.draw(spriteRIP);
 		window.draw(spriteAxe);
 		
 		if(isPaused) {
			window.draw(pauseText);
		}
		for (auto& p : particles) {
		    window.draw(p.sprite);
		}

 		
 		window.display();
	}
	return 0;
}

void updateBranches(int seed) {
	for (int j = NUM_BRANCHES-1; j > 0; j--) {
		branchPositions[j] = branchPositions[j - 1];
	}
	srand((int)time(0)+seed);
	int r = (rand() % 5);
	
	switch(r) {
		case 0:
			branchPositions[0] = side::LEFT;
			break;
		case 1:
			branchPositions[0] = side::RIGHT;
			break;
		default:
			branchPositions[0] = side::NONE;
			break;
	}
}
