#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

#define FNAME_I "D:\\bd15.dat\0" //имя файла с исходной базой
#define FNAME_R "D:\\bd25.dat\0" //имя файла с результатами поиска

void intro()
{
	cout << "\n\n\n\t            DATABASE";
	cout << "\n\n\t          РУКИ В РУКИ";
	cout << "\n\n\t    Сисетма управления МФО";
	cout << "\n\n\n\nВыполнил: студент уч. группы Z1411";
	cout << "\n\nВоробьев Н.А.";
	cin.get();
}

class account
{
	int idDogovora;
	char name[25];
	int birthY;
	char town[25];
	char telNubmer[11];
	char placeWork[30];
	double income;
	int deposit;
	char type;
	public:
		void create_account();	//функция для получения данных от пользователя
		void show_account() const;	//функция для отображения данных на экране
		void modify();	//функция для добавления новых данных
		void dep(int);	//функция для приема суммы и добавления к сумме баланса
		void draw(int);	//функция для приема суммы и вычитания из суммы баланса
		void report() const;	//функция для отображения данных в табличном формате
		int retacno() const;	//функция для возврата номера счета
		int retdeposit() const;	//функция для возврата суммы баланса
		char rettype() const;	//функция для возврата типа учетной записи
}; 

void account::create_account()
{
	cout << "\nВведите id индивидуального договора (6 цифр, должен совпадать с номером паспорта) :";
	cin >> idDogovora;
	cout << "\n\nВведите имя заёмщика : ";
	cin.ignore();
	cin.getline(name, 25);
	cout << "\nВведите год родения : ";
	cin >> birthY;
	cout << "\nВведите город проживания : ";
	cin.ignore();
	cin.getline(town, 25);
	cout << "\nВведите контактный номер телефона (в формате 89**) : ";
	cin.ignore();
	cin.getline(telNubmer, 11);
	cout << "\n\nВведите место работы (наименование организации): ";
	cin.ignore();
	cin.getline(placeWork, 30);
	cout << "\nВведите средний ежемесячный доход заёмщика (тыс. руб.) : ";
	cin >> income;
	cout << "\nВведите тип учетной записи (Снятие (W)/Накопление (A)) : "; //Введите тип учетной записи (C/S) 
	cin >> type;
	type = toupper(type);
	cout << "\nВведите сумму, вносимую на Л/С (тыс. руб.) : ";
	cin >> deposit;
	cout << "\n\n\nУчетная запись создана.";
}

void account::show_account() const
{
	cout << "\nAccount No. : " << idDogovora;//Номер учетной записи.
	cout << "\nAccount Holder Name : "; //Имя владельца учетной записи : 
	cout << name; 	//имя
	cout << "\nType of Account : " << type;	//тип учетной записи : 
	cout << "\nBalance amount : " << deposit;	//сумма баланса :
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
	cout << idDogovora << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account::retacno() const
{
	return idDogovora;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}

int create_bd(const char*, const char*); //создание БД
void create_user();	//функция для записи записи в двоичный файл
void display_sp(int);	//функция для отображения реквизитов учетной записи, предоставленных пользователем
void modify_account(int);	//функция для изменения записи файла
void delete_account(int);	//функция для удаления записи файла
void display_all();		//функция для отображения всех сведений об учетной записи
void deposit_withdraw(int, int); // функция для пополнения/снятия суммы с данного счета
void intro();	//функция вводного экрана
void operations_rko(); //функция операций РКО
void settings_bd(); // настройки БД

const char PR_R[] = "rb"; //признак открытия бинарного файла на чтение
const char PR_S[] = "r+b"; //признак открытия файла на чтение и запись
const char PR_W[] = "wb"; //признак открытия файла на запись
const char PR_A[] = "ab"; //признак открытия файла на добавление

int main()
{
	char ch;
	int num;
	char otv;
	char fname_i[20] = FNAME_I;
	char fname_r[20] = FNAME_R;
	setlocale(LC_ALL, "Russian");
	intro();
	do
	{
		system("cls");
		cout << "\n\n\n\tГлавное меню";
		cout << "\n\n\t01. Создать базу данных МФО";
		cout << "\n\n\t02. Добавить клиента в базу данных";//НОВАЯ УЧЕТНАЯ ЗАПИСЬ
		cout << "\n\n\t03. Сортировать базу данных по среднему еж-му доходу";
		cout << "\n\n\t04. Сортировать базу данных по местоположени клиентов";
		cout << "\n\n\t05. Операции РКО";
		cout << "\n\n\t06. Редактировать базу данных";
		cout << "\n\n\t07. Выход из программы";


		cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";//СПИСОК ВСЕХ ВЛАДЕЛЬЦЕВ УЧЕТНЫХ ЗАПИСЕЙ";

		cout << "\n\n\tВведите номер варианта (1-7) ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1': //создание базы данных
			if (create_bd(fname_i, PR_R)) {
				cout << " Файл базы данных владельцев яхт с именем " << fname_i;
				cout << " был создан раньше." << endl;
				cout << " Создаём файл с новым именем? [Y/N] ";
				while ((otv = getchar()) == '\n');
				if (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н') {
					cout << " Задайте имя создаваемого файла: ";
					cin >> fname_i;
				}
				else break;
			}
			else if (!create_bd(fname_i, PR_W)) {
				cout << "\n Ошибка открытия файла для записи" << endl;
				break;
			}
			cout << " Создаем базу " << fname_i << endl;
			getchar();
			create_user();
			cout << "Создание файла закончено." << endl;
			if (create_bd(fname_i, PR_R))
				cout << " База данных готова к работе" << endl;
			else cout << "база не создана" << endl;
			break;
			break;
		case '2': //добавления лкиента в бд
			create_user();
			break;


		case '4':
			cout << "\n\n\tВведите id индивидуального договора : "; cin >> num;//Введите номер учетной записи. : 
			display_sp(num);
			break;

		case '5':
			operations_rko();
			break;
		case '6':
			settings_bd();
			break;
		case '7':
			cout << "\n\n\tБлагодарим Вас за использование нашего ПО. До новых встреч!";//спасибо за использование системы управления банком
			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != '7');
	return 0;
}

void create_user()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
	outFile.close();
}

