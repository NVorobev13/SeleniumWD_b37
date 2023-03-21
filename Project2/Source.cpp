#include <stdio.h>
#include <string.h>
#include<fstream>
#include<cctype>
#include<iomanip>
#include <iostream>
#define FNAME_B "Hands_in_Hand.dat" //имя файла с исходной базой
#define FNAME_T "searchTown.dat" //имя файла с результатами поиска
#define FNAME_ID "searchID.dat" //имя файла с результатами поиска

using namespace std;

void intro();	//функция вводного экрана
int proverka_file(const char*, const char*); //проверка наличия файла
void dobavka(const char* fname);

void zag1();
void zag2();
void zag3();
void prosmotrbd1(const char* fname);
void prosmotrbd2(const char* fname);
void prosmotrbd3(const char* fname);
void sort_town(const char* fname1, const char* fname2);
void sort_income(const char* fname);
void operations_rko(const char* fname1, const char* fname2); //функция операций РКО
void settings_bd();
void sort_ID(const char* fname_i, const char* fname2);		//функция для отображения реквизитов учетной записи, предоставленных пользователем
void sort_title(const char* fname);
void deposit_withdraw(const char* fname, int n, int option);

const char PR_R[] = "rb"; //признак открытия бинарного файла на чтение
const char PR_S[] = "r+b"; //признак открытия файла на чтение и запись
const char PR_W[] = "wb"; //признак открытия файла на запись
const char PR_A[] = "ab"; //признак открытия файла на добавление

typedef struct {
    char title[15]; //Название яхты
    char owner[15]; //Имя владельца
    double lenght;   //длинна  (м.)
    double cost;   //Стоимсоть (млн.$)
    int yearsOld; //Год застройки 

    char idDogovora[7];
    int birthY;
    char name[20];
    char town[25];
    char telNubmer[12];
    char placeWork[30];
    char type[12];
    double deposit;
    double income;

}
trip;

class account {
public:
    double deposit;
    void dep(int);
    void draw(int);
    void show_account() const;
    char idDogovora[7];
    int birthY;
    char name[20];
    char town[25];
    char telNubmer[12];
    char placeWork[30];
    char type[12];
    double income;
};

void account::dep(int x)
{
    deposit += x;
}

void account::draw(int x)
{
    deposit -= x;
}

