#include <iostream>
#include <Windows.h>
#include <string>
#include <cstdlib> 
#include <ctime>  

using namespace std;

class Character
{
private:
	string name;
	int hp;
	int damage;
	int armor;

public:
	Character(string n, int h, int d, int ar)
	{
		name = n;
		hp = h;
		damage = d;
		armor = ar;
	}

	string getName() { return name; }
	int getHp() { return hp; }
	int getDamage() { return damage; }

	virtual void attack(Character& target) = 0;

	void takeDamage(int amount)
	{

		int currentArmor = armor + (rand() % 5 - 2);

		int realDamage = amount - currentArmor;

		if (realDamage < 0)
		{
			realDamage = 0;
		}

		hp -= realDamage;
		if (hp <= 0)
		{
			hp = 0;
		}
		cout << "[" << name << "] получил " << amount << " урона. Осталось HP: " << hp << "\n";
		cout << "(Броня сработала на " << currentArmor << "). Итоговый урон: " << realDamage << ". Осталось HP: " << hp << "\n";
	}
};


class Player : public Character
{
public:
	Player(string n, int h, int d, int ar) : Character(n, h, d, ar) {}

	void attack(Character& target) override
	{
		int finalDamage = getDamage() + (rand() % 7 - 3);

		if (rand() % 100 < 20)
		{
			cout << "КРИТ! ";
			finalDamage = finalDamage * 2;
		}

		cout << "[" << getName() << "] атакует! Урон: " << finalDamage << "\n";
		target.takeDamage(finalDamage);
	}
};


class Ork : public Character
{
public:
	Ork(string n, int h, int d, int ar) : Character(n, h, d, ar) {}

	void attack(Character& target) override
	{
		int finalDamage = getDamage() + (rand() % 11 - 5);

		if (rand() % 100 < 10)
		{
			cout << "КРИТ! ";
			finalDamage = finalDamage * 2;
		}

		cout << "[" << getName() << "] наносит сокрушительный удар! Урон: " << finalDamage << "\n";
		target.takeDamage(finalDamage);
	}
};


int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	srand(time(0));

	Player p1("Игрок", 100, 15, 2);
	Ork p2("Орк", 100, 15, 5);

	cout << "=== БОЙ НАЧАЛСЯ ===\n\n";

	while (p1.getHp() > 0 && p2.getHp() > 0)
	{
		p1.attack(p2);
		if (p2.getHp() <= 0) break; 
		Sleep(1000);

		p2.attack(p1);
		if (p1.getHp() <= 0) break; 
		Sleep(1000);
	}

	cout << "\n=== БОЙ ОКОНЧЕН ===\n";
	if (p1.getHp() <= 0)
	{
		cout << "Победил " << p2.getName() << "!\n";
	}
	else
	{
		cout << "Победил " << p1.getName() << "!\n";
	}

	return 0;
}