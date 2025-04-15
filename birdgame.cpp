#include<iostream>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <time.h>
#include <cassert>
using namespace std;

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20

#define GAP_SIZE 7
#define PIPE_DIF 45
#define PIPE_SPEED 2
#define PIPE_WIDTH 3

#define GAP_WALL_BIRD 2
#define BIRD_WIDTH 6
#define BIRD_HEIGHT 2
#define BIRD_JUMP_HEIGHT 3
#define GRAVITY 1

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int pipePos[2];
int gapPos[2];
bool pipeFlag[2];
char bird[BIRD_HEIGHT][BIRD_WIDTH] = { '/','-','-','O','\\',' ',
					'|','_','_','_',' ','>' };
int birdPos = 6;
int score = 0;
int highscore = -1;

// Color definitions
enum Color {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    YELLOW = 6,
    WHITE = 7,
    GRAY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_YELLOW = 14,
    BRIGHT_WHITE = 15
};

void setColor(Color text, Color background = BLACK) {
    SetConsoleTextAttribute(console, (background << 4) | text);
}

void resetColor() {
    setColor(WHITE, BLACK);
}

void gotoxy(int col, int row) {
    CursorPosition.X = col;
    CursorPosition.Y = row;
    SetConsoleCursorPosition(console, CursorPosition);
}

void drawBorder() {
    setColor(LIGHT_CYAN);
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        gotoxy(i, 0); cout << "=";
        gotoxy(i, SCREEN_HEIGHT-1); cout << "=";
    }

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(0, i); cout << "|";
        gotoxy(SCREEN_WIDTH-1, i); cout << "|";
    }
    
    setColor(GRAY);
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(WIN_WIDTH, i); cout << "|";
    }
    resetColor();
}

void genPipe(int ind) {
    gapPos[ind] = 3 + rand() % 14;
}

void drawPipe(int ind) {
    if (pipeFlag[ind] == true) {
        setColor(LIGHT_GREEN);
        for (int i = 0; i < gapPos[ind]; i++) {
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "###";
        }
        for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 2; i++) {
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "###";
        }
        resetColor();
    }
}

void erasePipe(int ind) {
    if (pipeFlag[ind] == true) {
        for (int i = 1; i < gapPos[ind]+1; i++) {
            gotoxy(WIN_WIDTH - pipePos[ind], i); cout << "   ";
        }
        for (int i = 1+gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) {
            gotoxy(WIN_WIDTH - pipePos[ind], i); cout << "   ";
        }
    }
}

void drawBird() {
    setColor(LIGHT_YELLOW);
    for (int i = 0; i < BIRD_HEIGHT; i++) {
        for (int j = 0; j < BIRD_WIDTH; j++) {
            int row = i + birdPos;
            int col = j + GAP_WALL_BIRD;
            if (col >= 0 && row >= 0 && col < SCREEN_WIDTH && row < SCREEN_HEIGHT) {
                gotoxy(col, row); cout << bird[i][j];
            }
        }
    }
    resetColor();
}

void eraseBird() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            gotoxy(j + 2, i + birdPos); cout << " ";
        }
    }
}

bool collision() {
    if (birdPos <= 0) {
        return 1;
    }
    if (birdPos + BIRD_HEIGHT - 1 >= SCREEN_HEIGHT - 1) {
        return 1;
    }
    if (birdPos + BIRD_HEIGHT - 1 <= gapPos[0] && GAP_WALL_BIRD + BIRD_WIDTH >= WIN_WIDTH-pipePos[0]) {
        return 1;
    }
    if (birdPos + BIRD_HEIGHT - 1 >= gapPos[0]+GAP_SIZE && GAP_WALL_BIRD + BIRD_WIDTH >= WIN_WIDTH - pipePos[0]) {
        return 1;
    }
    if (pipePos[0] >= WIN_WIDTH-BIRD_WIDTH) {
        if (birdPos <= gapPos[0] || birdPos + BIRD_HEIGHT - 1 >= gapPos[0] + GAP_SIZE) {
            return 1;
        }
    }
    return 0;
}

int gameover() {
    setColor(LIGHT_RED);
    gotoxy(WIN_WIDTH + 5, 13); cout << "Game Over!";
    gotoxy(WIN_WIDTH + 4, 14); cout << "Press 1 to Restart";
    gotoxy(WIN_WIDTH + 4, 15); cout << "Press 2 to Main Menu";
    resetColor();
    
    while (1) {
        if (_kbhit()) {
            char k = _getch();
            if (k == '1') return 1; // Restart
            if (k == '2') return 2; // Main Menu
        }
    }
}

void updateScore() {
    highscore = max(highscore, score);
    setColor(LIGHT_YELLOW);
    gotoxy(WIN_WIDTH + 7, 5); cout << "Score: " << score << endl;
    gotoxy(WIN_WIDTH + 8, 10); cout << "Best: " << highscore;
    resetColor();
}

char AI() {
    if (birdPos + BIRD_HEIGHT - 1 <= gapPos[0]) {
        return 1;
    }
    if (birdPos + BIRD_HEIGHT - 1 >= gapPos[0] + GAP_SIZE) {
        if (birdPos - BIRD_JUMP_HEIGHT > gapPos[0]) {
            return 32;
        }
    }
    return 0;
}

