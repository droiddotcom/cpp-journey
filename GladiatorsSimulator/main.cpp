#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;


void set_color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}



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
	int hp = 120;
	int money = 100;
	int level = 1;
	int currentExp = 0;
	int strength = 1;
	int agility = 1;
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
	int getMaxHealth() { return 100 + (strength * 20); }
	int getCurrentLevel() { return level; }
	int getCurrentExp() { return currentExp; }
	int getExpToNewLevel() 
	{ 
		return 100 + ((level - 1) * 50);
	}
	int getStrength() { return strength; }
	int getAgility() { return agility; }
	int getDamage()
	{
		if (equippedWeapon == nullptr)
		{
			return damage + (agility * 2);
		}
		else
		{
			return damage + (agility * 2) + equippedWeapon->getDamageWeapon();
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
		if (hp > getMaxHealth())
		{
			hp = getMaxHealth();
		}
	}

	void printStatistic()
	{
		cout << "[" << getName() << "] | [Хп]: " << getHealth() << " | [Золото]: " << getMoney() << " | [Урон]: " << getDamage() << " | [Сила]: " << getStrength() << " | [Ловкость]: " << getAgility() << " | [Уровень]: " << getCurrentLevel() << " | [Опыт]: " << getCurrentExp() << "/" << getExpToNewLevel() << "\n";
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

	void addExpToPlayer(int amount)
	{
		if (amount < 0)
		{
			amount = 0;
			return;
		}
		currentExp += amount;

		int expNeeded = getExpToNewLevel();

		if (currentExp >= expNeeded)
		{
			level += 1;
			strength += 1;
			agility += 1;
			currentExp -= expNeeded;
			hp = getMaxHealth();
			set_color(10);
			cout << "=== УРОВЕНЬ ПОВЫШЕН! ===" << "\n";
			set_color(7);
			setPause();
		}
	}




	bool isDead()
	{
		return hp <= 0;
	}

	void goToHospital()
	{
		if (hp >= getMaxHealth())
		{
			set_color(12);
			cout << "Ты выглядишь слишком целым для этого места. Иди, не занимай место, мне тут трупы бинтовать надо" << "\n";
			set_color(7);
			setPause();
			return;
		}
		if (money < 30)
		{
			set_color(12);
			cout << "Эй, приятель, я вижу, ты еле стоишь. Но я тут работаю за звонкую монету. Приходи, когда у тебя будет 30 золотых, и я подлатаю твои кости." << "\n";
			set_color(7);
			setPause();
			return;
		}
		if (hp <= (getMaxHealth() / 2))
		{
			set_color(10);
			cout << "Ну-ка, покажись... Ого, да у тебя тут мясо висит. Так, 30 монет на бочку. Сейчас будет больно." << "\n";
			set_color(7);
		}
		else
		{
			set_color(14);
			cout << "Ты почти в порядке. Но раз платишь, я замажу твои царапины. Только учти, что нынче труд оплачивается!" << "\n";
			set_color(7);
		}

		money -= 30;
		hp += 50;
		if (hp > getMaxHealth()) hp = getMaxHealth();
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
					set_color(10);
					cout << "  <=== [В РУКАХ]";
					set_color(7);
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
				set_color(10);
				cout << "[" << selectedWeapon->getNameWeapon() << "] успешно куплен!" << "\n";
				set_color(7);
				buyer.spendMoney(selectedWeapon->getPriceWeapon());
				buyer.addWeaponToInv(selectedWeapon);
				shop.erase(weaponName);
			}
			else
			{
				set_color(12);
				cout << "Нехватает денег!" << "\n";
				set_color(7);
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
	int rewardExp;
public:
	Enemy(string n, int h, int d, int r, int rE) { name = n, hp = h, damage = d, reward = r; rewardExp = rE; }

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
	int getRewardExp() { return rewardExp; }

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
		cout << "[Ваши статы]: HP: " << player.getHealth() << " | Урон: " << player.getDamage() << " | Уровень: " << player.getCurrentLevel() << " | Опыт: " << player.getCurrentExp() << " | Опыта до следущего уровня: " << player.getExpToNewLevel() - player.getCurrentExp() << "\n";
		cout << "[Статы врага]: HP: " << enemy->getHpOfEnemy() << " | Урон: " << enemy->getDamageOfEnemy() << " | Награда: " << enemy->getRewardOfEnemy() << " | Опыт: " << enemy->getRewardExp() << "\n\n";
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
			player.addExpToPlayer(enemy->getRewardExp());
			cout << "Вы получили " << enemy->getRewardOfEnemy() << " золота и " << enemy->getRewardExp() << " опыта!" << "\n";
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
	set_color(14);
	cout << "==== Симулятор Гладиатора ====" << "\n";
	set_color(7);
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
			set_color(11);
			myPlayer.printStatistic();
			set_color(7);
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
				Enemy slime("Слайм", 30, 5, 20, 30);
				myArena.getStatisticOfFight(&slime, myPlayer);
				myArena.startRound(&slime, myPlayer);
			}
			else
			{
				Enemy goblin("Гоблин", 60, 15, 50, 60);
				myArena.getStatisticOfFight(&goblin, myPlayer);
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