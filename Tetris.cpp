#include <iostream>
#include <iomanip>
#include <conio.h>   //_kbhit _getch
#include <windows.h> //gettickcount   sleep
using namespace std;
const int WIDTH = 10;
const int HEIGHT = 20;
int score = 0;
int lines = 0;
string state = "PLAYING";
char Board[HEIGHT][WIDTH];
int x = 4, y = 0;
char O[4][4] = {{'#', '#', '.', '.'},
                {'#', '#', '.', '.'},
                {'.', '.', '.', '.'},
                {'.', '.', '.', '.'}};

char I[4][4] = {
    {'#', '#', '#', '#'},
    {'.', '.', '.', '.'},
    {'.', '.', '.', '.'},
    {'.', '.', '.', '.'}};

char T[4][4] = {
    {'#', '#', '#', '.'},
    {'.', '#', '.', '.'},
    {'.', '.', '.', '.'},
    {'.', '.', '.', '.'}};

char Z[4][4] = {{'#', '#', '.', '.'},
                {'.', '#', '#', '.'},
                {'.', '.', '.', '.'},
                {'.', '.', '.', '.'}};

char L[4][4] = {{'#', '.', '.', '.'},
                {'#', '#', '#', '.'},
                {'.', '.', '.', '.'},
                {'.', '.', '.', '.'}};

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
            if (tempx >= 0 && tempx < 4 && tempy >= 0 && tempy < 4 && O[tempy][tempx] == '#')
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
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
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
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            if (O[i][j] == '#')
                Board[i + y][x + j] = '#';
}
void spawn_new_piece()
{
    x = 4;
    y = 0;
    if (!can_move(x, y))
        state = "GAME OVER";
}
bool line_is_full(int y1)
{
    for (size_t j = 0; j < WIDTH; j++)
        if (Board[y1][j] != '#')
            return false;
    return true;
}
void line_clear()
{
    int cleared_lines = 0;

    for (int i = HEIGHT - 1; i >= 0; i--)
    {
        if (line_is_full(i))
        {
            cleared_lines++;
            lines++;
            for (int row = i; row > 0; row--)
                for (size_t col = 0; col < WIDTH; col++)
                    Board[row][col] = Board[row - 1][col];
            for (size_t col = 0; col < WIDTH; col++)
                Board[0][col] = '.';
            i++;
        }
    }
    switch (cleared_lines)
    {
    case 1:
    {
        score += 100;
        break;
    }
    case 2:
    {
        score += 300;
        break;
    }
    case 3:
    {
        score += 500;
        break;
    }
    case 4:
    {
        score += 800;
        break;
    }
    }
}
void rotaite_piece(char piece[4][4])
{
    char rotate_piece[4][4];
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            rotate_piece[j][4 - 1 - i] = piece[i][j];
        }
    }
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
        {
            if (rotate_piece[i][j] == '#')
            {
                int nx = x + j;
                int ny = y + i;
                if (nx < 0 || nx >= WIDTH || ny < 0 || ny >= HEIGHT)
                    return;
                if (Board[ny][nx] == '#')
                    return;
            }
        }
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            piece[i][j] = rotate_piece[i][j];
}

int main()
{
    Init_Board();
    select_Menu();
    DWORD last_fall_time = GetTickCount();
    while (state != "GAME OVER")
    {
        DWORD now_time = GetTickCount();

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
                        line_clear();
                        spawn_new_piece();

                        if (state == "GAME OVER")
                        {
                            Render();
                            break;
                        }
                    }
                    last_fall_time = GetTickCount();
                }

                else if (ch == 'q')
                {
                    state = "FINISHED";
                    Render();
                    cout << "\n=======Good Bye=======\n";
                    break;
                }

                else if (ch == 'p')
                {
                    state = "PAUSED";
                }
                else if (ch == 'w')
                {
                    rotaite_piece(O);
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
                    cout << "\n=======Good Bye=======\n";
                    break;
                }
            }
        }
        if (state == "PLAYING")
        {
            if (now_time - last_fall_time >= 400)
            {
                if (can_move(x, y + 1))
                {
                    y++;
                }
                else
                {
                    lock_piece();
                    line_clear();
                    spawn_new_piece();
                }
                last_fall_time = GetTickCount();
            }
        }
        Render();
        Sleep(80);
    }
    return 0;
}