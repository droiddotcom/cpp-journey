#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <map>

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
	string getName() { return name; }
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
	map<string, Item*> items;
public:
	
	
	void addItem(Item* newItem)
	{
		items[newItem->getName()] = newItem;
	}

	void findItem(string name)
	{
		auto it = items.find(name);
		if (it != items.end())
		{
			it->second->printInfo();
		}
		else
		{
			cout << "Предмета " << name << " нет в рюкзаке.\n";
		}

	}

	void showInventory()
	{
		for (auto const& pair : items)
		{
			pair.second->printInfo();
		}
	}

	int getTotalWeigth()
	{
		int totalWeight = 0;

		for (auto const& pair : items)
		{
			totalWeight += pair.second->getWeigth();
		}

		return totalWeight;
	}

	int getTotalPrice()
	{
		int totalPrice = 0;

		for (auto const& pair : items)
		{
			totalPrice += pair.second->getPrice();
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