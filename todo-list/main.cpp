#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <fstream>
using namespace std;


struct Task {
    string text;
    bool done = false;
};

void print_menu()
{
    cout << "=== TODO LIST ===\n";
    cout << "1. Добавить задачу\n";
    cout << "2. Показать все задачи\n";
    cout << "3. Отметить выполненной\n";
    cout << "4. Удалить задачу\n";
    cout << "5. Выход\n";
}

void save_file(const vector<Task>& tasks)
{
    ofstream file("tasks.txt");
    for (auto& t : tasks)
    {
        file << t.done << "|" << t.text << "\n";

    }
    file.close();
}

void load_file(vector<Task>& tasks) {
    ifstream file("tasks.txt");
    if (!file.is_open()) {
        return;
    }
    string line;
    while (getline(file, line)) {
        Task my_task;
        int pos = line.find('|');
        my_task.text = line.substr(pos + 1);
        my_task.done = (line[0] == '1');
        tasks.push_back(my_task);
    }
    file.close();
}


int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    vector<Task> tasks;
    load_file(tasks);

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

        if (choice < 1 || choice > 5)
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
            cout << "Задача добавлена.\n";
            cout << "Нажмите Enter...";
            cin.ignore();
            system("cls");
            break;
        }
        case 2: 
        {
            if (tasks.empty())
            {
                cout << "Задач пока нет\n";
                cout << "Нажмите Enter...";
                cin.ignore();
                cin.get();
                system("cls");
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
            cout << "Нажмите Enter...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        }
        case 3:
        {
            if (tasks.empty())
            {
                cout << "Задач пока нет...\n";
                cout << "Нажмите Enter...";
                cin.ignore();
                cin.get();
                system("cls");
                break;
            }
            int i = 1;
            for (auto option : tasks)
            {
                cout << i << ". ";
                if (option.done) { cout << "[x] "; }
                else { cout << "[ ] "; }
                cout << option.text << "\n";
                ++i;
            }

            cout << "\nКакую задачу отметить?: ";
            int option;
            if (!(cin >> option))
            {
                cout << "\nНеправильно выбран номер задачи\n";
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Нажмите Enter...";
                cin.ignore();
                system("cls");
                continue;
            }

            if (option <= 0 || option > tasks.size())
            {
                cout << "Ошибка! Номера такой задачи не существует!\n";
                cout << "Нажмите Enter...";
                cin.ignore();
                cin.get();
                system("cls");
                break;
            }
            tasks[option - 1].done = true;

            cout << "Задача отмечена!\n";
            cout << "Нажмите Enter...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        }
        case 4:
        {
            if (tasks.empty())
            {
                cout << "Задач пока нет...\n";
                cout << "Нажмите Enter...";
                cin.ignore();
                cin.get();
                system("cls");
                break;
            }
            int i = 1;
            for (auto option : tasks)
            {
                cout << i << ". ";
                if (option.done) { cout << "[x] "; }
                else { cout << "[ ] "; }
                cout << option.text << "\n";
                ++i;
            }

            cout << "Какую задачу удалить?: ";
            int option;
            if (!(cin >> option))
            {
                cout << "\nНеправильно выбран номер задачи\n";
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Нажмите Enter...";
                cin.ignore();
                cin.get();
                system("cls");
                continue;
            }
            if (option <= 0 || option > tasks.size())
            {
                cout << "\nТакой задачи не существует!";
                cout << "\nНажмите Enter...";
                cin.ignore();
                cin.get();
                system("cls");
                break;
            }
            tasks.erase(tasks.begin() + (option - 1));

            cout << "\nЗадача удалена";
            cout << "\nНажмите Enter...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        }
        case 5:
        {
            save_file(tasks);
            cout << "До свидания!\n";
            cout << "Нажмите Enter...";
            cin.ignore();
            cin.get();
            return 0;
            break;
        }

                
        }
    }
    cin.ignore();
    cin.get();
    return 0;
}