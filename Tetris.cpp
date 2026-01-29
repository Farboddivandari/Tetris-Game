#include <iostream>
#include <iomanip>
using namespace std;
const int WIDTH = 10;
const int HEIGHT = 20;
int score = 0;
int lines = 0;
string state = "PLAYING";

char Board[HEIGHT][WIDTH];
void show_Menu()
{
    cout << "_____ Tetris Game _____" << endl
         << "1-New Game" << "\n2-Help" << "\n3_Exit" << endl;
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
    cout << '+' << setw(11) << setfill('=') << '+' << endl;
    for (size_t i = 0; i < HEIGHT; i++)
    {
        cout << "|";
        for (size_t j = 0; j < WIDTH; j++)
            cout << Board[i][j];
        cout << "|" << endl;
    }
    cout << '+' << setw(WIDTH + 1) << setfill('=') << '+' << endl;
}
int main()
{
    Init_Board();
    select_Menu();
    Render();
    return 0;
}