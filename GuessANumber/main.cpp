#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);


    srand(time(0));
    int secret = rand() % 100 + 1;
    int guess = 0;
    int attempts = 0;
    cout << "Угадай число от 1 до 100" << "\n";
    while (guess != secret)
    {
        cout << "Твоя попытка: ";
        cin >> guess;
        attempts++;
        if (guess > secret) { cout << "Меньше\n\n"; }
        else if (guess < secret) { cout << "Больше\n\n"; }

    }
    cout << "\nПопыток: " << attempts;
    cout << "\nУгадал! Это было число: " << secret << "!" << "\n";
    cin.ignore();
    cin.get();
    return 0;
}