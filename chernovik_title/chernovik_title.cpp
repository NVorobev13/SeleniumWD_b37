#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>

using namespace std;


												//***************************************************************
												//                   КЛАСС, ИСПОЛЬЗУЕМЫЙ В ПРОЕКТЕ
												//****************************************************************


class account
{
	int idDogovora;
	char name[20];
	double deposit;
	char type;
	int birthY;
	char town[25];
	char telNubmer[11];
	char placeWork[30];
	double income;
	public:
		void create_account();					//функция для получения данных от пользователя
		void show_account() const;				//функция для отображения данных на экране
		void modify();							//функция для добавления новых данных
		void dep(int);							//функция для принятия суммы и добавления к сумме баланса
		void draw(int);							//функция для принятия суммы и вычитания из суммы баланса
		void report() const;					//функция для отображения данных в табличном формате
		double retdeposit() const;					//функция для возврата суммы баланса
		char rettype() const;					//функция для возврата типа счета
		int retidDogovora() const;				//функция для возврата id договора
		int retbirthY() const;					//функция для возврата года рождения
		double retincome() const;				//функция для возврата среднего заработка 
};												

void account::create_account()
{
	cout << " Введите id индивидуального договора (6 цифр, должен совпадать с номером паспорта) : ";
	cin >> idDogovora;
	cout << " Введите имя заёмщика : ";
	cin.ignore();
	cin.getline(name, 25);
	cout << " Введите год родения: ";
	cin >> birthY;
	cout << " Введите город проживания: ";
	cin.ignore();
	cin.getline(town, 25);
	cout << " Введите контактный номер телефона (в формате 89**): ";
	cin.ignore();
	cin.getline(telNubmer, 11);
	cout << " Введите место работы (наименование организации): ";
	cin.ignore();
	cin.getline(placeWork, 30);
	cout << " Введите средний ежемесячный доход заёмщика (тыс. руб.): ";
	cin >> income;
	cout << " Введите тип учетной записи (Снятие (W)/Накопление (A)): "; //Введите тип учетной записи (C/S) 
	cin >> type;
	type = toupper(type);
	cout << " Введите сумму, вносимую на Л/С (тыс. руб.): ";
	cin >> deposit;
	cout << "\n Учетная запись создана.\n" << endl;
}

void account::show_account() const
{
	cout << "\n Id индивидуального договора: " << idDogovora;
	cout << "\n Имя заёмщика: " << name;
	cout << "\n Год рождения: " << birthY;
	cout << "\n Город проживания: " << town;
	cout << "\n Контактный номер телефона: " << telNubmer;
	cout << "\n Место работы: " << placeWork;
	cout << "\n Средний ежемесячный доход: " << income;
	cout << "\n Тип учетной записи (Снятие (W)/Накопление (A)): " << type;
	cout << "\n Баланс учетной записи: " << deposit;
}

void account::modify()
{
	cout << "\nВведите id индивидуального договора (6 цифр, должен совпадать с номером паспорта) :";
	cin >> idDogovora;
	cout << "\n\nВведите актуальное имя заёмщика : ";
	cin.ignore();
	cin.getline(name, 25);
	cout << "\nВведите актуальный год родения : ";
	cin >> birthY;
	cout << "\nВведите актуальный город проживания : ";
	cin.ignore();
	cin.getline(town, 25);
	cout << "\nВведите актуальный контактный номер телефона (в формате 89**) : ";
	cin.ignore();
	cin.getline(telNubmer, 11);
	cout << "\n\nВведите актуальное место работы (наименование организации): ";
	cin.ignore();
	cin.getline(placeWork, 30);
	cout << "\nВведите средний ежемесячный доход заёмщика (тыс. руб.) : ";
	cin >> income;
	cout << "\nВведите тип учетной записи (Снятие (W)/Накопление (A)) : "; //Введите тип учетной записи (C/S) 
	cin >> type;
	type = toupper(type);
	cout << "\nВведите сумму, вносимую на Л/С (тыс. руб.) : ";
	cin >> deposit;
}

void account::dep(int x)
{
	deposit += x;
}

void account::draw(int x)
{
	deposit -= x;
}

void account::report() const
{
	cout << "| " << idDogovora << setw(4)
		<< " | " << name << setw(4) 
		<< " | " << birthY << setw(4) 
		<< " | " << town << setw(4) 
		<< " | " << telNubmer << setw(4) 
		<< " | " << placeWork << setw(4) 
		<< " | " << type << setw(4) 
		<< " | " << income << setw(4) << endl;
}

int account::retidDogovora() const
{
	return idDogovora;
}

