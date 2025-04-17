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

    
## 📝 Features

| Feature        | Description                                  |
|----------------|----------------------------------------------|
| 🎮 Gameplay     | Classic Flappy Bird physics and logic       |
| 🤖 AI Mode      | Basic jump logic to navigate pipes          |
| 🖼️ ASCII Art    | Colored title, bird, and pipes              |
| 🧠 Collision     | Pixel-based, smart detection                |
| 🏆 Scoring      | Tracks high score and current run           |
| 🎨 Colors       | Uses Windows API for terminal colors        |


![Screenshot 2025-04-16 201110](https://github.com/user-attachments/assets/79c50b71-b466-4ada-9949-0ba9d511dcab)

![Screenshot 2025-04-16 201041](https://github.com/user-attachments/assets/cde1c384-580e-49c7-aa03-103fe485a30d)

### List of Functions Used in the Game

| Function Name         | Function Name         | Function Name         |
|-----------------------|-----------------------|-----------------------|
| `setColor()`           | `resetColor()`         | `gotoxy()`             |
| `drawBorder()`         | `genPipe()`            | `drawPipe()`           |
| `erasePipe()`          | `drawBird()`           | `eraseBird()`          |
| `collision()`          | `gameover()`           | `updateScore()`        |
| `AI()`                 | `ClearTerminalText()`  | `InitialiseTerminal()` |
| `play()`               | `hidecursor()`         | `main()`               |


## 🧱 Data Structures Used

| Data Structure        | Variable(s)             | Purpose                                                                 |
|-----------------------|-------------------------|-------------------------------------------------------------------------|
| **Array (1D)**        | `pipePos[2]`            | Holds the X positions of two pipes (obstacles)                         |
|                       | `gapPos[2]`             | Stores the vertical position of the gap between top and bottom pipe    |
|                       | `pipeFlag[2]`           | Flags to indicate whether a pipe is active                             |
| **Array (2D - char)** | `bird[2][6]`            | ASCII representation of the bird sprite                                |
| **Enum**              | `enum Color`            | Holds color codes for colored text in the terminal                     |
| **Primitive types**   | `int`, `char`, `bool`   | For position tracking, game state, input, etc.                         |
| **Struct**            | `COORD CursorPosition`  | Windows-specific structure to set cursor position in the terminal      |

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