void account::show_account() const
{
    int i;
    cout << endl << "\t";
    for (i = 1; i < 55; i++) {
        cout << "-";
    }
    cout << "\n\t| Id индивидуального договора: " << idDogovora;
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

void intro()
{
    cout << "\n\n\n\t            DATABASE";
    cout << "\n\n\t          РУКИ В РУКИ";
    cout << "\n\n\t    Система управления МФО";
    cout << "\n\n\n\nВыполнил: студент уч. группы Z1411";
    cout << "\n\nВоробьев Н.А.";
    cin.get();
}

int main() {
    {
        char otv;
        char fname_b[25] = FNAME_B;
        char fname_t[25] = FNAME_T;
        char fname_id[25] = FNAME_ID;

        setlocale(LC_ALL, "Russian");
        char ch;
        intro();
        do
        {
            system("cls");
            cout << "\n\n\n\t Главное меню";
            cout << "\n\n\t 01. СОЗДАТЬ БАЗУ ДАННЫХ МФО";                               //+++
            cout << "\n\n\t 02. СОЗДАТЬ АНКЕТУ ЗАЁМЩИКА";                               //+++
            cout << "\n\n\t 03. СОРТИРОВКА ПО СРЕДНЕМУ ЕЖЕМЕСЯЧНОМУ ДОХОДУ ЗАЁМЩИКА";   //+++
            cout << "\n\n\t 04. СОРТИРОВКА ПО МЕСТОПОЛОЖЕНИЮ ЗАЁМЩИКА";                 //+++
            cout << "\n\n\t 05. РАСЧЕТНЫЕ БАНКОВСКИЕ ОПЕРАЦИИ";                         //
            cout << "\n\n\t 06. РЕДАКТИРОВАТЬ БАЗУ ДАННЫХ ЗАЁМЩИКОВ";                   //
            cout << "\n\n\t 07. ВЫХОД" << endl;                                         //+++
            cout << "\n\n\t Введите номер варианта (1-7) ";
            cin >> ch;
            system("cls");
            switch (ch)
            {
            case '1':
                if (proverka_file(fname_b, PR_R)) {
                    cout << " Файл базы данных МФО с именем " << fname_b;
                    cout << " был создан ранее." << endl;
                    cout << " Создать файл с новым именем? [Y/N] ";
                    while ((otv = getc(stdin)) == '\n');
                    if (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н') {
                        cout << " Введи название базы данных МФО на латин. (необходимо также указать разширение .dat): ";
                        cin >> fname_b;
                    }
                    else if (otv == 'N' || otv == 'n' || otv == 'Т' || otv == 'т')
                    {
                        cout << "\n Для возврата в главное меню, пожалуйста, нажмите <Enter>.";
                        int main();
                        break;
                    }
                    else {
                        cout << "\n Мы не смогли распознать Ваш ответ. Возращаем Вас в Главное меню." << endl;
                        int main();
                        break;
                    }
                }
                if (!proverka_file(fname_b, PR_W)) {
                    cout << "\n Ошибка открытия файла для записи." << endl;
                    break;
                }
                cout << " Создаем базу " << fname_b << endl;
                cout << " Вы хотите произвести запись в созданную базу? [Y/N]: ";
                while ((otv = getc(stdin)) == '\n');
                if (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н') {
                    dobavka(fname_b);
                    break;
                }
                else if (otv == 'N' || otv == 'n' || otv == 'Т' || otv == 'т') {
                    cout << "\n Для возврата в главное меню, пожалуйста, нажмите <Enter>.";
                    int main();
                    break;
                }
                else {
                    cout << "\n Мы не смогли распознать Ваш ответ. Возращаем Вас в Главное меню." << endl;
                    int main();
                    break;
                }
                cout << "\n Создание файла закончено." << endl;
                if (proverka_file(fname_b, PR_R)) {
                    cout << " База данных МФО готова к работе. Пожалуйста, нажмите <Enter>" << endl;
                }
                else {
                    cout << "\n База не создана." << endl;
                }
                break;

            case '2':
                if (proverka_file(fname_b, PR_R)) {
                    cout << " Файл базы данных МФО с именем " << fname_b;
                    cout << " был создан ранее.";
                    cout << "\n Продолжить заполнение заполнее в данном файле? [Y/N]: ";

                    while ((otv = getc(stdin)) == '\n');
                    if (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н') {
                        dobavka(fname_b);
                        break;
                    }
                    else if (otv == 'N' || otv == 'n' || otv == 'Т' || otv == 'т') {
                        cout << " Задайте имя ранее создаваемого файла (необходимо также указать разширение .dat): ";
                        cin >> fname_b;
                        if (!proverka_file(fname_b, PR_R)) {
                            cout << " Такая база данных не создавалась." << endl;
                            cout << " \nСоздаём новый файл базы данных." << endl;
                            cout << " Введи название базы данных МФО на латин. (необходимо также указать разширение .dat): ";
                            cin >> fname_b;
                            cout << " Хотите продолжить заполнение базы данных? [Y/N]: ";

                            while ((otv = getc(stdin)) == '\n');
                            if (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н') {
                                dobavka(fname_b);
                                break;
                            }
                            else if (otv == 'N' || otv == 'n' || otv == 'Т' || otv == 'т')
                            {
                                cout << "\n Для возврата в главное меню, пожалуйста, нажмите <Enter>.";
                                int main();
                                break;
                            }
                            else {
                                cout << "\n Мы не смогли распознать Ваш ответ. Возращаем Вас в Главное меню." << endl;
                                int main();
                                break;
                            }
                        }
                    }
                    else {
                        cout << "\n Мы не смогли распознать Ваш ответ. Возращаем Вас в Главное меню." << endl;
                        int main();
                        break;
                    }
                }
                cout << " Добавляем записи в файл " << fname_b << endl;
                dobavka(fname_b);
                cout << "\n Файл базы данных успешно обновлен.";
                break;

            case '3':
                if (!proverka_file(fname_b, PR_S)) {
                    cout << "\n Ошибка открытия файла для чтения и записи" << endl;
                    break;
                }
                sort_income(fname_b);
                prosmotrbd1(fname_b);
                cout << "\n\n\t СОРТИРОВКА ПО СРЕДНЕМУ ЕЖЕМЕСЯЧНОМУ ДОХОДУ ЗАЁМЩИКА ЗАКОНЧЕНА.";
                cout << "\n\n\t Для продолжения, пожалуйста, нажмите <Enter>" << endl;
                break;

            case '4':
                if (!proverka_file(fname_b, PR_R)) {
                    cout << "\n Ошибка открытия файла для чтения" << endl;
                    break;
                }
                if (!proverka_file(fname_t, PR_W)) {
                    cout << "\n Ошибка открытия файла для записи" << endl;
                    break;
                }
                sort_town(fname_b, fname_t);
                prosmotrbd2(fname_t);
                cout << "\n\n\t СОРТИРОВКА ПО МЕСТОПОЛОЖЕНИЮ ЗАЁМЩИКА ЗАКОНЧЕНА.";
                cout << "\n\n\t Для продолжения, пожалуйста, нажмите <Enter>" << endl;
                break;

            case '5':
                operations_rko(fname_b, fname_id);
                break;

            case '6':
                settings_bd();
                break;

            case '11':
                if (!proverka_file(fname_b, PR_S)) {
                    cout << "\n Ошибка открытия файла для чтения и записи" << endl;
                    break;
                }
                sort_title(fname_b);
                cout << "\n Сортировка по названию яхт закончена.";
                break;



            case '8':
                if (!proverka_file(fname_b, PR_R)) {
                    cout << "\n Ошибка открытия файла для чтения" << endl;
                    break;
                }
                prosmotrbd1(fname_b);
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
}

//Добавление новых элементов в базу данных
void dobavka(const char* fname) {
    char otv;
    //char type;
    trip ship{};
    FILE* baza;
    baza = fopen(fname, PR_A);
    rewind(baza);
    do {
        cout << "\n Введите id индивидуального договора (6 цифр, должен совпадать с номером паспорта) : ";
        cin >> ship.idDogovora;
        cout << " Введите имя заёмщика: ";
        cin.ignore();
        cin.getline(ship.name, 25);
        cout << " Введите год родения: ";
        cin >> ship.birthY;
        cout << " Введите город проживания: ";
        cin.ignore();
        cin.getline(ship.town, 25);
        cout << " Введите контактный номер телефона (в формате 89**): ";
        cin >> ship.telNubmer;
        cout << " Введите место работы (наименование организации): ";
        cin >> ship.placeWork;
        cout << " Введите средний ежемесячный доход заёмщика (тыс. руб.): ";
        cin >> ship.income;
        cout << " Введите тип учетной записи (Bring_out / Insert): ";
        cin.ignore();
        cin.getline(ship.type, 12);
        cout << " Введите сумму, вносимую на Л/С (тыс. руб.): ";
        cin >> ship.deposit;
        cout << "\n Учетная запись создана.\n" << endl;
        fwrite(&ship, sizeof(ship), 1, baza);
        cout << "\n Продолжать?[Y/N]";

        while ((otv = getc(stdin)) == '\n');
    } while (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н');

    cout << "\n Для возврата в главное меню, пожалуйста, нажмите <Enter>.";
    fclose(baza);
    return;
}


//***************************************************************
//    		функция для вывода ТАБЛИЦ БАЗЫ ДАННЫХ
//****************************************************************

void zag1() {
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

void zag2() {
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

void zag3() {
    int i;
    cout << endl << "\t";
    for (i = 1; i <= 51; i++)
        cout << "-";
    cout << endl;
    cout << "\t| ID договора |" << " Имя заёмщика |" << " Баланс |" << " Тип счёта |" << endl;
    cout << "\t";
    for (i = 1; i <= 51; i++)
        cout << "-";
    return;
}

void prosmotrbd1(const char* fname) {
    int i;
    trip ship;
    FILE* baza;
    baza = fopen(fname, PR_R);
    cout << "\n\n\n\t БАЗА ДАННЫХ МИКРО-ФИНАНСОВОЙ ОРГАНИЗАЦИИ 'Руки в Руки'\n\n";
    zag1();
    while (fread(&ship, sizeof(ship), 1, baza) > 0) {
        cout << endl << "\t|";
        cout.width(13); cout << ship.idDogovora << "|";
        cout.width(14); cout << ship.name << "|";
        cout.width(14); cout << ship.birthY << "|";
        cout.width(14); cout << ship.town << "|";
        cout.width(20); cout << ship.telNubmer << "|";
        cout.width(18); cout << ship.placeWork << "|";
        cout.width(11); cout << ship.income << "|";
        cout.width(8); cout << ship.deposit << "|";
        cout.width(11); cout << ship.type << "|";
    }
    cout << endl << "\t";
    for (i = 1; i <= 133; i++)
        cout << "-";
    fclose(baza);
    return;
}

void prosmotrbd2(const char* fname) {
    int i;
    trip ship;
    FILE* baza;
    baza = fopen(fname, PR_R); //открываем файл на чтение
    cout << "\n\n\n\t БАЗА ДАННЫХ МИКРО-ФИНАНСОВОЙ ОРГАНИЗАЦИИ 'Руки в Руки'\n\n";
    zag2();
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
    for (i = 1; i <= 133; i++)
        cout << "-";
    fclose(baza);
    return;
}

void prosmotrbd3(const char* fname) {
    int i;
    trip ship;
    FILE* baza;
    baza = fopen(fname, PR_R); //открываем файл на чтение
    cout << "\n\n\n\t БАЛАНС ПОЛЬЗОВАТЕЛЯ\n\n";
    zag3();
    while (fread(&ship, sizeof(ship), 1, baza) > 0) {
        cout << endl << "\t|";
        cout.width(13); cout << ship.idDogovora << "|";
        cout.width(14); cout << ship.name << "|";
        cout.width(8); cout << ship.deposit << "|";
        cout.width(11); cout << ship.type << "|";
    }
    cout << endl << "\t";
    for (i = 1; i <= 51; i++)
        cout << "-";
    fclose(baza);
    return;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Сортировка по названию яхт по алфавиту!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void sort_title(const char* fname) {
    int i;
    int fl;
    trip ppp, ship;
    FILE* baza;
    baza = fopen(fname, PR_S); //открываем файл на чтение и запись
    do {
        rewind(baza);
        fl = 0;
        for (i = 0; fread(&ship, sizeof(ship), 1, baza) > 0; i += sizeof(ship), fseek(baza, i, SEEK_SET)) {
            if (fread(&ppp, sizeof(ship), 1, baza) > 0) {
                if (strncmp(ship.title, ppp.title, 15) > 0) {
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

//проверка наличия физического файла
int proverka_file(const char* fname, const char* pr) {//Открываем файл
    if (!(fopen(fname, pr)))
        return(0);
    return(1);
}

void settings_bd()
{
    char ch;
    int num;
    char otv;
    char fname_b[25] = FNAME_B;

    do {
        system("cls");
        cout << "\n\n\n\t РЕДАКТИРОВАНИЕ БАЗЫ ДАННЫХ ЗАЁМЩИКОВ";
        cout << "\n\n\t 01. ВЫВЕСТИ СПИСОК ВСЕХ ЗАЁМЩИКОВ.";
        cout << "\n\n\t 02. ДОБАВИТЬ УЧЁТНУЮ ЗАПИСЬ ЗАЁМЩИКА.";
        cout << "\n\n\t 03. ИЗМЕНИТЬ УЧЁТНУЮ ЗАПИСЬ ЗАЁМЩИКА.";//НОВАЯ УЧЕТНАЯ ЗАПИСЬ
        cout << "\n\n\t 04. УДАЛИТЬ УЧЁТНУЮ ЗАПИСЬ ЗАЁМЩИКА.";
        cout << "\n\n\t 05. Вернуться в меню" << endl;
        cout << "\n\t Введите номер варианта (1-5): ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            if (!proverka_file(fname_b, PR_R)) {
                cout << "\n Ошибка открытия файла для чтения" << endl;
                break;
            }
            prosmotrbd1(fname_b);
            break;
        case '2':
            if (proverka_file(fname_b, PR_R)) {
                cout << " Файл базы данных МФО с именем " << fname_b;
                cout << " был создан ранее.";
                cout << "\n Продолжить заполнение заполнее в данном файле? [Y/N]: ";

                while ((otv = getc(stdin)) == '\n');
                if (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н') {
                    dobavka(fname_b);
                    break;
                }
                else if (otv == 'N' || otv == 'n' || otv == 'Т' || otv == 'т') {
                    cout << " Задайте имя ранее создаваемого файла (необходимо также указать разширение .dat): ";
                    cin >> fname_b;
                    if (!proverka_file(fname_b, PR_R)) {
                        cout << " Такая база данных не создавалась." << endl;
                        cout << " \nСоздаём новый файл базы данных." << endl;
                        cout << " Введи название базы данных МФО на латин. (необходимо также указать разширение .dat): ";
                        cin >> fname_b;
                        cout << " Хотите продолжить заполнение базы данных? [Y/N]: ";

                        while ((otv = getc(stdin)) == '\n');
                        if (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н') {
                            dobavka(fname_b);
                            break;
                        }
                        else if (otv == 'N' || otv == 'n' || otv == 'Т' || otv == 'т')
                        {
                            cout << "\n Для возврата в главное меню, пожалуйста, нажмите <Enter>.";
                            int main();
                            break;
                        }
                        else {
                            cout << "\n Мы не смогли распознать Ваш ответ. Возращаем Вас в Главное меню." << endl;
                            int main();
                            break;
                        }
                    }
                }
                else {
                    cout << "\n Мы не смогли распознать Ваш ответ. Возращаем Вас в Главное меню." << endl;
                    int main();
                    break;
                }
            }
            cout << " Добавляем записи в файл " << fname_b << endl;
            dobavka(fname_b);
            cout << "\n Файл базы данных успешно обновлен.";
            break;
        case '3':
            cout << "\n\n\tВведите id договора : "; cin >> num;
            //modify_account(fname_b, num);
            break;
        case '4':
            cout << "\n\n\tВведите id договора : "; cin >> num;
            //delete_account(num);
            break;
        case '5':
            cout << "\n\n\t Для продолжения, пожалуйста, нажмите <Enter>" << endl;
            break;
        }
        cin.ignore();
        cin.get();
    } while (ch != '5');
    return;
}

//***************************************************************
//    		функция для изменения записи файла
//****************************************************************

//***************************************************************
//    		функция для проведения РАСЧЕТНЫХ БАНКОВСКИХ ОПЕРАЦИЙ
//****************************************************************

void operations_rko(const char* fname_b, const char* fname_id)
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
            deposit_withdraw(fname_b, num, 1);
            break;
        case '2':
            cout << "\n\n\t Введите id договора : "; cin >> num;
            deposit_withdraw(fname_b, num, 2);
            break;
        case '3':

            if (!proverka_file(fname_b, PR_R)) {
                cout << "\n Ошибка открытия файла для чтения" << endl;
                break;
            }
            if (!proverka_file(fname_id, PR_W)) {
                cout << "\n Ошибка открытия файла для записи" << endl;
                break;
            }
            sort_ID(fname_b, fname_id);
            prosmotrbd3(fname_id);
            cout << "\n\n\t Для продолжения, пожалуйста, нажмите <Enter>" << endl;
            break;

            //display_sp(fname1, fname2);
            break;
        case '4':
            cout << "\n\n\t Для продолжения, пожалуйста, нажмите <Enter>" << endl;
            break;
        }
        cin.ignore();
        cin.get();
    } while (ch != '4');
    return;
}

void deposit_withdraw(const char* fname, int n, int option)
{
    int amt;
    trip ac{};
    account ap{};
    FILE* baza;
    baza = fopen(fname, PR_S);

    if (!proverka_file(fname, PR_R))
    {
        cout << "\n\t Ошибка открытия файла для чтения и записи! Press any Key...";
        return;
    }

    while (fread(&ap, sizeof(ac), 1, baza) > 0) {
        if (ac.idDogovora[6] == n)
        {
            ap.show_account();
            if (option == 1)
            {
                cout << "\n\n\t\t ПОПОЛНЕНИЕ ЛИЦЕВОГО СЧЁТА ЗАЁМЩИКА ";
                cout << "\n\n\t Введите сумму, на которую хотите произвести пополнение: ";
                cin >> amt;
                ap.dep(amt);
            }
            if (option == 2)
            {
                cout << "\n\n\t\t ВЫВОД СРЕДСТВ С ЛИЦЕВОГО СЧЁТА ЗАЁМЩИКА ";
                cout << "\n\n\t Введите сумму, на которую хотите произвести вывод средств:";
                cin >> amt;
                double bal = ac.deposit - amt;
                if ((bal < 5 && ac.type == "") || (bal < 25 && ac.type == ""))
                    cout << "\n\t Для данной операции недостаточно денежных средств.\n Пожалуйста, убедитеть в корректности запроса и попробуйте еще раз!";
                else
                    ap.draw(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            //fseekp(pos, ios::cur);
            fwrite(reinterpret_cast<char*> (&ac), sizeof(trip), 1, baza);
            cout << "\n\t\t УЧЁТНАЯ ЗАПИСЬ ЗАЁМЩИКА ОБНОВЛЕНА.";
            cout << "\n\n\t Для продолжения - нажмите <Enter>.";
            //found = true;
        }
    }
        
    fclose(baza);
    return;
}

//*******************************************************************************************
//    		функция для отображения БАЛАНСА по ID учетной записи, предоставленных пользователем
//*******************************************************************************************

void sort_ID(const char* fname1, const char* fname2)
{
    char searchID[7];
    trip ship;
    FILE* in,     //исходный файл
        * out;    //файл результатов поиска
    in = fopen(fname1, PR_R);  //открываем файл на чтение
    out = fopen(fname2, PR_W);  //открываем файл на запись
    cout << "\n\t Введите ID договора для проверки баланса: ";
    cin >> searchID;
    while (fread(&ship, sizeof(ship), 1, in) > 0)
        if (strncmp(ship.idDogovora, searchID, 7) == 0)
            fwrite(&ship, sizeof(ship), 1, out);
    fclose(out);
    fclose(in);
    return;
}

//*******************************************************************************************
//    		функция для сортировки по возрастанию СРЕДНЕГО ЕЖЕМЕСЯЧНОГО ДОХОДА 
//*******************************************************************************************
void sort_income(const char* fname) {
    int i;
    int fl;
    trip ppp, ship;
    FILE* baza;
    baza = fopen(fname, PR_S); //открываем файл на чтение и запись
    do {
        rewind(baza);
        fl = 0;
        for (i = 0; fread(&ship, sizeof(ship), 1, baza) > 0; i += sizeof(ship), fseek(baza, i, SEEK_SET)) {
            if (fread(&ppp, sizeof(ship), 1, baza) > 0) {
                if (ship.income > ppp.income) {
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

//Поиск по городу проживания
//*******************************************************************************************
//    		функция для отображения БАЗЫ ДАННЫХ по ГОРОДУ учетной записи, предоставленных пользователем
//*******************************************************************************************
void sort_town(const char* fname1, const char* fname2) {
    char searchTown[25];
    trip ship;
    FILE* in,     //исходный файл
        * out;    //файл результатов поиска
    in = fopen(fname1, PR_R);  //открываем файл на чтение
    out = fopen(fname2, PR_W);  //открываем файл на запись
    cout << "\n\t Введите город, по которому необходимо выгрузить фильтр: ";
    cin >> searchTown;
    while (fread(&ship, sizeof(ship), 1, in) > 0)
        if (strncmp(ship.town, searchTown, 25) == 0)
            fwrite(&ship, sizeof(ship), 1, out);
    fclose(out);
    fclose(in);
    return;
}