double account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}

int account::retbirthY() const
{
	return birthY;
}

double account::retincome() const
{
	return income;
}



												//***************************************************************
												//			объявление функции
												//****************************************************************
void create_database(string name_file, string tip);
void operations_rko();							//функция операций РКО
void settings_bd(string name_file, string tip);								//функция настройки БД
void zag1();

void write_account();							//функция для записи записи в двоичный файл
void display_sp(int);							//функция для отображения реквизитов учетной записи, предоставленных пользователем
void modify_account(int);						//функция для изменения записи файла
void delete_account(int);						//функция для удаления записи файла
void display_all(string name_file, string tip);								//функция для отображения всех реквизитов счета
void deposit_withdraw(int, int);				//функция для внесения/снятия суммы для данного счета
void intro();									//функция вводного экрана

char otv;


int main()
{
	setlocale(LC_ALL, "Russian");
	char ch;
	intro();
	do
	{
		system("cls");
		cout << "\n\n\n\t Главное меню";
		cout << "\n\n\t 01. СОЗДАТЬ БАЗУ ДАННЫХ МФО";
		cout << "\n\n\t 02. СОЗДАТЬ АНКЕТУ ЗАЁМЩИКА";
		cout << "\n\n\t 03. СОРТИРОВКА ПО СРЕДНЕМУ ЕЖЕМЕСЯЧНОМУ ДОХОДУ ЗАЁМЩИКА";
		cout << "\n\n\t 04. СОРТИРОВКА ПО МЕСТОПОЛОЖЕНИЮ ЗАЁЁМЩИКА";
		cout << "\n\n\t 05. РАСЧЕТНЫЕ БАНКОВСКИЕ ОПЕРАЦИИ";
		cout << "\n\n\t 06. РЕДАКТИРОВАТЬ БАЗУ ДАННЫХ ЗАЁМЩИКОВ";
		cout << "\n\n\t 07. ВЫХОД";
		cout << "\n\n\t Введите номер варианта (1-7) ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			//create_database(name_file, tip);
			break;
		case '2':
			write_account();
			break;
		case '3':
			
			break;
		case '4':
			
			break;
		case '5':
			operations_rko();
			break;
		case '6':
			//settings_bd(name_file, tip);
			break;


		case '7':
			cout << "\n\n\tБлагодарим Вас за использование нашего ПО. \n\n\t\t\tДо новых встреч!";
			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != '7');
	return 0;
}


												//*******************************************************************************************
												//    		функция для настройки базы данных
												//*******************************************************************************************
void settings_bd(string name_file, string tip) {
	char ch;
	int num;
	do {
		system("cls");
		cout << "\n\n\n\t РЕДАКТИРОВАНИЕ БАЗЫ ДАННЫХ ЗАЁМЩИКОВ";
		cout << "\n\n\t 01. Вывести список всех заёмщиков";
		cout << "\n\n\t 02. Добавить учетную запись заёщика";
		cout << "\n\n\t 03. Изменить учетную запись заёмщика";//НОВАЯ УЧЕТНАЯ ЗАПИСЬ
		cout << "\n\n\t 05. Удалить учетную запись заёмщика";
		cout << "\n\n\t 05. Вернуться в меню" << endl;
		cout << "\n\t Введите номер варианта (1-5): ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			display_all(name_file, tip);
			break;
		case '2':
			write_account();
			break;
		case '3':
			cout << "\n\n\tВведите id договора : "; cin >> num;
			modify_account(num);
			break;
		case '4':
			cout << "\n\n\tВведите id договора : "; cin >> num;
			delete_account(num);
			break;
		case '5':
			//main();
			break;
		}
		cin.ignore();
		cin.get();
	} while (ch != '5');
	return;
}

												//***************************************************************
												//			функция для записи записи в двоичный файл
												//****************************************************************

void create_database(string name_file, string tip)
{		
	account ac;
	ofstream outFile;
	cout << " Назови базу данных: ";
	cin >> name_file;
	tip = name_file + tip;


	outFile.open(tip, ios::binary | ios::app);

	ac.create_account();
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));

	outFile.close();
	
}


												//***************************************************************
												//			функция для записи записи в двоичный файл
												//****************************************************************

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
	outFile.close();
}

												//*******************************************************************************************
												//    		функция РАСЧЕТНЫЕ БАНКОВСКИЕ ОПЕРАЦИИ
												//*******************************************************************************************

