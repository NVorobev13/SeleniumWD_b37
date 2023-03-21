#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;

int main() {
	setlocale(LC_ALL, "Rus");
	int pop_1, pop_2, pop_3;
	double sr_ariv, BON = .557;
	cout << "Попытка №1" << endl;
	cout << "Введите число от 11 до 99" << endl;
	cin >> pop_1;
	cout << "Попытка №2" << endl;
	cout << "Введите число от 101 до 199" << endl;
	cin >> pop_2;
	cout << "Попытка №3" << endl;
	cout << "Введите число от 201 до 299" << endl;
	cin >> pop_3;
	sr_ariv = (pop_1 + pop_2 + pop_3) / 3;
	cout << "Среднее арифмитическое равно: " << sr_ariv << endl;
	cout << "Бонус за набранное число: " << BON * sr_ariv << endl;
	return 0;
}