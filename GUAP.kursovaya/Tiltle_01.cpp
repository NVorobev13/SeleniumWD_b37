#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<cstdlib>

#define FNAME_B "Hands_in_Hand.dat"  //имя файла с исходной базой
#define FNAME_T "searchTown.dat"  //имя файла с результатами сортировки по городам
#define FNAME_D "Delete.dat"   //имя файла с результатами после удаления

using namespace std;

const char PR_R[] = "rb";            //признак открытия бинарного файла на чтение
const char PR_S[] = "r+b";           //признак открытия файла на чтение и запись

class trip {
public:
    int idDogovora;
    int birthY;
    char name[20];
    char town[20];
    char telNubmer[12];
    char placeWork[30];
    char type;
    double deposit;
    double income;
};

class account
{
    int idDogovora;
    int birthY;
    char name[20];
    char town[20];
    char telNubmer[12];
    char placeWork[30];
    char type;
    double deposit;
    double income;
public:
    void create_account();
    void show_account() const;
    void dep(double);
    void draw(double);
    void visual_table() const;
    void visual_sort_income(const char* fname) const;
    void visual_sort_town(const char* fname) const;
    void zag_vt() const;
    void zag_vsi() const;
    void zag_vst() const;
    int retidDogovora() const;
    double retdeposit() const;
    double retincome() const;
    char rettype() const;
    char rettown() const;
};

void account::create_account()
{
    int i;
    cout << endl << "\t";
    for (i = 1; i < 100; i++) {
        cout << "-";
    }
    cout << "\n\t|| Введите id индивидуального договора (6 цифр, должен совпадать с номером паспорта) : ";
    cin >> idDogovora;
    cout << "\t|| Введите имя заёмщика: ";
    cin.ignore();
    cin.getline(name, 25);
    cout << "\t|| Введите год рождения: ";
    cin >> birthY;
    cout << "\t|| Введите город проживания: ";
    cin.ignore();
    cin.getline(town, 20);
    cout << "\t|| Введите контактный номер телефона (в формате 89**): ";
    cin >> telNubmer;
    cout << "\t|| Введите место работы (вместо пробелов используйте '_'): ";
    cin >> placeWork;
    cout << "\t|| Введите средний ежемесячный доход заёмщика (тыс. руб.): ";
    cin >> income;
    cout << "\t|| Введите тип учетной записи (B (Bring_out) / I (Insert)): ";
    cin >> type;
    type = toupper(type);
    cout << "\t|| Введите сумму, вносимую на Л/С (тыс. руб.): ";
    cin >> deposit;
    cout << "\t";
    for (i = 1; i < 100; i++) {
        cout << "-";
    }
}

void account::show_account() const
{
    int i;
    cout << endl << "\t";
    for (i = 1; i < 55; i++) {
        cout << "-";
    }
    cout << "\n\t| ID индивидуального договора: " << idDogovora;
    cout << "\n\t| Имя заёмщика: " << name;
    cout << "\n\t| Год рождения: " << birthY;
    cout << "\n\t| Город проживания: " << town;
    cout << "\n\t| Контактный номер телефона: " << telNubmer;
    cout << "\n\t| Место работы: " << placeWork;
    cout << "\n\t| Средний ежемесячный доход: " << income;
    cout << "\n\t| Тип учетной записи (Bring_out (B)/Insert (I)): " << type;
    cout << "\n\t| Баланс учетной записи: " << deposit;
    cout << endl << "\t";
    for (i = 1; i < 55; i++) {
        cout << "-";
    }
}

void account::dep(double x)
{
    deposit += x;
}

void account::draw(double x)
{
    deposit -= x;
}

void account::visual_table() const
{
    cout << endl << "\t|";
    cout.width(13); cout << idDogovora << "|";
    cout.width(14); cout << name << "|";
    cout.width(14); cout << birthY << "|";
    cout.width(14); cout << town << "|";
    cout.width(20); cout << telNubmer << "|";
    cout.width(18); cout << placeWork << "|";
    cout.width(11); cout << income << "|";
    cout.width(8); cout << deposit << "|";
    cout.width(11); cout << type << "|";
}

