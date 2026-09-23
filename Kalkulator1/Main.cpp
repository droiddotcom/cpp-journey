#include <iostream>
#include <cstdlib>
#include <windows.h>
using namespace std;

void print_menu() {
    system("cls");

    cout << "=== КАЛЬКУЛЯТОР ===\n";
    cout << "1. Сложение\n";
    cout << "2. Вычитание\n";
    cout << "3. Умножение\n";
    cout << "4. Деление\n";
    cout << "0. Выход\n";
    cout << "Выбор: ";
}

bool read_number(double& value) {
    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    while (true) {
        print_menu();

        int choice;

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Это не число! Нажми Enter...\n";
            cin.get();
            continue;
        }

        if (choice == 0) {
            cout << "До свидания!\n";
            return 0;
        }

        if (choice < 0 || choice > 4) {
            cout << "Неверный пункт меню! Нажми Enter...\n";
            cin.ignore();
            cin.get();
            continue;  
        }



        double a, b;
        cout << "Первое число: ";
        if (!read_number(a)) {
            cout << "Это не число! Нажми Enter...\n";
            cin.get();
            continue;
        }
        cout << "Второе число: ";
        if (!read_number(b)) {
            cout << "Это не число! Нажми Enter...\n";
            cin.get();
            continue;
        }
        

        switch (choice) {
        case 1:
            cout << "Результат: " << a + b << "\n";
            break;
        case 2:
            cout << "Результат: " << a - b << "\n";
            break;
        case 3:
            cout << "Результат: " << a * b << "\n";
            break;
        case 4:
            if (b == 0)
            {
                cout << "Ошибка! На ноль делить нельзя!\n";
            }
            else 
            {
                cout << a / b << "\n";
            }
            break;
        default:
            cout << "Неверный пункт меню!\n";
            break;
        }

        cout << "\nНажми Enter для продолжения...";
        cin.ignore();
        cin.get();
    }
}