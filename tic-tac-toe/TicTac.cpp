#include <iostream>
#include <Windows.h>

using namespace std;

int main() {
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	
	char current = 'X';

	char board[3][3];

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			board[i][j] = ' ';
		}
		
	}
	int moves = 0;
	while (true)
	{

		system("cls");
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				cout << "|" << board[i][j];
			}
			cout << "|\n";
		}
		
		cout << "Введите строку и столбец (0-2) через пробел: ";
		int row, col;
		cin >> row >> col;
		if (row < 0 || row > 2 || col < 0 || col > 2) {
			cout << "Координаты от 0 до 2!\n";
			cout << "Нажмите Enter..";
			cin.ignore();
			cin.get();
			continue;
		}
		if (board[row][col] != ' ') {
			cout << "Клетка занята!\n";
			cout << "Нажмите Enter..";
			cin.ignore();
			cin.get();
			continue;    // вернуться в начало while
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
			board[0][2] != ' ' && board[0][2] == board[1][2] && board[1][2] == board[2][2]||
			// условие 7 (главная диагональ)
			board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2] ||
			// условие 8 (побочная диагональ)
			board[2][0] != ' ' && board[2][0] == board[1][1] && board[1][1] == board[0][2]					// 0 1 2
																											// 0 1 2
																											// 0 1 2
			) {
			cout << "Победил " << current << "!\n";
			break;
		}
		if (moves == 9)
		{
			cout << "Ничья!\n";
			break;
		}
		current = (current == 'X') ? 'O' : 'X';
	}

	return 0;
}