void account::visual_sort_income(const char* fname) const {
    int i;
    account ship{};
    FILE* baza;
    baza = fopen(fname, PR_R);
    cout << "\n\n\n\t БАЗА ДАННЫХ МИКРО-ФИНАНСОВОЙ ОРГАНИЗАЦИИ 'Руки в Руки'\n\n";
    zag_vsi();
    while (fread(&ship, sizeof(ship), 1, baza) > 0) {
        cout << endl << "\t|";
        cout.width(11); cout << ship.income << "|";
        cout.width(13); cout << ship.idDogovora << "|";
        cout.width(14); cout << ship.name << "|";
        cout.width(14); cout << ship.birthY << "|";
        cout.width(14); cout << ship.town << "|";
        cout.width(20); cout << ship.telNubmer << "|";
        cout.width(18); cout << ship.placeWork << "|";
        cout.width(8); cout << ship.deposit << "|";
        cout.width(11); cout << ship.type << "|";
    }
    cout << endl << "\t";
    for (i = 1; i <= 133; i++) {
        cout << "-";
    }
    cout << "\n\n\t СОРТИРОВКА ПО СРЕДНЕМУ ЕЖЕМЕСЯЧНОМУ ДОХОДУ ЗАЁМЩИКА ЗАКОНЧЕНА.";
    cout << "\n\n\t Для продолжения, пожалуйста, нажмите <Enter>" << endl;
    fclose(baza);
    return;
}

void account::visual_sort_town(const char* fname) const {
    int i;
    account ship;
    FILE* baza;
    baza = fopen(fname, PR_R); //открываем файл на чтение
    cout << "\n\n\t БАЗА ДАННЫХ МИКРО-ФИНАНСОВОЙ ОРГАНИЗАЦИИ 'Руки в Руки'\n";
    zag_vst();
    while (fread(&ship, sizeof(ship), 1, baza) > 0) {
        cout << endl << "\t|";
        cout.width(14); cout << ship.town << "|";
        cout.width(13); cout << ship.idDogovora << "|";
        cout.width(14); cout << ship.name << "|";
        cout.width(14); cout << ship.birthY << "|";
        cout.width(20); cout << ship.telNubmer << "|";
        cout.width(18); cout << ship.placeWork << "|";
        cout.width(11); cout << ship.income << "|";
        cout.width(8); cout << ship.deposit << "|";
        cout.width(11); cout << ship.type << "|";
    }
    cout << endl << "\t";
    for (i = 1; i <= 133; i++) {
        cout << "-";
    }
    fclose(baza);
    return;
}

void account::zag_vt() const
{
    int i;
    cout << endl << "\t";
    for (i = 1; i <= 133; i++)
        cout << "-";
    cout << endl;

    cout << "\t| ID договора |" << " Имя заёмщика |" << " Год рождения |" << "    Город     |" << " Контактный телефон |" << "   Место работы   |" << " Еж. доход |" << " Баланс |" << " Тип счёта |" << endl;
    cout << "\t";
    for (i = 1; i <= 133; i++)
        cout << "-";
    return;
}

void account::zag_vsi() const
{
    int i;
    cout << endl << "\t";
    for (i = 1; i <= 133; i++)
        cout << "-";
    cout << endl;
    cout << "\t| Еж. доход |" << " ID договора |" << " Имя заёмщика |" << " Год рождения |" << "    Город     |" << " Контактный телефон |" << "   Место работы   |" << " Баланс |" << " Тип счёта |" << endl;
    cout << "\t";
    for (i = 1; i <= 133; i++)
        cout << "-";
    return;
}

void account::zag_vst() const
{
    int i;
    cout << endl << "\t";
    for (i = 1; i <= 133; i++)
        cout << "-";
    cout << endl;
    cout << "\t|    Город     |" << " ID договора |" << " Имя заёмщика |" << " Год рождения |" << " Контактный телефон |" << "   Место работы   |" << " Еж. доход |" << " Баланс |" << " Тип счёта |" << endl;
    cout << "\t";
    for (i = 1; i <= 133; i++)
        cout << "-";
    return;
}

