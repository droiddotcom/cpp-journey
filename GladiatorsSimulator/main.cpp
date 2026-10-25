#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

class Weapon
{
protected:
	string nameWeapon;
	int damage;
	int price;
	bool isAvailible;
public:
	Weapon(string n, int d, int p, bool iA) { nameWeapon = n, damage = d, price = p, isAvailible = iA; }
	virtual ~Weapon() {}

	string getNameWeapon()
	{
		return nameWeapon;
	}

	int getDamageWeapon()
	{
		return damage;
	}

	int getPriceWeapon()
	{
		return price;
	}

	bool getIsAvailible()
	{
		return isAvailible;
	}
};


class Player
{
private:
	string name;
	int damage = 10;
	int hp = 100;
	int money = 100;
	map<string, Weapon*> inventory;
public:
	Player(string n)
	{
		name = n;
	}

	string getName() { return name; }
	int getMoney() { return money; }
	int getHealth() { return hp; }
	int getDamage() { return damage; }

	void takeDamage(int amount)
	{
		hp -= amount;
		if (hp < 0)
		{
			hp = 0;
		}
		cout << "[" << getName() << "] получил " << amount << " единиц урона. Оставшееся [Хп]: " << hp << "\n";
	}

	void printStatistic()
	{
		cout << "[" << getName() << "] | [Хп]: " << getHealth() << " | [Золото]: " << getMoney() << " | [Урон]: " << getDamage() << "\n";
	}

	void addDamage(int amount)
	{
		damage += amount;
	}

	void spendMoney(int amount)
	{
		money -= amount;
	}

	void addWeaponToInv(Weapon* weapon)
	{
		inventory[weapon->getNameWeapon()] = weapon;
	}

};



class Shop
{
private:
	map<string, Weapon*> shop;
public:
	void showAllItems()
	{
		for(auto const& pair: shop)
		{
			cout << "[" << pair.second->getNameWeapon() << "] | [Стоимость]: " << pair.second->getPriceWeapon() << " | [Урон]: " << pair.second->getDamageWeapon() << "\n";
		}
	}

	void buyWeapon(string weaponName, Player& buyer)
	{
		
		if (shop.find(weaponName) != shop.end())
		{
			int price = shop[weaponName]->getPriceWeapon();
			Weapon* selectedWeapon = shop[weaponName];
			if (buyer.getMoney() >= price)
			{
				buyer.addDamage(selectedWeapon->getDamageWeapon());
				cout << "[" << selectedWeapon->getNameWeapon() << "] успешно куплен!" << "\n";
				buyer.spendMoney(selectedWeapon->getPriceWeapon());
				buyer.addWeaponToInv(selectedWeapon);
				buyer.addWeaponToInv(selectedWeapon);
				shop.erase(weaponName);
			}
			else
			{
				cout << "Нехватает денег!" << "\n";
			}
		}
		else
		{
			cout << "[" << weaponName << "] нету в наличии!" << "\n";
		}
	}


	void addWeaponToShop(Weapon* weapon)
	{
		shop[weapon->getNameWeapon()] = weapon;
	}


};

void setPause()
{
	cout << "Нажмите Enter для продолжения..." << "\n";
	cin.ignore();
	cin.get();
}


void printMenu()
{
	system("cls");
	cout << "==== Симулятор Гладиатора ====" << "\n";
	cout << "1. Мои характеристики" << "\n";
	cout << "2. Посмотреть магазин" << "\n";
	cout << "3. Купить оружие" << "\n";
	cout << "4. Выход" << "\n";
}


bool checkChoice(int& choice)
{
	if (!(cin >> choice))
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Выбран неверный пункт меню! Нажмите Enter..." << "\n";
		setPause();
		return true;
	}
	return false;
}

void coutN()
{
	cout << "\n";
}

int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);


	Player myPlayer("Геральд");
	Shop myShop;
	Weapon WoodenClub("Деревянная дубина", 5, 100, true);
	Weapon WoodenSword("Деревянный меч", 13, 180, true);
	Weapon IronAxe("Железный топор", 50, 460, true);

	myShop.addWeaponToShop(&WoodenClub);
	myShop.addWeaponToShop(&WoodenSword);
	myShop.addWeaponToShop(&IronAxe);

	while (true)
	{
		int choice;
		printMenu();
		cout << "Выберите действие: ";
		if (checkChoice(choice))
		{
			continue;
		}
		if (choice < 1 || choice > 4)
		{
			cout << "Такого пункта нет!" << "\n";
			setPause();
			continue;
		}

		switch (choice)
		{
		case 1:
		{
			myPlayer.printStatistic();
			setPause();
			break;

		}
		case 2:
		{
			myShop.showAllItems();
			setPause();
			break;
		}
		case 3:
		{
			myShop.showAllItems();
			coutN();
			cout << "Введите название оружия: ";
			cin.ignore(1000, '\n');
			string weaponNameGame;
			getline(cin, weaponNameGame);
			myShop.buyWeapon(weaponNameGame, myPlayer);
			setPause();
			break;
		}
		case 4:
		{
			cout << "До свидания!" << "\n";
			setPause();
			return 0;
		}
		}
		
	}


	return 0;
}