#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>

using namespace std;

class Item
{
protected:
	string name;
	int price;
	int weight;


public:
	Item(string n, int p, int w)
	{
		name = n;
		price = p;
		weight = w;
	}

	virtual ~Item() {}

	virtual void printInfo() = 0;

	int getWeigth() { return weight; }
	int getPrice() { return price; }
};


class Weapon : public Item
{
private:
	int damage;


public:
	Weapon(string n, int p, int w, int d) : Item(n, p, w) { damage = d; }

	void printInfo() override
	{
		cout << "Оружие: " << "[" << name << "] | Урон: " << "[" << damage << "] | Цена: " << "[" << price << "] | Вес: " << "[" << weight << "]\n";
	}

};

class Potion : public Item
{
private: 
	int healAmount;
public:
	Potion(string n, int p, int w, int h) : Item(n, p, w) { healAmount = h; }

	void printInfo() override
	{
		cout << "Зелье: " << "[" << name << "] | Лечение: " << "[" << healAmount << "] | Цена: " << "[" << price << "] | Вес: " << "[" << weight << "]\n";
	}
};

class Armor : public Item
{
private:
	int defense;
public:
	Armor(string n, int p, int w, int d) : Item(n, p, w) { defense = d; }

	void printInfo() override
	{
		cout << "Броня: " << "[" << name << "] | Защита: " << "[" << defense << "] | Цена: " << "[" << price << "] | Вес: " << "[" << weight << "]\n";
	}
	
};


class Inventory
{
private:
	vector<Item*> items;
public:
	
	
	void addItem(Item* newItem)
	{
		items.push_back(newItem);
	}

	void showInventory()
	{
		for (Item* item : items)
		{
			item->printInfo();
		}
	}

	int getTotalWeigth()
	{
		int totalWeight = 0;

		for (Item* item : items)
		{
			totalWeight += item->getWeigth();
		}

		return totalWeight;
	}

	int getTotalPrice()
	{
		int totalPrice = 0;

		for (Item* item : items)
		{
			totalPrice += item->getPrice();
		}

		return totalPrice;
	}

};


int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	Inventory myBag;

	Weapon sword("Меч рыцаря", 100, 10, 25);
	Potion healthPotion("Зелье лечения", 50, 1, 30);
	Armor plate("Стальная броня", 200, 25, 15);

	myBag.addItem(&sword);
	myBag.addItem(&healthPotion);
	myBag.addItem(&plate);
	myBag.showInventory();

	cout << "Общий вес: " << myBag.getTotalWeigth() << "\n";
	cout << "Общая ценность: " << myBag.getTotalPrice() << "\n";


	return 0;
}