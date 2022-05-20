/*
Control:
A - speed X -1 (MAX: +-3)
D - speed X +1
W - speed Y +1
S - speed Y -1
Spacebar - exit
*/

#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>

std::chrono::milliseconds THREAD_WAIT{50};

int keypress = -1;

class cBall {
public:
    int X, Y, vectX, vectY;
};

void gotoxy(short x, short y)
{
    COORD p = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void GetKeyPress()
{
        for (int i = 8; i <= 90; i++)
        {
            int k = GetAsyncKeyState(i);
            if (k != 0) {
                keypress = i;
                break;
            }
        }
}

int main()
{
    unsigned long long lTime, ldTime;
    char cBoard[40][20];
    cBall Bal1;
    Bal1.X = 20;
    Bal1.Y = 10;
    Bal1.vectX = 0;
    Bal1.vectY = 0;
    for (int i = 1; i < 39; i++) {
        for (int j = 1; j < 19; j++) {
            cBoard[i][j] = ' ';
        }
    }
    for (int i = 0; i < 20; i++) {
        cBoard[0][i] = '#';
        cBoard[39][i] = '#';
    }
    for (int i = 0; i < 40; i++) {
        cBoard[i][0] = '#';
        cBoard[i][19] = '#';
    }
    ldTime = GetTickCount64();
m0: 
    lTime = GetTickCount64();
    GetKeyPress();
    
    if (keypress != 32) {
        switch (keypress) {
            case 87:    // pressed W
                if (Bal1.vectY > -3) Bal1.vectY--;
                break;
            case 83:    // pressed S
                if (Bal1.vectY < 3)Bal1.vectY++;
                break;
            case 65:    // pressed A
                if (Bal1.vectX > -3) Bal1.vectX--;
                break;
            case 68:    // pressed D
                if (Bal1.vectX < 3) Bal1.vectX++;
                break;
        }

        Bal1.Y = Bal1.Y + Bal1.vectY;
        if (Bal1.Y < 1) {
            Bal1.Y = 1;
            Bal1.vectY = -Bal1.vectY;
        }
        if (Bal1.Y > 18) {
            Bal1.Y = 18;
            Bal1.vectY = -Bal1.vectY;
        }
        Bal1.X = Bal1.X + Bal1.vectX;
        if (Bal1.X < 1) {
            Bal1.X = 1;
            Bal1.vectX = -Bal1.vectX;
        }
        if (Bal1.X > 38) {
            Bal1.X = 38;
            Bal1.vectX = -Bal1.vectX;
        }

        ldTime = GetTickCount64();
        if ((ldTime - lTime) < 50) {
            std::chrono::milliseconds llWait{ 50 - (ldTime - lTime) };
            std::this_thread::sleep_for(llWait);
        }
        gotoxy(0,0);
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 40; j++) {
                std::cout << cBoard[j][i];
            }
            std::cout << std::endl;
        }
        gotoxy(Bal1.X, Bal1.Y);
        std::cout << "O";
        gotoxy(41, 21);
        std::cout << Bal1.vectX << ' ' << Bal1.vectY << ' ' << std::endl;
        keypress = -1;
        goto m0;
    }
}
