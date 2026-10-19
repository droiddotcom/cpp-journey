#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <cctype>


using namespace std;

struct Answers
{
	string text;
	string answer;
};


int main()
{

	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	vector<Answers> quiz;
	Answers tempQ;
	quiz.push_back({ "Сколько будет 2 + 2\n", "4" });
	quiz.push_back({ "\Sky color?\n", "blue" });
	quiz.push_back({ "\nWhat drink cow?\n", "water" });

	int score = 0;

	for (Answers q : quiz)
	{
		string userAsnwer;
		cout << q.text << "Ответ: ";
		getline(cin, userAsnwer);
		for (char& c : q.answer)
		{
			c = tolower(c);
		}
		for (char& c : userAsnwer)
		{
			c = tolower(c);
		}
		if (userAsnwer == q.answer)
		{
			cout << "Правильно!\n";
			score += 1;
		}
		else
		{
			cout << "Неверно!\n";
		}
	}

	cout << "Ваш результат: " << score << "\n";



	return 0;
}