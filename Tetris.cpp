#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
using namespace std;
const int WIDTH = 10;
const int HEIGHT = 20;
int score = 0;
int lines = 0;
string state = "PLAYING";
char Board[HEIGHT][WIDTH];
int x = 4, y = 0;
char O[2][2] = {{'#', '#'},
                {'#', '#'}};
char I[1][4] = {'#', '#', '#', '#'};
char T[2][3] = {{'#', '#', '#'}, {'.', '#', '.'}};
char Z[2][3] = {{'#', '#', '.'},
                {'.', '#', '#'}};
char L[2][3] = {{'#', '.', '.'}, {'#', '#', '#'}};

void show_Menu()
{
    cout << "======= Tetris Game =======" << endl
         << "1-New Game" << "\n2-Help" << "\n3-Exit" << endl;
}

void select_Menu()
{
    int choice;
    do
    {
        show_Menu();
        cin >> choice;
    } while (!(choice == 1 || choice == 2 || choice == 3));

    switch (choice)
    {
    case 1:
    {
        break;
    }
    case 2:
    {
        cout << "controls:\n"
             << "A : Move  Left\n"
             << "D : Move Right\n"
             << "S : Move Down\n"
             << "W : Rotate\n"
             << endl;
        char ch;
        do
        {
            cout << "Press Q to return\n"
                 << endl;
            cin >> ch;
        } while (!(ch == 'Q' || ch == 'q'));
        select_Menu();
        break;
    }
    case 3:
    {
        char ch;
        do
        {
            cout << "Are you sure you want to exit the game? (y/n)" << endl;
            cin >> ch;
        } while (!(ch == 'y' || ch == 'n'));
        switch (ch)
        {
        case 'y':
        {
            cout << "Good bye" << endl;
            break;
        }
        case 'n':
            select_Menu();
            break;
        }
    }
    }
}
void Init_Board()
{
    for (size_t i = 0; i < HEIGHT; i++)
        for (size_t j = 0; j < WIDTH; j++)
        {
            Board[i][j] = '.';
        }
}
void screen_clear()
{
    system("cls");
}
void Render()
{
    screen_clear();
    cout << "Score : " << score << "\tLines : " << lines << "\tState : " << state << endl;
    cout << '+' << setw(WIDTH + 1) << setfill('=') << '+' << endl;
    for (size_t i = 0; i < HEIGHT; i++)
    {
        cout << "|";
        for (size_t j = 0; j < WIDTH; j++)
        {
            int tempy = i - y;
            int tempx = j - x;
            if (tempx >= 0 && tempx < 2 && tempy >= 0 && tempy < 2 && O[tempy][tempx] == '#')
                cout << '#';
            else
                cout << Board[i][j];
        }
        cout << "|" << endl;
    }
    cout << '+' << setw(WIDTH + 1) << setfill('=') << '+' << endl;
}

bool can_move(int newx, int newy)
{
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            if (O[i][j] == '#')
            {
                int tempx = newx + j;
                int tempy = newy + i;
                if (tempx < 0 || tempx >= WIDTH || tempy < 0 || tempy >= HEIGHT)
                    return false;
                if (Board[tempy][tempx] == '#')
                    return false;
            }
        }
    }
    return true;
}
void lock_piece()
{
    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 2; j++)
            if (O[i][j] == '#')
                Board[i + y][x + j] = '#';
}
void new_piece()
{
    x = 4;
    y = 0;
    if (!can_move(x, y))
        state = "GAME OVER";
}
int main()
{
    Init_Board();
    select_Menu();
    while (state != "GAME OVER")
    {
        if (_kbhit())
        {
            char ch;
            ch = _getch();

            if (ch >= 'A' && ch <= 'Z')
                ch += 32;
            int newx = x;
            int newy = y;
            if (state == "PLAYING")
            {
                if (ch == 'a')
                    newx--;
                else if (ch == 'd')
                    newx++;
                else if (ch == 's')
                {
                    if (can_move(x, y + 1))
                        newy++;
                    else
                    {
                        lock_piece();
                        new_piece();
                        if (state == "GAME OVER")
                        {
                            Render();
                            break;
                        }
                    }
                }

                else if (ch == 'q')
                {
                    state = "FINISHED";
                    Render();
                    break;
                }

                else if (ch == 'p')
                {
                    state = "PAUSED";
                }
                if (can_move(newx, newy))
                {
                    x = newx;
                    y = newy;
                }
            }
            else if (state == "PAUSED")
            {
                if (ch == 'p')
                    state = "PLAYING";
                else if (ch == 'q')
                {
                    state = "FINISHED";
                    Render();
                    break;
                }
            }
        }
        Render();
        Sleep(80);
    }
    return 0;
}