void ClearTerminalText() {
    gotoxy(SCREEN_WIDTH, SCREEN_HEIGHT); cout << "   " << endl;
    gotoxy(10, 3); cout << "                                               " << endl;
    gotoxy(10, 4); cout << "                                               " << endl;
    gotoxy(10, 5); cout << "                                               " << endl;
    gotoxy(10, 6); cout << "                                               " << endl;
    gotoxy(10, 7); cout << "                                               " << endl;

    gotoxy(10, 9); cout << "                             " << endl;
    gotoxy(10, 10); cout << "                             " << endl;
    gotoxy(10, 11); cout << "                             " << endl;
    gotoxy(10, 12); cout << "                             " << endl;

    gotoxy(10, 14); cout << "                    " << endl;
    gotoxy(10, 15); cout << "                    "  << endl;
    gotoxy(10, 16); cout << "                    "  << endl;
    gotoxy(10, 17); cout << "                    "  << endl;

    gotoxy(10, 19); cout << "                           " << endl;
    gotoxy(10, 20); cout << "                           " << endl;
    gotoxy(10, 21); cout << "                           " << endl;
    gotoxy(10, 22); cout << "                           " << endl;
}

void InitialiseTerminal() {
    system("cls");
    score = 0;

    drawBorder();
    birdPos = 6;
    drawBird();

    pipeFlag[0] = 1;
    pipeFlag[1] = 0;
    pipePos[0] = pipePos[1] = 4;
    genPipe(0);
    updateScore();
    drawPipe(0);

    setColor(LIGHT_BLUE);
    gotoxy(WIN_WIDTH + 6, 4); cout << "-----------";
    gotoxy(WIN_WIDTH + 6, 6); cout << "-----------";
    gotoxy(WIN_WIDTH + 6, 9); cout << "-----------";
    gotoxy(WIN_WIDTH + 6, 11); cout << "-----------";
    resetColor();

    // Title with colors
    setColor(LIGHT_MAGENTA);
    gotoxy(10,3); cout <<  " ___ _                       ___ _        _    " << endl;
    gotoxy(10, 4); cout << "| __| |__ _ _ __ _ __ _  _  | _ |_)_ _ __| |   " << endl;
    setColor(LIGHT_CYAN);
    gotoxy(10, 5); cout << "| _|| / _` | '_ \\ '_ \\ || | | _ \\ | '_/ _` |" << endl;
    gotoxy(10, 6); cout << "|_| |_\\__,_| .__/ .__/\\_, | |___/_|_| \\__,_|" << endl;
    gotoxy(10, 7); cout << "           |_|  |_|   |__/                  " << endl;
    
    setColor(LIGHT_YELLOW);
    gotoxy(10, 9); cout <<  "  _     ___ _            _   " << endl;
    gotoxy(10, 10); cout << " / |   / __| |_ __ _ _ _| |_ " << endl;
    gotoxy(10,11); cout <<  " | |_  \\__ \\  _/ _` | '_|  _|" << endl;
    gotoxy(10, 12); cout << " |_(_) |___/\\__\\__,_|_|  \\__|" << endl;

    setColor(LIGHT_GREEN);
    gotoxy(10, 14); cout << "  ___       _   ___ " << endl;
    gotoxy(10, 15); cout << " |_  )     /_\\ |_ _|" << endl;
    gotoxy(10, 16); cout << "  / / _   / _ \\ | | " << endl;
    gotoxy(10, 17); cout << " /___(_) /_/ \\_\\___|" << endl;

    setColor(LIGHT_RED);
    gotoxy(10, 19); cout << "  ____     ___       _ _   " << endl;
    gotoxy(10, 20); cout << " |__ /    / _ \\ _  _(_) |_ " << endl;
    gotoxy(10, 21); cout << " |___(_)  \\__\\\_\\_,_|_|\\__|" << endl;
    resetColor();
}

void play(const bool AIMode) {
    ClearTerminalText();
    eraseBird();
    while (1) {
        birdPos += GRAVITY;

        if (AIMode) {
            char ch = AI();
            if (ch == 32) birdPos -= BIRD_JUMP_HEIGHT;
        }
        else {
            if (_kbhit()) {
                char ch = _getch();
                if (ch == 32) {
                    birdPos -= BIRD_JUMP_HEIGHT;
                }
                if (ch == 27) {
                    break;
                }
            }
        }

        drawBird();
        drawPipe(0);
        drawPipe(1);

        if (collision() == 1) {
            int choice = gameover();
            if (choice == 1) {
                // Restart game
                score = 0;
                birdPos = 6;
                pipeFlag[0] = 1;
                pipeFlag[1] = 0;
                pipePos[0] = pipePos[1] = 4;
                genPipe(0);
                system("cls");
                drawBorder();
                updateScore();
                drawPipe(0);
                ClearTerminalText();
                eraseBird();
                continue;
            }
            else {
                return; // Return to main menu
            }
        }

        if (AIMode) Sleep(50);
        else Sleep(75);

        eraseBird();
        erasePipe(0);
        erasePipe(1);

        if (pipeFlag[0] == 1)
            pipePos[0] += PIPE_SPEED;

        if (pipeFlag[1] == 1)
            pipePos[1] += PIPE_SPEED;

        if (pipePos[0] >= 40 && pipePos[0] < 42) {
            pipeFlag[1] = 1;
            pipePos[1] = 4;
            genPipe(1);
        }
        if (pipePos[0] > 68) {
            score++;
            updateScore();
            pipeFlag[1] = 0;
            pipePos[0] = pipePos[1];
            gapPos[0] = gapPos[1];
        }
    }
}

void hidecursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

int main() {
    hidecursor();
    srand((unsigned)time(NULL));
    InitialiseTerminal();
    do {
        InitialiseTerminal();
        gotoxy(SCREEN_WIDTH, SCREEN_HEIGHT);
        char op = _getche();
        if (op == '1') play(0);
        else if (op == '2') play(1);
        else if (op == '3') break;
    } while (1);

    return 0;
}
