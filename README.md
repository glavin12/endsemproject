# 🐦 Flappy Bird in C++ (Terminal Edition)

A fun, retro-style **Flappy Bird clone** written in pure **C++** for the Windows terminal. Play manually or let a simple AI play for you!

---

## 🎮 How to Play

- **Manual Mode**
  - Press `1` to play yourself.
  - Press `SPACE` to make the bird jump.
  - Avoid crashing into pipes or the screen edges.
  - Press `ESC` anytime during the game to exit.

- **AI Mode**
  - Press `2` to let the AI take control of the bird.
  - The AI tries to stay in the pipe gap intelligently.

- **Quit**
  - Press `3` on the start screen to exit.

    
---Feature | Description
🎮 Gameplay | Classic Flappy Bird physics and logic
🤖 AI Mode | Basic jump logic to navigate pipes
🖼️ ASCII Art | Colored title, bird, and pipes
🧠 Collision | Pixel-based, smart detection
🏆 Scoring | Tracks high score and current run
🎨 Colors | Uses Windows API for terminal colorsments/assets/9a9f77d2-8a3d-4da6-a9ed-16a6c8ef7ea5)
![Screenshot 2025-04-16 201041](https://github.com/user-attachments/assets/cde1c384-580e-49c7-aa03-103fe485a30d)
![Screenshot 2025-04-16 201058](https://github.com/user-attachments/assets/123e70c1-902f-43f4-92ca-d7b7a8db8dea)

## 🖥️ Requirements

- Windows Operating System
- C++ compiler supporting Windows headers (`conio.h`, `windows.h`)
- Command Prompt (cmd) or any terminal that supports console positioning

---

## 🛠️ Build & Run

### Compile using `g++` (MinGW or similar):

```bash
g++ -o FlappyBird main.cpp
FlappyBird.exe
