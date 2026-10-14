#include <iostream>
#include <Windows.h>
#include <string>


using namespace std;

void pause()
{
	cin.ignore();
	cin.get();
}

void printMenu()
{
	cout << "=== ФЕРМА ===\n";
	cout << "1. Показать статус\n";
	cout << "2. Подождать N дней\n";
	cout << "3. Наполнить воды\n";
	cout << "4. Полить растение\n";
	cout << "5. Выход\n";
	cout << "Ваш выбор: ";

}

bool read_number(int& choice)
{

	if (!(cin >> choice))
	{
		cin.clear();
		cin.ignore(10000, '\n');
		return false;
	}
	
	return true;

	
}

void show_status(int day, int water, int water_plant, int grow, int fade)
{
	system("cls");
	cout << "=== ДЕНЬ " << day << " ===\n";
	cout << "Вода в запасе: " << water << "/100\n";
	cout << "Единиц воды растения: " << water_plant << "/100\n";
	cout << "Прогресс роста: " << grow << "\n";
	cout << "Дней без воды: " << fade << "\n";
	cout << "==============\n";
	cout << "Нажмите Enter для продолжения...\n";
	pause();
	system("cls");
}

void wait_days(int skipDay, int& fade, bool& isRestart, int& day, int& grow, int& water_plant, int water)
{
	if (skipDay <= 0)
	{
		cout << "Введите положительное число!\n";
		cout << "Нажмите Enter...";
		pause();
		system("cls");
		return;
	}
	for (int i = 1; i <= skipDay; ++i)
	{
		if (fade >= 3)
		{
			isRestart = true;
			break;
		}
		if (water_plant <= 0)
		{
			fade += 1;
		}
		else
		{
			grow += 1;
		}

		day += 1; // --- +1 день
		if (water_plant > 0)
		{
			water_plant -= 10;
		}

	}
	if (fade >= 3) { isRestart = true; return; }
	cout << "\n\n=== Наступил " << day << " день ===\n";
	cout << "Воды в запасе: " << water << "/100\n";
	cout << "Единиц воды растения: " << water_plant << "/100\n";
	cout << "Прогресс роста: " << grow << "\n";
	cout << "Дней без воды: " << fade << "\n";
	cout << "==============\n\n";
	cout << "\n\nНажмите Enter для продолжения\n";
	pause();
	system("cls");
}

void fill_water(int water_pumped, int& water)
{
	if (water_pumped <= 0)
	{
		cout << "Введите положительное число!\n";
		cout << "Нажмите Enter...";
		pause();
		system("cls");
		return;
	}
	if (water + water_pumped > 100)
	{
		cout << "Вы не можете наполнить столько!\n";
		cout << "Нажмите Enter...";
		pause();
		system("cls");
		return;
	}
	else
	{
		water += water_pumped;
	}
	cout << "Вы набрали " << water_pumped << " единиц воды!\n";
	cout << "Воды в запасе: " << water << "/100\n";
	cout << "Нажмите Enter для продолжения...\n";
	pause();
	system("cls");
}


void water_plant_action(int& water, int& fade, int polivka, int& water_plant)
{
	if (polivka <= 0)
	{
		cout << "Введите положительное число!\n";
		cout << "Нажмите Enter...";
		pause();
		system("cls");
		return;
	}
	if (water < polivka)
	{
		cout << "Вам не хватает воды!\n" << "Вы можете пополнить ее в любой момент!\n";
		pause();
		system("cls");
		return;
	}
	if (water_plant + polivka > 100)
	{
		cout << "Вы не столько поливать растение!\n";
		cout << "Нажмите Enter...";
		pause();
		system("cls");
		return;
	}
	else
	{
		water_plant += polivka;
		water -= polivka;
		fade = 0;
	}


	cout << "Вы полили растение на " << polivka << " единиц воды. Теперь у него " << water_plant << " единиц воды!\n";
	cout << "Воды в запасе: " << water << "/100\n";
	cout << "Нажмите Enter для продолжения...\n";
	pause();
	system("cls");
}


int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	int water = 100;
	int water_plant = 10;
	int grow = 0;
	int day = 1;
	int fade = 0;
	int skipDay = 0;
	int choice = 1;
	int water_pumped = 0;
	int polivka = 0;
	bool isRestart = false;
	char answer = 'y';

	while (answer == 'y')
	{
		if (isRestart)
		{
			isRestart = false;
			water = 100;
			water_plant = 10;
			grow = 0;
			day = 1;
			fade = 0;
			do
			{
				cout << "К сожалению растение погибло...\n";
				cout << "Играть еще раз?(y/n): ";
				cin >> answer;
				cin.ignore(10000, '\n');
				system("cls");

			} while (answer != 'y' && answer != 'n');
			if (answer == 'n') { cout << "\nДо свидания!"; return 0; }
				
		} 
		printMenu();
		if (!read_number(choice))
		{
			cout << "\nВвод неверный!\n";
			cout << "Нажмите Enter...\n";
			pause();
			system("cls");
			continue;
		}

		if (choice < 1 || choice > 5)
		{
			cout << "Неправильно указан пункт меню!\n";
			pause();
			system("cls");
			continue;
		}

		switch (choice)
		{
			case 1:
				show_status(day, water, water_plant, grow, fade);
			break;

			case 2:
				system("cls");
				cout << "Введите число дней для пропуска!: ";
				if (!read_number(skipDay))
				{
					cout << "Введите число!\n";
					cout << "Нажмите Enter...\n";
					pause();
					system("cls");
					continue;
				}
				
				wait_days(skipDay, fade, isRestart, day, grow, water_plant, water);
			break;

			case 3:
				if (water >= 100)
				{
					cout << "Вы больше не можете наполнить воду!\n";
					cout << "Нажмите Enter...";
					pause();
					system("cls");
					continue;
				}
				
				cout << "На сколько единиц пополнить воды?: ";
				if (!read_number(water_pumped))
				{
					cout << "Введите число!\n";
					cout << "Нажмите Enter...\n";
					pause();
					system("cls");
					continue;
				}
				fill_water(water_pumped, water);
				break;

			case 4:
				if (water_plant >= 100)
				{
					cout << "Растение уже полито!\n";
					cout << "Нажмите Enter...";
					pause();
					system("cls");
					continue;
				}
				cout << "На сколько единиц воды полить растение?: ";
				if (!read_number(polivka))
				{
					cout << "Введите число!\n";
					cout << "Нажмите Enter...\n";
					pause();
					system("cls");
					continue;
				}
				water_plant_action(water, fade, polivka, water_plant);
				break;
			case 5:
				system("cls");
				cout << "До свидания!";
				pause();
				return 0;
		}
			
		
	}
	



	return 0;
}