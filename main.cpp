#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

// Define constants
const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 24;
const char COP_CAR_CHAR = 'C';
const char CRIMINAL_CHAR = 'X';
const char BULLET_CHAR = '|';

// Define game state variables
int copCarX, copCarY; // Cop car coordinates
int criminalX, criminalY; // Criminal coordinates
int bulletX, bulletY; // Bullet coordinates
int gameSpeed = 500; // Initial game speed in milliseconds

// Function to initialize game
void initializeGame() {
    copCarX = SCREEN_WIDTH / 2;
    copCarY = SCREEN_HEIGHT - 2;
    criminalX = rand() % SCREEN_WIDTH;
    criminalY = SCREEN_HEIGHT / 2; // Initialize criminalY halfway down the screen
    bulletX = -1; // Initialize bullet coordinates to indicate it's not active
    bulletY = -1;
}

// Function to display game screen
void displayGame() {
    system("cls"); // Clear the screen

    // Draw cop car
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        if (i == copCarX) {
            cout << COP_CAR_CHAR;
        } else {
            cout << " ";
        }
    }
    cout << endl;

    // Draw criminal
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        if (i == criminalX && criminalY >= 0 && criminalY < SCREEN_HEIGHT) {
            cout << CRIMINAL_CHAR;
        } else {
            cout << " ";
        }
    }
    cout << endl;

    // Draw bullet if active
    if (bulletY != -1) {
        for (int i = 0; i < SCREEN_WIDTH; i++) {
            if (i == bulletX && bulletY >= 0 && bulletY < SCREEN_HEIGHT) {
                cout << BULLET_CHAR;
            } else {
                cout << " ";                                             
            }
        }
        cout << endl;
    }
}

// Function to update game state
void updateGame() {
    criminalY++;

    // Move bullet upwards if active
    if (bulletY != -1) {
        bulletY--;
        // Check for collision between bullet and criminal
        if (bulletX == criminalX && bulletY == criminalY) {
            cout << "You shot the criminal! Game over." << endl;
            exit(0);
        }
    }

    // Move cop car left or right based on user input
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
            case 'a':
                copCarX = max(0, copCarX - 1);
                break;
            case 'd':
                copCarX = min(SCREEN_WIDTH - 1, copCarX + 1);
                break;
            case ' ': // Shoot if spacebar is pressed
                if (bulletY == -1) { // Only shoot if bullet is not active
                    bulletX = copCarX;
                    bulletY = copCarY - 1;
                }
                break;
        }
    }

    // Check if criminal reached the bottom
    if (criminalY >= SCREEN_HEIGHT) {
        cout << "A criminal reached the bottom! Game over." << endl;
        exit(0);
    }
}

int main() {
    srand(time(0)); // Seed random number generator

    initializeGame();

    while (true) {
        displayGame();
        updateGame();
        // Sleep for game speed
        Sleep(gameSpeed);
    }

    return 0;
}

