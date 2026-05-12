#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;


bool gameOver;
const int width = 30;
const int height = 15;


int x, y;				// x and y store snake position.
int fruitX, fruitY;			// fruitX and fruitY are food positions.

// Each tail segment needs: x coordinate, y coordinate - tail coordinates

int tailX[100], tailY[100];			// tailX[0], tailX[1], ....... Each slot stores one tail segment's X position. Similarly, tailY[] stores Y position.
int nTail;					// stores how many tail segments currently exist.



/*
Example:

tailX[0] = 5;					first tail segement + its position
tailY[0] = 5;

Means:

first tail segment at (5,5)

tailX[1] = 4;
tailY[1] = 5;

means:

second tail segment at (4,5)			second tail segment + its position

*/



enum Direction {STOP, LEFT, RIGHT, UP, DOWN};		// enum - giving names to numbers. EXAMPLE: 0 - STOP, 1 - LEFT.........
Direction dir;



void setup()
{
    gameOver = false;

    x = width / 2;
    y = height / 2;

    fruitX = rand() % width;			// rand() generates a random number. % gives the remainder. This expression forces the random number to be in the range.
    fruitY = rand() % height;

    dir = STOP;

    nTail = 0;					// at start, the snake has no tail yet. Only a head.
}



/*
If current position equals: snake position

draw: O

Else if current position equals: food position

draw: *

Else: empty space
*/



void draw()
{
    system("cls");

    for(int i = 0; i < width + 2; i++)
        cout << "#";

    cout << endl;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(j == 0)
                cout << "#";

            if(i == y && j == x)
                cout << "O";

            else if(i == fruitY && j == fruitX)
                cout << "*";

            else
            {
                bool print = false;

                for(int k = 0; k < nTail; k++)
                {
                    if(tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }

                if(!print)
                    cout << " ";
            }

            if(j == width - 1)
                cout << "#";
        }

        cout << endl;
    }

    for(int i = 0; i < width + 2; i++)			// BOTTOM WALL.
        cout << "#";

    cout << endl;
}



/*

_kbhit() asks: 'has a key been pressed ?'. Returns true / false.
_getch() gets the pressed key.

*/



void input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'a':
                dir = LEFT;
                break;

            case 'd':
                dir = RIGHT;
                break;

            case 'w':
                dir = UP;
                break;

            case 's':
                dir = DOWN;
                break;

            case 'x':
                gameOver = true;
                break;
        }
    }
}



// MOVEMENT BLOCK
void logic()
{
    int prevX = tailX[0];		// save old position of first tail segment in prevX and prevY
    int prevY = tailY[0];

    int prev2X, prev2Y;			// prev2X, prev2Y = temporary storage for the CURRENT segment before overwriting it

    tailX[0] = x;			// first tail segment copies the head position in x and y
    tailY[0] = y;



    // Tail Following loop
    for(int i = 1; i < nTail; i++)		// go through every tail segment after the first one. ex: nTail = 3, then loop checks i = 1, i = 2
    {
        prev2X = tailX[i];			// saving current segment's old position.
        prev2Y = tailY[i];

        tailX[i] = prevX;			// makes current segment copy previous segment's OLD position.
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir)
    {
        case LEFT:
            x--;				// smaller x means further left on the grid.
            break;

        case RIGHT:				
            x++;
            break;

        case UP:
            y--;				// smaller y means top of the screen.
            break;

        case DOWN:
            y++;
            break;

        default:
            break;
    }

    if(x == fruitX && y == fruitY) 		// if snake position == food position, spawn new food.
    {
        fruitX = rand() % width;
        fruitY = rand() % height;

        nTail++;				// makes the tail grow after the snake eats food.
    }



    // wall collision check
    if(x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;


    // self collision check - we check if the head position equals any tail segment posiiton.
    for(int i = 0; i < nTail; i++)		// this loop checks every tail segment.
    {
        if(tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }
}

int main()
{
    setup();

    while(!gameOver)
    {
        draw();
        input();
        logic();

        Sleep(100);
    }

    cout << "GAME OVER" << endl;

    return 0;
}