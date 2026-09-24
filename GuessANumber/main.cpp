#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>


using namespace std;

void select_difficulty() // ---Выбор сложности ---
{
    system("cls");

    cout << "Выбери уровень сложности: \n";
    cout << "1. Легкий (1-50)\n";
    cout << "2. Средний (1-100)\n";
    cout << "3. Сложный (1-1000)\n";
    cout << "Твой выбор: \n";
    
}

int main() {
    SetConsoleCP(65001); // --- UTF-8 в консоли для Windows ---
    SetConsoleOutputCP(65001);
    

    srand(time(0));
    char answer = 'y';
    int max_number = 100;
    int max_attempts = 0;


    while (answer == 'y') {
        select_difficulty();
        int choice;
        int secret = 0;
        int attempts = 0;
        int guess = 0;




        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Это не число! Нажми Enter...\n";
            cin.get();
            continue;
        }

        if (choice < 1 || choice > 3) {
            cout << "Неверный пункт меню! Нажми Enter...";
            cin.ignore();
            cin.get();
            continue;
        }

        switch (choice) 
        {
            case 1: 
                max_number = 50;
                max_attempts = 7;
                break;
            case 2: 
                max_number = 100; 
                max_attempts = 10;
                break;
            case 3: 
                max_number = 1000; 
                max_attempts = 11;
                break;
            default: 
                max_number = 100; 
                max_attempts = 10;
                break;
        }

        secret = rand() % max_number + 1;
        system("cls");
        cout << "Угадай число от 1 до " << max_number << "\n";
        while (secret != guess && max_attempts != 0)
        {
            cout << "Твой выбор: ";
            cin >> guess;
            ++attempts;
            --max_attempts;
            cout << "\nПопыток осталось: " << max_attempts;
            if (guess > secret) { cout << "\nЗагаданное число: Меньше\n\n"; }
            else if (guess < secret) { cout << "\nЗагаданное число: Больше\n\n"; }
        }

        if (max_attempts <= 0)
        {
            cout << "\nНе угадал! Это было число: " << secret;
            cout << "\nПопробуй еще раз..";
        }
        else {
            cout << "\n\nУгадал! Это было число: " << secret << "!" << "\n";
            cout << "Попыток: " << attempts;
        }
        
        do
        {
            cout << "\nИграть еще? (y/n): ";
            cin >> answer;
            cin.ignore(10000, '\n');
        } while (answer != 'y' && answer != 'n');
        system("cls");
    }


    cout << "Нажми 2 раза Enter чтобы выйти";
    cin.ignore();
    cin.get();
    return 0;
}