void operations_rko()
{
	char ch;
	int num;
	do {
		system("cls");
		cout << "\n\n\n\t РАСЧЕТНЫЕ БАНКОВСКИЕ ОПЕРАЦИИ ";
		cout << "\n\n\t 01. ПОПОЛНИТЬ ЛИЦЕВЛЙ СЧЁТ";
		cout << "\n\n\t 02. СНЯТЬ С ЛИЦЕВОГО СЧЁТА";
		cout << "\n\n\t 03. ВЫВЕСТИ БАЛАНС НА ЭКРАН";
		cout << "\n\n\t 04. ВЕРНУТЬСЯ В ГЛАВНОЕ МЕНЮ" << endl;
		cout << "\n\n\t Введите номер варианта (1-4): ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			cout << "\n\n\t Введите id договора : "; cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '2':
			cout << "\n\n\t Введите id договора : "; cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '3':
			cout << "\n\n\t Введите id договора : "; cin >> num;
			display_sp(num);
			break;
		case '4':
			main();
			break;
		}
		cin.ignore();
		cin.get();
	} while (ch != '4');
	return;
}



												//*******************************************************************************************
												//    		функция для отображения реквизитов учетной записи, предоставленных пользователем
												//*******************************************************************************************

void display_sp(int n)
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << " Ошибка открытия файла для записи! Press any Key...";
		return;
	}
	cout << "\n\t СВЕДЕНИЯ О БАЛАНСЕ ЗАЁМЩИКОВ\n";

	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.retidDogovora() == n)
		{
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\t Данный id договора - не существует.";
}


												//***************************************************************
												//    		функция для изменения записи файла
												//****************************************************************

void modify_account(int n)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << " Ошибка открытия файла для записи! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retidDogovora() == n)
		{
			ac.show_account();
			cout << "\n\n Введите актуальные данные уч`тной записи" << endl;
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Учетная запись обновлена.";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Учетная запись не найдена. ";
}

												//***************************************************************
												//    		функция для удаления записи файла
												//****************************************************************


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << " Ошибка открытия файла для записи! Press any Key...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.retidDogovora() != n)
		{
			outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();



	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "\n\n\t Учётная запись удалена.";
}

												//***************************************************************
												//    		функция для отображения всех реквизитов счета
												//****************************************************************

void display_all(string name_file, string tip)
{
	account ac;
	ifstream inFile;
	inFile.open(tip, ios::binary);
	if (!inFile)
	{
		cout << " Ошибка открытия файла для записи! Press any Key...";
		return;
	}
	cout << "\n\n\t\t БАЗА ДАННЫХ ЗАЁМЩИКОВ \n\n";
	zag1();

	
	cout << "\n====================================================\n";
	cout << "A/c no.      NAME           Type  Balance\n";
	cout << "====================================================\n";
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

void zag1() {
	int i;
	for (i = 1; i <= 80; i++) {
		cout << "--";
	}
	cout << endl;
	cout << "| ID договора |" << " Имя заёмщика |" << " Год рождения |" << " Город |" << " Контактный телефон |" << " Место работы |" << " Счёт|" << " Еж. доход |" << endl;
	for (i = 1; i <= 80; i++) {
		cout << "--";
	}
	return;
}




												//***************************************************************
												//    		функция для внесения/снятия суммы для данного счета
												//****************************************************************

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "Ошибка открытия файла для записи! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retidDogovora() == n)
		{
			ac.show_account();
			if (option == 1)
			{
				cout << "\n\n\t ПОПОЛНЕНИЕ ЛИЦЕВОГО СЧЁТА ";
				cout << "\n\n Введите сумму, подлежащую внесению: ";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\t СНЯТИЕ С ЛИЦЕВОГО СЧЁТА ";
				cout << "\n\n Введите сумму, подлежащую снятию: ";
				cin >> amt;
				int bal = ac.retdeposit() - amt;
				if ((bal < 500 && ac.rettype() == 'A') || (bal < 1000 && ac.rettype() == 'W'))
					cout << " Недостатоно денежных средств!";
				else
					ac.draw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t КАРТОЧКА ЗАЁМЩИКА ОБНОВЛЕНА! ";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Нет возможности внести изменения! ";
}


												//***************************************************************
												//    		функция вводного экрана
												//****************************************************************


void intro()
{
	cout << "\n\n\n\t            DATABASE";
	cout << "\n\n\t          РУКИ В РУКИ";
	cout << "\n\n\t    Система управления МФО";
	cout << "\n\n\n\nВыполнил: студент уч. группы Z1411";
	cout << "\n\nВоробьев Н.А.";
	cin.get();
}

												//***************************************************************
												//    			Конец проекта
												//***************************************************************