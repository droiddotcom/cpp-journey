#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>


using namespace std;

class GuildMember
{
private:
	string name;
	int level;
	int power;
public:
	GuildMember(string n, int l) { name = n; level = l; }
	virtual ~GuildMember() {}

	virtual int getPower() = 0;


	virtual void printInfo() = 0;

	int getLevel()
	{
		return level;
	}

	string getName()
	{
		return name;
	}

};


class Warrior : public GuildMember
{
private:
	int strength;
public:
	Warrior(string n, int l, int s) : GuildMember(n, l) { strength = s; }
	virtual ~Warrior() {}

	int getPower() override
	{
		return getLevel() * strength;
	}

	int getStrength()
	{
		return strength;
	}

	void printInfo() override
	{
		cout << "Участник: " << "[" << getName() << "] | ЛВЛ: " << "[" << getLevel() << "] | Сила: " << "[" << getStrength() << "] | Мощь: " << getPower() << "\n" ;
	}


};

class Mage : public GuildMember
{
private:
	int mana;
	int intelligence;
public:
	Mage(string n, int l, int i) : GuildMember(n, l) { intelligence = i; mana = getMana(); }
	virtual ~Mage() {}

	int getMana()
	{
		return 75 + (intelligence * 12);
	}

	int getIntelligence()
	{
		return intelligence;
	}

	int getPower() override
	{
		return getLevel() * getIntelligence();
	}
		
	void printInfo() override
	{
		cout << "Участник: " << "[" << getName() << "] | ЛВЛ: " << "[" << getLevel() << "] | Интеллект: " << "[" << getIntelligence() << "] | Мана: " << getMana() << "] | Мощь: " << getPower() << "\n";
	}
};

class Bandit : public GuildMember
{
private:
	int agility;
public:
	Bandit(string n, int l, int a) : GuildMember(n, l) { agility = a; }
	virtual ~Bandit() {}


	int getAgility() { return agility; }

	int getPower() { return getLevel() * getAgility(); }

	void printInfo() override
	{
		cout << "Участник: " << "[" << getName() << "] | ЛВЛ: " << "[" << getLevel() << "] | Ловкость: " << "[" << getAgility() << "] | Мощь: " << getPower() << "\n";
	}

};

class Guild
{
private:
	vector<GuildMember*> members;
public:
	void addMember(GuildMember* user)
	{
		members.push_back(user);
	}

	void printMembers()
	{
		for (GuildMember* member : members)
		{
			member->printInfo();
		}
	}

	int getAllPower()
	{
		int allPower = 0;
		for (GuildMember* member : members)
		{
			allPower += member->getPower();
		}

		return allPower;
	}

	GuildMember* theStrongestMember()
	{
		GuildMember* theStrongest = members[0];
		for (GuildMember* member : members)
		{
			if (member->getPower() > theStrongest->getPower())
			{
				theStrongest = member;
			}
		}

		return theStrongest;
	}

};

int main()
{

	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	Guild myGuild;

	Warrior p1("Воин", 20, 70);
	Mage p2("Маг", 35, 80);
	Bandit p3("Бандит", 40, 110);


	myGuild.addMember(&p1);
	myGuild.addMember(&p2);
	myGuild.addMember(&p3);

	myGuild.printMembers();

	cout << "Общая сила: " << myGuild.getAllPower() << "\n";

	cout << "Самый сильный участник гильдии: " << myGuild.theStrongestMember()->getName() << " | Мощь: " << myGuild.theStrongestMember()->getPower() << "\n";


	return 0;
}