#include <SFML/Graphics.hpp>
using namespace sf;

int main() {
	srand(time(0));	
	
	bool isPaused = true;
	
	Text pauseText;
	FloatRect textRect = pauseText.getLocalBounds();
	pauseText.setOrigin(((textRect.left+textRect.width)/2.0f), ((textRect.top+textRect.top)/2.0f));
	
	
	Font font;
	font.loadFromFile("Timber_/fonts/KOMIKAP_.ttf");
	
	pauseText.setFont(font);
	pauseText.setString("Press Enter to Start!!");
	pauseText.setCharacterSize(75);
	pauseText.setFillColor(Color::White);
	pauseText.setPosition((1920/2.0f), (1080/2.0f));
	
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Playgroud");
	View view(FloatRect(0,0,1920,1080));
	
	window.setView(view);
	
	Texture textureBg;
	
	textureBg.loadFromFile("Timber_/graphics/background.png");
	
	Sprite spriteBg;
	
	CircleShape RedCircle(40.0f), BlueCircle(40.0f);
	
	RedCircle.setFillColor(Color::Red);
	RedCircle.setPosition(500, 100);
	
	BlueCircle.setFillColor(Color::Blue);
	BlueCircle.setPosition(600, 100);
	
	spriteBg.setTexture(textureBg);
	spriteBg.setPosition(0, 0);
	
	float velX = (rand() % 200) + 100.0f;
	//float velY = (rand() % 200 - 100) / 100.0f;
	
	while(window.isOpen()) {
		Event event;
		while(window.pollEvent(event)) {
			if(event.type == event.Closed) {
				window.close();
			}
			
			if(event.type == event.KeyPressed && event.key.code == Keyboard::Enter) {
			isPaused = !isPaused;
			}
		}
		
		Keyboard kb;
		if(kb.isKeyPressed(kb.Escape)) {
			window.close();
		}
		
		if(!isPaused) {
			RedCircle.move(velX, 0.f);
			if(RedCircle.getPosition().x > 1920) {
				float startX = -80.0f;
				float randomY = rand() % 1000;
				
				RedCircle.setPosition(startX, randomY);
				
				velX = (rand() % 500 + 100) / 1000.0f;
			}
		}
		
		window.clear();
		
		window.draw(spriteBg);
		window.draw(RedCircle);
		window.draw(BlueCircle);
		
		if(isPaused) {
			window.draw(pauseText);
		}
		
		window.display();
		
	}
	return 0;
}
