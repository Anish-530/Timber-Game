# 🌲 Timber!!! — SFML Game

> A fast-paced arcade-style lumberjack game built using **SFML (Simple and Fast Multimedia Library)** in **C++**.  
Chop the tree, dodge branches, beat the clock, and chase your highest score! 🪓

---

## 🎮 Gameplay

- Play as a lumberjack cutting down a tree 🌳
- Each chop:
  - Increases score 📈
  - Adds a bit of time ⏳
- Avoid falling branches — one mistake and it's game over 💀
- Watch out for the **🌟 Special Log** for bonus points!
- Difficulty increases as your score rises 🔥

---

## ✨ Features

### 🪓 Core Mechanics
- Left / Right chopping system
- Dynamic branch generation
- Progressive difficulty scaling
- Smooth controls and animations

### ⏳ Time System
- Countdown timer with visual time bar
- Bonus time per successful chop
- Game ends when time runs out

### 💥 Effects & Polish
- Screen shake on heavy hits
- Particle effects for special logs
- Glowing animation effects
- Sound effects:
  - Chop 🪓
  - Death 💀
  - Time-out ⏳

### 🌤 Environment
- Animated clouds ☁️
- Moving bee 🐝 for ambience
- Smooth background rendering

---

## 🧠 Special Mechanics

### 🌟 Special Log
- Spawns randomly
- Requires multiple hits
- Emits particles when damaged
- Rewards **+10 score**

### 💨 Particle System
- Activated on special log hits
- Color changes based on damage
- Auto cleanup using lifetime system

---

## 🎯 Controls

| Key            | Action                  |
|----------------|------------------------|
| ⬅️ Left Arrow  | Chop from left         |
| ➡️ Right Arrow | Chop from right        |
| ⏎ Enter        | Start / Restart game   |
| ␣ Space        | Speed boost (debug)    |
| ⎋ Escape       | Exit game              |

---

## 🛠️ Built With

- **C++**
- **SFML**
  - Graphics
  - Audio
  - Window

---

## 📂 Project Structure

```
Timber_/
│
├── graphics/      # Sprites and textures
├── sound/         # Audio files
├── fonts/         # Game fonts
│
└── timber.cpp       # Main game source code
```

---

## 🚀 How to Run

### 1️⃣ Install SFML  
Make sure SFML is installed and properly linked.

### 2️⃣ Compile

```bash
g++ main.cpp -o timber -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

### 3️⃣ Run

```bash
./timber
```

---

## ⚠️ Notes

- Ensure the `Timber_` assets folder is in the correct relative path
- Missing assets (fonts, textures, sounds) will cause runtime errors
- Uses `rand()` for randomness (can be improved with modern RNG)

---

## 🔮 Future Improvements

- 🎨 Improved UI/UX
- 🧍 Character animations
- 🏆 High score saving system
- 🎵 Background music
- ⚙️ Configurable difficulty
- 📱 Resolution scaling

---

## 📸 Preview

> Add screenshots or GIFs here to showcase gameplay!

```
![Gameplay Screenshot](path/to/screenshot.png)
```

---

## 🙌 Credits

- **Developed by Anish**
- Built with ❤️ using **SFML**

---

## ⭐ Support

If you like this project:

- ⭐ Star this repo  
- 🍴 Fork it  
- 🧠 Contribute ideas  

---

## 🪓 Happy Chopping!
- C++
- SFML (Graphics, Audio, Window)

---

📂 Project Structure

Timber_/
│
├── graphics/      # Sprites and textures
├── sound/         # Audio files
├── fonts/         # Game fonts
│
└── main.cpp       # Main game source code

---

🚀 How to Run

1. Install SFML

Make sure SFML is properly installed on your system.

2. Compile

Example using g++:

g++ main.cpp -o timber -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

3. Run

./timber

---

⚠️ Notes

- Ensure the "Timber_" assets folder is in the correct relative path.
- Fonts, textures, and sounds must be present or the game will not load properly.
- Uses "rand()" for randomness — could be improved with modern RNG.

---

🔮 Future Improvements

- 🎨 Better UI/UX design
- 🧍 Character animations
- 🏆 High score saving system
- 🎵 Background music
- ⚙️ Configurable difficulty
- 📱 Resolution scaling

---

🙌 Credits

- Developed by Anish
- Built with ❤️ using SFML

---

📸 Preview

«Add screenshots or gameplay GIFs here to showcase your game!»

---

⭐ If you like this project...

Give it a star ⭐ on GitHub and share it!

---

Happy chopping! 🌲🪓
