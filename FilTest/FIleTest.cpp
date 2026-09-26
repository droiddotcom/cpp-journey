#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;


void print_menu()
{
    cout << "=== ФАЙЛ ===\n";
    cout << "1. Записать в файл\n";
    cout << "2. Прочитать файл\n";
    cout << "3. Выход\n";
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int choice;

    while (true)
    {
        print_menu();
        cout << "Твой выбор: ";

        if (!(cin >> choice))
        {
            cout << "Введите цифру";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Нажмите Enter...";
            cin.ignore();
            continue;
        }
        if (choice < 1 || choice > 3)
        {
            cout << "Неправильно выбрана опция меню! Нажмите Enter";
            cin.ignore();
            cin.get();
            continue;
        }
        string line;
        switch (choice) {
        case 1:
        {
            ofstream file_out("test.txt");
            cin.ignore(10000, '\n');
            cout << "\nПодсказка - для выхода введите:\"Выход\"\n";
            while (true)
            {
                cout << "Строка: ";

                getline(cin, line);
                if (line == "Выход" || line == "выход") { break; }
                file_out << line << "\n";
            }
            file_out.close();
            cout << "Записано\n";
            cout << "Нажмите Enter для выхода...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        }

        case 2:
        {
            int i = 1;
            ifstream file_in("test.txt");
            if (!file_in.is_open())
            {
                cout << "Файл не найден!\n";
                cin.ignore();
                break;
            }
            while (getline(file_in, line))
            {
                cout << i << ". " << line << "\n";
                ++i;
            }
            file_in.close();
            cout << "Нажмите Enter...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        }
        case 3:
        {
            cout << "До свидания!\n";
            cout << "Нажмите Enter...";
            cin.ignore();
            cin.get();
            return 0;
        }
        }
    }


    return 0;
}