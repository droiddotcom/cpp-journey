#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

void setPause()
{
	cout << "[Нажмите Enter...]" << "\n";
	cin.ignore();
	cin.get();
}



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
	Weapon* equippedWeapon = nullptr;
public:
	Player(string n)
	{
		name = n;
	}

	string getName() { return name; }
	int getMoney() { return money; }
	int getHealth() { return hp; }
	int getDamage()
	{
		if (equippedWeapon == nullptr)
		{
			return damage;
		}
		else
		{
			return damage + equippedWeapon->getDamageWeapon();
		}
	}

	void takeDamage(int amount)
	{
		hp -= amount;
		if (hp < 0)
		{
			hp = 0;
		}
		cout << "[" << getName() << "] получил " << amount << " единиц урона. Оставшееся [Хп]: " << hp << "\n";
	}

	void Heal(int amount)
	{
		hp += amount;
		if (hp > 100)
		{
			hp = 100;
		}
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

	void addMoney(int amount)
	{
		money += amount;
	}


	bool isDead()
	{
		return hp <= 0;
	}

	void goToHospital()
	{
		if (hp >= 100)
		{
			cout << "Ты выглядишь слишком целым для этого места. Иди, не занимай место, мне тут трупы бинтовать надо" << "\n";
			setPause();
			return;
		}
		if (money < 30)
		{
			cout << "Эй, приятель, я вижу, ты еле стоишь. Но я тут работаю за звонкую монету. Приходи, когда у тебя будет 30 золотых, и я подлатаю твои кости." << "\n";
			setPause();
			return;
		}
		if (hp <= 50)
		{
			cout << "Ну-ка, покажись... Ого, да у тебя тут мясо висит. Так, 30 монет на бочку. Сейчас будет больно." << "\n";
		}
		else
		{
			cout << "Ты почти в порядке. Но раз платишь, я замажу твои царапины. Только учти, больше 100 ХП я тебе не сделаю." << "\n";
		}

		money -= 30;
		hp += 50;
		if (hp > 100) hp = 100;
		if (money < 0) money = 0;
		setPause();
	}

	void showFullInventoryPlayer()
	{
		if (inventory.empty())
		{
			cout << "Инвентарь пусть. Пора набить его оружием!" << "\n";
		}
		else
		{
			for (auto const& pair : inventory)
			{
				cout << "[" << pair.first << "] | Урон: " << pair.second->getDamageWeapon() << " единиц";

				if (equippedWeapon == pair.second)
				{
					cout << "  <=== [В РУКАХ]";
				}
				cout << "\n";
			}
		}
		
	}


	void equipWeapon(string weaponName)
	{
		if (inventory.find(weaponName) != inventory.end())
		{
			equippedWeapon = inventory[weaponName];
			cout << "Вы взяли в руки [" << weaponName << "]" << "\n";
			setPause();
		}
		else
		{
			cout << "У вас нет такого оружия в рюкзаке" << "\n";
			setPause();
		}
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
				cout << "[" << selectedWeapon->getNameWeapon() << "] успешно куплен!" << "\n";
				buyer.spendMoney(selectedWeapon->getPriceWeapon());
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

class Enemy
{
protected:
	string name;
	int hp;
	int damage;
	int reward;
public:
	Enemy(string n, int h, int d, int r) { name = n, hp = h, damage = d, reward = r; }

	void takeDamage(int amount)
	{
		hp -= amount;
		if (hp < 0)
		{
			hp = 0;
		}
	}

	string getNameOfEnemy()
	{
		return name;
	}
	int getHpOfEnemy()
	{
		return hp;
	}
	int getDamageOfEnemy()
	{
		return damage;
	}
	int getRewardOfEnemy()
	{
		return reward;
	}

	bool isDead()
	{
		return hp <= 0;
	}

};


class Arena
{
private:
	int countOfRound = 0;
public:


	int addCountToRound(int amount)
	{
		countOfRound += amount;
		return countOfRound;
	}

	void getStatisticOfFight(Enemy* enemy, Player& player)
	{
		cout << "=== НА АРЕНУ ВЫХОДИТ ПРОТИВНИК ===" << "\n";
		cout << "Вы столкнулись с [" << enemy->getNameOfEnemy() << "]!" << "\n\n";
		cout << "[Ваши статы]: HP: " << player.getHealth() << " | Урон: " << player.getDamage() << "\n";
		cout << "[Статы врага]: HP: " << enemy->getHpOfEnemy() << " | Урон: " << enemy->getDamageOfEnemy() << " | Награда: " << enemy->getRewardOfEnemy() << "\n\n";
		cout << "Нажмите Enter, чтобы начать бой..." << "\n";
		setPause();
	}


	void startRound(Enemy* enemy, Player& player)
	{
		
		string enemyName = enemy->getNameOfEnemy();
		int enemyDamage = enemy->getDamageOfEnemy();

		int playerDamage = player.getDamage();
		
		countOfRound = 0;

		while (player.getHealth() > 0 && enemy->getHpOfEnemy() > 0)
		{
			cout << "--- РАУНД " << addCountToRound(1) << " ---" << "\n";
			cout << "Вы атакуете " << enemyName << "а на " << playerDamage << " урона!" << "\n";
			
			enemy->takeDamage(playerDamage);
			cout << "У " << enemyName << "а осталось HP: " << enemy->getHpOfEnemy() << "\n";
			
			if (enemy->getHpOfEnemy() <= 0) break;

			setPause();

			cout << enemyName << " бьет вас на " << enemyDamage << " урона!" << "\n";
			
			player.takeDamage(enemyDamage);
			cout << "У вас осталось HP: " << player.getHealth() << "\n";
			
			if (player.getHealth() <= 0) break;

			cout << "\n\n";
			setPause();
		}
		if (enemy->getHpOfEnemy() <= 0)
		{
			cout << "Вы победили " << enemyName << "!\n";
			player.addMoney(enemy->getRewardOfEnemy());
			cout << "Вы получили " << enemy->getRewardOfEnemy() << " золота!\n";
			setPause();
		}
		else
		{
			cout << "Вы проиграли..." << "\n";
			cout << "До встречи!" << "\n";
			setPause();
			exit(0);
		}

	}

};


void printMenu()
{
	system("cls");
	cout << "==== Симулятор Гладиатора ====" << "\n";
	cout << "1. Мои характеристики" << "\n";
	cout << "2. Посмотреть магазин" << "\n";
	cout << "3. Купить оружие" << "\n";
	cout << "4. Пойти на арену" << "\n";
	cout << "5. Пойти в лазарет" << "\n";
	cout << "6. Посмотреть инвентарь" << "\n";
	cout << "7. Выбрать оружие" << "\n";
	cout << "8. Выход" << "\n";
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


int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);


	srand(time(0));


	
	Shop myShop;
	Arena myArena;
	Player myPlayer("Геральд");
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
		if (choice < 1 || choice > 8)
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
			cout << "\n";
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
			int chance = rand() % 100 + 1;
			if (chance <= 50)
			{
				Enemy slime("Слайм", 30, 5, 20);

				myArena.startRound(&slime, myPlayer);
			}
			else
			{
				Enemy goblin("Гоблин", 60, 15, 50);

				myArena.startRound(&goblin, myPlayer);
			}

			break;
		}
		case 5:
		{
			myPlayer.goToHospital();
			break;
		}
		case 6:
		{
			myPlayer.showFullInventoryPlayer();
			setPause();
			break;
		}
		case 7:
		{
			cout << "Введите название имеющегося оружия, чтобы взять его в руки:" << "\n";
			string weaponName;
			cin.ignore(10000, '\n');
			getline(cin, weaponName);
			myPlayer.equipWeapon(weaponName);
			break;
		}
		case 8:
		{
			cout << "До свидания!" << "\n";
			setPause();
			return 0;
		}
		}
		
	}


	return 0;
}