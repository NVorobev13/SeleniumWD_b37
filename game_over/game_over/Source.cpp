//Game over
//Первая программа на C++
#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, "Russian");
	int a;
	cout << "Введите номер книжной полки: " << endl;
	cin >> a;
	cout << "На полке " << a << " - 20 книг." << endl;
	return 0;
}