void display_sp(int n) 
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "Файл не может быть открыт! Нажмите любую клавишу...";
		return;
	}
	cout << "\nСВЕДЕНИЯ О БАЛАНСЕ\n";
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.retacno() == n)
		{
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\nВведенный id индивидуального договора - не существует.";
}

void modify_account(int n)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "Файл не может быть открыт! Нажмите любую клавишу...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			cout << "\n\nВведите актуальные данные учетной записи" << endl;//Введите новые данные учетной записи
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Учетная запись обновлена.";//Запись обновлена
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Учетная запись не найдена.";//Запись не найдена
}

void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";//Файл не удалось открыть !! Нажмите любую клавишу...
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.retacno() != n)
		{
			outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "\n\n\tRecord Deleted .."; //запись удалена
}

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";//Файл не удалось открыть !! Нажмите любую клавишу...
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";//СПИСОК ВЛАДЕЛЬЦЕВ УЧЕТНЫХ ЗАПИСЕЙ
	cout << "====================================================\n";
	cout << "A/c no.      NAME           Type  Balance\n";//номер             имя              тип баланса
	cout << "====================================================\n";
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";//Файл не удалось открыть !! Нажмите любую клавишу...
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			if (option == 1)
			{
				cout << "\n\n\tTO DEPOSITE AMOUNT ";//НА СУММУ ДЕПОЗИТА
				cout << "\n\nEnter The amount to be deposited";//Сумма, подлежащая внесению
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT ";//ДЛЯ ВЫВОДА СУММЫ 
				cout << "\n\nEnter The amount to be withdraw";//Введите сумму для вывода
				cin >> amt;
				int bal = ac.retdeposit() - amt;
				if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
					cout << "Insufficience balance";//Недостаточный баланс
				else
					ac.draw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";//запись обновлена 
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";//запись не найдена 
}

void operations_rko()
{
	char ch;
	int num;
	do {
		system("cls");
		cout << "\n\n\n\tОперации Расчетно-кассового обслуживания";//ГЛАВНОЕ МЕНЮ
		cout << "\n\n\t01. Внести денежные средства";
		cout << "\n\n\t02. Вывести денежные средства";//НОВАЯ УЧЕТНАЯ ЗАПИСЬ
		cout << "\n\n\t03. Запросить баланс";
		cout << "\n\n\t04. Вернуться в меню";
		cout << "\n\n\tВведите номер варианта (1-4): ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			cout << "\n\n\tВведите id договора : "; cin >> num;//Введите номер учетной записи. :
			deposit_withdraw(num, 1);
			break;
		case '2':
			cout << "\n\n\tВведите id договора : "; cin >> num;//Введите номер учетной записи. :
			deposit_withdraw(num, 2);
			break;
		case '3':
			cout << "\n\n\tВведите id договора : "; cin >> num;//Введите номер учетной записи. : 
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

void settings_bd()
{
	char ch;
	int num;
	do {
		system("cls");
		cout << "\n\n\n\tРедактирование базы данных";//ГЛАВНОЕ МЕНЮ
		cout << "\n\n\t01. Добавить учетную запись";
		cout << "\n\n\t02. Изменить учетную запись";//НОВАЯ УЧЕТНАЯ ЗАПИСЬ
		cout << "\n\n\t03. Удалить учетную запись";
		cout << "\n\n\t04. Вернуться в меню";
		cout << "\n\n\tВведите номер варианта (1-4): ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			create_user();
			break;
		case '2':
			cout << "\n\n\tВведите id договора : "; cin >> num;//Введите номер учетной записи. :
			modify_account(num);
			break;
		case '3':
			cout << "\n\n\tВведите id договора : "; cin >> num;//Введите номер учетной записи. : 
			delete_account(num);
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

int create_bd(const char* fname, const char* pr) {
	if (!(fopen(fname, pr)))
		return(0);
	return(1);
}