int account::retidDogovora() const
{
    return idDogovora;
}

double account::retdeposit() const
{
    return deposit;
}

double account::retincome() const
{
    return income;
}

char account::rettype() const
{
    return type;
}

char account::rettown() const
{
    return town[19];
}

//объявление функции
void display_sp(const char* fname, int);                                      //функция для отображения реквизитов учетной записи, предоставленных пользователем
void modify_account(const char* fname, int);                                     //функция для изменения записи файла
void delete_account(const char* fname_b, const char* fname_d, int);                                //функция для удаления записи файла
void display_all(const char* fname);                                       //функция для отображения всех реквизитов счета
void settings_bd(const char* fname1, const char* fname2);                   //функция настройки БД   
void intro();                                             //функция вводного экрана
int proverka_file(const char* fname);                                                       //функция проверки наличия физического файла
void write_account(const char* fname);                                       //функция для записи записи в двоичный файл
void sort_income(const char* fname);                                                                  //функция сортировки заёмщиков по среднему ежемесячному доходу
void sort_town(const char* fname1, const char* fname2);                                               //функция сортировки заёмщиков по местоположению
void operations_rko(const char* fname);                                       //функция операций РКО
void deposit_withdraw(const char* fname, int, int);                                       //функция для внесения/снятия суммы для данного счета

