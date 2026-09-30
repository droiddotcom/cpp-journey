#include <iostream>
#include <Windows.h>


using namespace std;

void set_color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int x_wins = 0;
    int o_wins = 0;
    int draws = 0;

    char answer = 'y';
    char board[3][3];

    while (answer == 'y')
    {
        

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                board[i][j] = ' ';
            }

        }
        char current = 'X';
        int moves = 0;
        while (true)
        {
            system("cls");
            cout << "Счёт: X: " << x_wins << " | " << "O: " << o_wins << " | " << "Ничьих: " << draws << "\n\n";
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    cout << "|";
                    if (board[i][j] == 'X') set_color(12);
                    else if (board[i][j] == 'O') set_color(9);
                    else set_color(7);
                    cout << board[i][j];
                    set_color(7);
                }
                cout << "|\n";
            }


            cout << "\nВведите строку и столбец (0-2) через пробел: ";
            int row, col;
            if (!(cin >> row >> col))
            {
                cout << "Вы ввели неправильное значение!\n";
                cout << "Нажмите Enter..";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            if (row < 0 || row > 2 || col < 0 || col > 2)
            {
                cout << "Координаты от 0 до 2";
                cout << "Нажмите Enter..";
                cin.ignore();
                cin.get();
                continue;
            }

            if (board[row][col] != ' ')
            {
                cout << "Клетка занята\n";
                cout << "Нажмите Enter..";
                cin.ignore();
                cin.get();
                continue;


            }
            board[row][col] = current;
            ++moves;
            if (
                // условие 1 (верхняя строка) 
                board[0][0] != ' ' && board[0][0] == board[0][1] && board[0][1] == board[0][2] ||
                // условие 2 (средняя строка)
                board[1][0] != ' ' && board[1][0] == board[1][1] && board[1][1] == board[1][2] ||
                // условие 3 (нижняя строка)
                board[2][0] != ' ' && board[2][0] == board[2][1] && board[2][1] == board[2][2] ||
                // условие 4 (левый столбец)
                board[0][0] != ' ' && board[0][0] == board[1][0] && board[1][0] == board[2][0] ||
                // условие 5 (средний столбец)
                board[0][1] != ' ' && board[0][1] == board[1][1] && board[1][1] == board[2][1] ||
                // условие 6 (правый столбец)
                board[0][2] != ' ' && board[0][2] == board[1][2] && board[1][2] == board[2][2] ||
                // условие 7 (главная диагональ)
                board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2] ||
                // условие 8 (побочная диагональ)
                board[2][0] != ' ' && board[2][0] == board[1][1] && board[1][1] == board[0][2]
                ) {
                cout << "Победил: " << current << "!\n";
                if (current == 'X') ++x_wins;
                else ++o_wins;
                cout << "Играть еще? (y/n): ";
                cin >> answer;
                break;
            }
            if (moves == 9)
            {
                cout << "Ничья!";
                ++draws;
                cout << "Играть еще? (y/n): ";
                cin >> answer;
                break;
            }

            current = (current == 'X') ? 'O' : 'X';

        }
    }


    return 0;
}
