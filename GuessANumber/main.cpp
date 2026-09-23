#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    srand(time(0));
    char answer = 'y';
    
    
    
    
    while (answer == 'y')
    {
        int secret = rand() % 100 + 1;
        int attempts = 0;
        int guess = 0;
        cout << "Угадай число от 1 до 100\n";

        while (guess != secret) 
        {
            cout << "Твое число: ";
            cin >> guess;
            attempts++;
            if (guess > secret) { cout << "Меньше\n\n"; }
            else if (guess < secret) { cout << "Больше\n\n"; }

        }

        cout << "\nУгадал! Это было число: " << secret << "!" << "\n";
        cout << "Попыток: " << attempts;

        do
        {
            cout << "\nИграть еще? (y/n): \n\n";
            cin >> answer;
            cin.ignore(10000, '\n');
        } while (answer != 'y' && answer != 'n');
        system("cls");

    }
    cin.ignore();
    cin.get();
    return 0;
}