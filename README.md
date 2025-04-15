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

---

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
