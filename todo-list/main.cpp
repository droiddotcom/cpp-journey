#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
using namespace std;

void print_menu()
{
    cout << "=== TODO LIST ===\n";
    cout << "1. Добавить задачу\n";
    cout << "2. Показать все задачи\n";
    cout << "3. Выход\n";
}


struct Task {
    string text;
    bool done = false;
};



int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    vector<Task> tasks;

    while (true)
    {
        print_menu();
        int choice;
        cout << "Твой выбор: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Выбран неправильный пункт меню. Нажмите Enter...\n";
            cin.get();
            continue;
        }
        
        if (choice == 3) {
            cout << "До свидания!\n";
            return 0;
        }

        if (choice < 1 || choice > 3)
        {
            cout << "Неверный пункт меню! Нажми Enter...";
            cin.ignore();
            cin.get();
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            cin.ignore(10000, '\n');
            Task my_task;
            cout << "Текст: ";
            getline(cin, my_task.text);
            my_task.done = false;
            tasks.push_back(my_task);
            break;
        }
        case 2: 
        {
            if (tasks.empty())
            {
                cout << "Задач пока нет\n";
                break;
            }
            int i = 1;
            for (auto item : tasks) {
                cout << i << ". ";
                if (item.done) { cout << "[x] "; }
                else { cout << "[ ] "; }
                cout << item.text << "\n";
                ++i;
            }
            
            break;
        }

                
        }
    }
    cin.ignore();
    cin.get();
    return 0;
}