int main()
{
    account ac{};
    char ch, otv;
    char fname_b[25] = FNAME_B;
    char fname_t[25] = FNAME_T;
    char fname_d[20] = FNAME_D;
    setlocale(LC_ALL, "Russian");
    intro();
    do
    {
        system("cls");
        cout << "\n\n\n\t Главное меню";
        cout << "\n\n\t 01. СОЗДАТЬ БАЗУ ДАННЫХ МФО";         //+++
        cout << "\n\n\t 02. СОЗДАТЬ АНКЕТУ ЗАЁМЩИКА";         //+++
        cout << "\n\n\t 03. СОРТИРОВКА ПО СРЕДНЕМУ ЕЖЕМЕСЯЧНОМУ ДОХОДУ ЗАЁМЩИКА";  //+++
        cout << "\n\n\t 04. СОРТИРОВКА ПО МЕСТОПОЛОЖЕНИЮ ЗАЁМЩИКА";      //---
        cout << "\n\n\t 05. РАСЧЕТНЫЕ БАНКОВСКИЕ ОПЕРАЦИИ";        //+++
        cout << "\n\n\t 06. РЕДАКТИРОВАТЬ БАЗУ ДАННЫХ ЗАЁМЩИКОВ";      //+++
        cout << "\n\n\t 07. ВЫХОД";              //+++
        cout << "\n\n\t Введите номер варианта (1-7) ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            
            if (proverka_file(fname_b)) {
                cout << "\n\t Создать файл с новым именем? [Y/N] ";
                while ((otv = getc(stdin)) == '\n');
                if (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н') {
                    cout << "\n\t Введи название базы данных МФО на латин. (необходимо также указать разширение .dat): ";
                    cin >> fname_b;
                }
                else {
                    cout << "\n\t База данных с новым именем - не создана." << endl;
                    cout << "\n\t Для возврата в главное меню, пожалуйста, нажмите <Enter>.";
                    break;
                }
            }
            else if (!(proverka_file(fname_b))) {
                cout << "\n\t Ошибка открытия файла для записи." << endl;
                break;
            }

            cout << "\n\t Создаем базу " << fname_b << endl;
            cout << "\n\t Добавьте первого клиента в Вашу базу данных.";
            getchar();
            write_account(fname_b);
            if (proverka_file(fname_b)) {
                cout << "\n\t База данных МФО готова к работе. Пожалуйста, нажмите <Enter>" << endl;
            }
            else {
                cout << "\n\t База данных - не создана." << endl;
            }
            break;
        case '2':
            write_account(fname_b);
            break;
        case '3':
            sort_income(fname_b);
            ac.visual_sort_income(fname_b);
            break;
        case '4':
            sort_town(fname_b, fname_t);
            ac.visual_sort_town(fname_t);
            cout << "\n\n\t СОРТИРОВКА ПО МЕСТОПОЛОЖЕНИЮ ЗАВЕРШЕНА.";
            cout << "\n\n\t Для продолжения, пожалуйста, нажмите <Enter>" << endl;
            break;

        case '5':
            operations_rko(fname_b);
            break;
        case '6':
            settings_bd(fname_b, fname_d);
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

void intro()
{
    int i;
    cout << endl << "\t";
    for (i = 1; i < 92; i++) {
        cout << "-";
    }
    cout << "\n\n\t|| \t\t\t\t\t   DATABASE \t\t\t\t\t ||";
    cout << "\n\n\t|| \t\t\t\t\t РУКИ В РУКИ \t\t\t\t\t ||";
    cout << "\n\n\t|| \t\t\t\t   Система управления МФО  \t\t\t\t ||";
    cout << "\n\n\t|| \t\t\t\t\t\t\t\t\t\t\t ||";
    cout << "\n\n\t|| Выполнил: студент учебной группы Z1411  \t\t\t\t\t\t ||";
    cout << "\n\n\t|| «Санкт-Петербургского государственного университета аэрокосмического приборостроения» ||";
    cout << "\n\n\t|| \t\t\t\t\t\t\t\t\t   Воробьев Н.А. ||";
    cout << endl << "\t";
    for (i = 1; i < 92; i++) {
        cout << "-";
    }
    cout << "\n\n\t *Для осуществления поставленных задач - нажмите <Enter>.";
    cin.get();
}

//функция для записи записи в двоичный файл
void write_account(const char* fname_b)
{
    char otv;
    account ac{};
    ofstream outFile;
    outFile.open(fname_b, ios::binary | ios::app);
    cout << "\n\t Создание анкеты заёмщика в базу МФО: " << fname_b;
    do {
        ac.create_account();
        outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
        cout << "\n\t УЧЁТНАЯ ЗАПИСЬ СОЗДАНА.\n";
        cout << "\n\n\t Создать ещё? [Y/N]: ";
        while ((otv = getc(stdin)) == '\n');
    } while (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н');
    cout << "\n\n\t Для продолжения, пожалуйста, нажмите <Enter>" << endl;
    outFile.close();
}

//функция для сортировки по возрастанию СРЕДНЕГО ЕЖЕМЕСЯЧНОГО ДОХОДА 
void sort_income(const char* fname)
{
    int i;
    int fl;
    account ppp, ship;
    FILE* baza;
    baza = fopen(fname, PR_S); //открываем файл на чтение и запись
    do {
        rewind(baza);
        fl = 0;
        for (i = 0; fread(&ship, sizeof(ship), 1, baza) > 0; i += sizeof(ship), fseek(baza, i, SEEK_SET)) {
            if (fread(&ppp, sizeof(ship), 1, baza) > 0) {
                if (ship.retincome() > ppp.retincome()) {
                    fseek(baza, i, SEEK_SET); //позиция i от НАЧАЛА файла
                    fwrite(&ppp, sizeof(ship), 1, baza);
                    fwrite(&ship, sizeof(ship), 1, baza);
                    fl = 1;
                }
            }
        }
    } while (fl);
    fclose(baza);
    return;
}

//функция для сортировки по местоположению
void sort_town(const char* fname1, const char* fname2) {
    char searchTown[20];
    trip ship{};
    ifstream inFile;
    ofstream outFile;
    inFile.open(fname1, ios::binary);
    if (!inFile)
    {
        cout << "\n\t Ошибка открытия файла для чтения и записи! Press any Key...";
        return;
    }
    outFile.open(fname2, ios::binary);
    cout << "\n\t Введите название города: : ";
    cin >> searchTown;
    while (inFile.read(reinterpret_cast<char*> (&ship), sizeof(trip))) {
        if (strncmp(ship.town, searchTown, 20) == 0) {
            outFile.write(reinterpret_cast<char*> (&ship), sizeof(trip));
        }
    }
    inFile.close();
    outFile.close();
    return;
}

//функция для осуществелния рассчетно-кассовых операций
void operations_rko(const char* fname_b)
{
    int num;
    char ch;
    do {
        system("cls");
        cout << "\n\n\n\t РАСЧЕТНЫЕ БАНКОВСКИЕ ОПЕРАЦИИ ";
        cout << "\n\n\t 01. ПОПОЛНИТЬ ЛИЦЕВОЙ СЧЁТ.";
        cout << "\n\n\t 02. СНЯТЬ С ЛИЦЕВОГО СЧЁТА.";
        cout << "\n\n\t 03. ВЫВЕСТИ БАЛАНС НА ЭКРАН.";
        cout << "\n\n\t 04. ВЕРНУТЬСЯ В ГЛАВНОЕ МЕНЮ.";
        cout << "\n\n\n\t Введите номер варианта (1-4): ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            cout << "\n\t Введите ID Вашего договора: ";
            cin >> num;
            deposit_withdraw(fname_b, num, 1);
            break;
        case '2':
            cout << "\n\t Введите ID Вашего договора: ";
            cin >> num;
            deposit_withdraw(fname_b, num, 2);
            break;
        case '3':
            cout << "\n\t Введите ID Вашего договора: ";
            cin >> num;
            display_sp(fname_b, num);
            break;
        case '4':
            cout << "\n\n\t Для продолжения, пожалуйста, нажмите <Enter> 3 раза." << endl;
            break;
        }
        cin.ignore();
        cin.get();
    } while (ch != '4');
    return;
}

//функция пополнения / списания денежных средств с лицевого счета
void deposit_withdraw(const char* fname, int num, int option)
{
    double amt;
    bool found = false;
    account ac{};
    fstream File;
    File.open(fname, ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "\n\t Ошибка открытия файла для чтения и записи! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char*> (&ac), sizeof(account));
        if (ac.retidDogovora() == num)
        {
            ac.show_account();
            if (option == 1)
            {
                cout << "\n\n\t\t ПОПОЛНЕНИЕ ЛИЦЕВОГО СЧЁТА ЗАЁМЩИКА ";
                cout << "\n\n\t Введите сумму, на которую хотите произвести пополнение: ";
                cin >> amt;
                ac.dep(amt);
                cout << "\n\t\t УЧЁТНАЯ ЗАПИСЬ ЗАЁМЩИКА ОБНОВЛЕНА.";
            }
            if (option == 2)
            {
                cout << "\n\n\t\t ВЫВОД СРЕДСТВ С ЛИЦЕВОГО СЧЁТА ЗАЁМЩИКА ";
                cout << "\n\n\t Введите сумму, на которую хотите произвести вывод средств: ";
                cin >> amt;
                double bal = ac.retdeposit() - amt;
                if ((bal < 5 && ac.rettype() == 'B') || (bal < 25 && ac.rettype() == 'I')) {
                    cout << "\n\t *Для данной операции недостаточно денежных средств.\n\t **Пожалуйста, убедитесь в корректности запроса и попробуйте еще раз!";
                }
                else {
                    ac.draw(amt);
                    cout << "\n\t\t УЧЁТНАЯ ЗАПИСЬ ЗАЁМЩИКА ОБНОВЛЕНА.";
                }
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*> (&ac), sizeof(account));

            cout << "\n\n\t Для продолжения - нажмите <Enter>.";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\t Ошибка чтения файла. Приносим свои извинения! ";
}

//функция для отображения реквизитов учетной записи, предоставленных пользователем
void display_sp(const char* fname_b, int n)
{
    account ac{};
    bool flag = false;
    ifstream inFile;
    inFile.open(fname_b, ios::binary);
    if (!inFile)
    {
        cout << "\n\t Ошибка открытия файла для записи! Press any Key...";
        return;
    }
    cout << "\n\t СВЕДЕНИЯ О БАЛАНСЕ ЗАЁМЩИКОВ\n";

    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
    {
        if (ac.retidDogovora() == n)
        {
            ac.show_account();
            flag = true;
            cout << "\n\t Для продолжения - нажмите <Enter>.";
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\t Данный id договора - не существует.";
}

//функция для НАСТРОЙКИ БАЗЫ ДАННЫХ
void settings_bd(const char* fname1, const char* fname2)
{
    char ch;
    int num;

    do {
        system("cls");
        cout << "\n\n\n\t РЕДАКТИРОВАНИЕ БАЗЫ ДАННЫХ ЗАЁМЩИКОВ";
        cout << "\n\n\t 01. ВЫВЕСТИ СПИСОК ВСЕХ ЗАЁМЩИКОВ.";
        cout << "\n\n\t 02. ДОБАВИТЬ УЧЁТНУЮ ЗАПИСЬ ЗАЁМЩИКА.";
        cout << "\n\n\t 03. ИЗМЕНИТЬ УЧЁТНУЮ ЗАПИСЬ ЗАЁМЩИКА.";
        cout << "\n\n\t 04. УДАЛИТЬ УЧЁТНУЮ ЗАПИСЬ ЗАЁМЩИКА.";
        cout << "\n\n\t 05. ВЕРНУТЬСЯ В МЕНЮ." << endl;
        cout << "\n\t Введите номер варианта (1-5): ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            display_all(fname1);
            break;
        case '2':
            cout << "\n\t Добавляем записи в файл " << fname1 << endl;
            write_account(fname1);
            cout << "\n\n\t **Файл базы данных успешно обновлен.";
            break;
        case '3':
            cout << "\n\t Введите id договора : "; cin >> num;
            modify_account(fname1, num);
            break;
        case '4':
            cout << "\n\t Введите id договора : "; cin >> num;
            delete_account(fname1, fname2, num);
            break;
        case '5':
            cout << "\n\t Для продолжения - нажмите <Enter> 3 раза." << endl;
            break;
        }
        cin.ignore();
        cin.get();
    } while (ch != '5');
    return;
}

//функция для отображения всех реквизитов счета
void display_all(const char* fname)
{
    int i;
    account ac{};
    ifstream inFile;
    inFile.open(fname, ios::binary);
    if (!inFile)
    {
        cout << " Ошибка открытия файла для записи! Press any Key...";
        return;
    }
    cout << "\n\n\t\t БАЗА ДАННЫХ ЗАЁМЩИКОВ: " << fname << "\n";
    ac.zag_vt();
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
    {
        ac.visual_table();
    }
    cout << endl << "\t";
    for (i = 1; i <= 133; i++) {
        cout << "-";
    }
    cout << "\n\n\t *Для продолжения - нажмите <Enter>." << endl;
    inFile.close();
}

//функция для изменения записи файла
void modify_account(const char* fname, int n)
{
    bool found = false;
    account ac;
    fstream File;
    File.open(fname, ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "\n\t Ошибка открытия файла для записи! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char*> (&ac), sizeof(account));
        if (ac.retidDogovora() == n)
        {
            ac.show_account();
            cout << "\n\n\t Введите актуальные данные учётной записи" << endl;
            ac.create_account();
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*> (&ac), sizeof(account));
            cout << "\n\n\t Учётная запись - обновлена.";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n\t Учётная запись не найдена. ";
}

//функция удаления записанного файла 
void delete_account(const char* fname1, const char* fname2, int n)
{
    account ac{};
    ifstream inFile;
    ofstream outFile;
    inFile.open(fname1, ios::binary);
    if (!inFile)
    {
        cout << "\n\t Ошибка открытия файла для чтения и записи! Press any Key...";
        return;
    }
    outFile.open(fname2, ios::binary);
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
    remove(fname1);
    rename(fname2, fname1);
    cout << "\n\t УЧЁТНАЯ ЗАПИСЬ ПО ДОГОВОРУ " << n << " - УДАЛЕНА. \n";
    display_all(fname1);
}

//функция проверки наличия физического файла
int proverka_file(const char* fname) {
    fstream File;
    File.open(fname, ios::binary | ios::in | ios::out);
    if (!File) {
        return 0;
    }
    return 1;
}