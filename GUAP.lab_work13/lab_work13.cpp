#include <stdio.h>
#include <string.h>
#include<fstream>
#include<cctype>
#include<iomanip>
#include <iostream>
using namespace std;
#define FNAME_I "D:\\bd15.dat\0" //имя файла с исходной базой
#define FNAME_R "D:\\bd25.dat\0" //имя файла с результатами поиска

int proverka_file(const char*, const char*); //проверка наличия файла
void dobavka(const char* fname);
void zag1();
void zag2();
void prosmotrbd1(const char* fname);
void prosmotrbd2(const char* fname);
void sort_owner(const char* fname1, const char* fname2);
void sort_title(const char* fname);
void sort_lenght(const char* fname);

void intro();	//функция вводного экрана

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
}
trip;

void intro()
{
    cout << "\n\n\n\t     BANK";
    cout << "\n\n\tUSER MANAGEMENT";
    cout << "\n\n\t    SYSTEM";
    cout << "\n\n\n\nCREATED BY: N.A. VOROBEV";
    cout << "\n\nUNIVERSITY: GUAP";
    cin.get();
}

int main() {
    int var;
    char otv;
    char fname_i[20] = FNAME_I;
    char fname_r[20] = FNAME_R;
    setlocale(LC_ALL, "Russian");
    intro();

    for (; ;) { //Выбор вида действия
        cout << "\n    Вид действия:" << endl;
        cout << "  1 - создание базы данных" << endl;
        cout << "  2 - добавление новых записей" << endl;
        cout << "  3 - сортировка по названию яхт" << endl;
        cout << "  4 - сортировка по длинне яхт" << endl;
        cout << "  5 - поиск яхт по имени владельца" << endl;
        cout << "  6 - просмотр базы данных" << endl;
        cout << "  7 - просмотр базы данных поиска яхт" << endl;
        cout << "  8 - завершение задачи" << endl;
        cout << "  Введите вид действия -> (1-8): ";
        cin >> var;
        switch (var) {
        default:break;
        case 1:
            if (proverka_file(fname_i, PR_R)) {
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
            if (!proverka_file(fname_i, PR_W)) {
                cout << "\n Ошибка открытия файла для записи" << endl;
                break;
            }
            cout << " Создаем базу " << fname_i << endl;
            getchar();
            dobavka(fname_i);
            cout << "Создание файла закончено." << endl;
            if (proverka_file(fname_i, PR_R))
                cout << " База данных готова к работе" << endl;
            else cout << "база не создана" << endl;
            break;

        case 2:
            if (proverka_file(fname_i, PR_R)) {
                cout << " Файл базы данных владельцев яхт с именем " << fname_i;
                cout << " был создан раньше.";
                cout << " Будем добавлять новые записи в него? [Y/N] ";
                while ((otv = getchar()) == '\n');
                if (otv == 'N' || otv == 'n' || otv == 'Т' || otv == 'т') {
                    cout << " Задайте имя файла другой базы: ";
                    cin >> fname_i;
                    if (!proverka_file(fname_i, PR_R)) {
                        cout << " Такая база данных не создавалась" << endl;
                        break;
                    }
                }
            }
            cout << " Добавляем записи в файл " << fname_i << endl;
            dobavka(fname_i);
            cout << "\n Изменение файла закончено.";
            break;

        case 3:
            if (!proverka_file(fname_i, PR_S)) {
                cout << "\n Ошибка открытия файла для чтения и записи" << endl;
                break;
            }
            sort_title(fname_i);
            cout << "\n Сортировка по названию яхт закончена.";
            break;

        case 4:
            if (!proverka_file(fname_i, PR_S)) {
                cout << "\n Ошибка открытия файла для чтения и записи" << endl;
                break;
            }
            sort_lenght(fname_i);
            cout << "\n Сортировка по длинне яхт закончена.";
            break;

        case 5:
            if (!proverka_file(fname_i, PR_R)) {
                cout << "\n Ошибка открытия файла для чтения" << endl;
                break;
            }
            if (!proverka_file(fname_r, PR_W)) {
                cout << "\n Ошибка открытия файла для записи" << endl;
                break;
            }
            sort_owner(fname_i, fname_r);
            cout << "\n Поиск по имени владельцая яхты закончен.";
            break;

        case 6:
            if (!proverka_file(fname_i, PR_R)) {
                cout << "\n Ошибка открытия файла для чтения" << endl;
                break;
            }
            prosmotrbd1(fname_i);
            break;

        case 7:
            if (!proverka_file(fname_r, PR_R)) {
                cout << "\n Ошибка открытия файла для чтения" << endl;
                break;
            }
            prosmotrbd2(fname_r);
            break;

        case 8:
            return 0;
        }
    }
}

//Добавление новых элементов в базу данных
void dobavka(const char* fname) {
    char otv;
    trip ship{};
    FILE* baza;
    baza = fopen(fname, PR_A);
    rewind(baza);
    do {
        cout << "\n Название яхты? ";
        cin >> ship.title;

        cout << " Имя владельца? ";
        cin >> ship.owner;

        cout << " Длинна яхты? (м.) ";
        cin >> ship.lenght;

        cout << " Стоимость? (млн.$) ";
        cin >> ship.cost;

        cout << " Год постройки? ";
        cin >> ship.yearsOld;

        fwrite(&ship, sizeof(ship), 1, baza);

        cout << "\n Продолжать?[Y/N]";
        while ((otv = getchar()) == '\n');
    } while (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н');
    fclose(baza);
    return;
}

//Вывод заголовка при просмотре исходного файла
void zag1() {
    int i;
    cout << endl;
    for (i = 1; i <= 80; i++)
        cout << "-";
    cout << endl;
    cout << "| Название яхты |" << " Имя владельца |" << " Длинна, м |" << " Стоимость, млн.$ |" << " Год постройки |" << endl;

    for (i = 1; i <= 80; i++)
        cout << "-";
    return;
}

//Вывод заголовка при просмотре файла поиска имени владельца
void zag2() {
    int i;
    cout << endl;
    for (i = 1; i <= 80; i++)
        cout << "-";
    cout << endl;
    //cout("|%15s|%15s|%11s|%18s|%15s|\n", "Имя владельца ", "Название яхты ", "Длина, м", "Стоимость, млн.$", "Год постройки");
    cout << "| Название яхты |" << " Имя владельца |" << " Длинна, м |" << " Стоимость, млн.$ |" << " Год постройки |" << endl;
    for (i = 1; i <= 80; i++)
        cout << "-";
    return;
}

//Просмотр базы данных владельцев яхт
void prosmotrbd1(const char* fname) {
    int i;
    trip ship;
    FILE* baza;
    baza = fopen(fname, PR_R);
    cout << "\n     База данных владельцев яхт";
    zag1();
    while (fread(&ship, sizeof(ship), 1, baza) > 0) {
        cout << endl;
        cout.width(16); cout << ship.title << "|";
        cout.width(15); cout << ship.owner << "|";
        cout.width(11); cout << ship.lenght << "|";
        cout.width(18); cout << ship.cost << "|";
        cout.width(15); cout << ship.yearsOld << "|";

    }
    cout << endl;
    for (i = 1; i <= 80; i++)
        cout << "-";
    fclose(baza);
    return;
}

//Просмотр базы данных поиска по имени владельца яхт
void prosmotrbd2(const char* fname) {
    int i;
    trip ship;
    FILE* baza;
    baza = fopen(fname, PR_R); //открываем файл на чтение
    cout << "\n  База данных поиска владельцев яхт по имени владельца";
    zag2();
    while (fread(&ship, sizeof(ship), 1, baza) > 0) {
        //cout << "\n|%15s|%15s|%11i|%18i|%15s|" << ship.owner << ship.title << ship.lenght << ship.cost << ship.yearsOld;
        cout << endl;
        cout.width(16); cout << ship.owner << "|";
        cout.width(15); cout << ship.title << "|";
        cout.width(11); cout << ship.lenght << "|";
        cout.width(18); cout << ship.cost << "|";
        cout.width(15); cout << ship.yearsOld << "|";

    }
    cout << endl;
    for (i = 1; i <= 80; i++)
        cout << "-";
    fclose(baza);
    return;
}

//Поиск яхт по имени владельца
void sort_owner(const char* fname1, const char* fname2) {
    char ownerName[15];
    trip ship;
    FILE* in,     //исходный файл
        * out;    //файл результатов поиска
    in = fopen(fname1, PR_R);  //открываем файл на чтение
    out = fopen(fname2, PR_W);  //открываем файл на запись
    cout << "\n Имя владельца яхты для поиска? ";
    cin >> ownerName;
    while (fread(&ship, sizeof(ship), 1, in) > 0)
        if (strncmp(ship.owner, ownerName, 15) == 0)
            fwrite(&ship, sizeof(ship), 1, out);
    fclose(out);
    fclose(in);
    return;
}

//Сортировка по названию яхт по алфавиту
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

//Сортировка по убыванию длинны яхты
void sort_lenght(const char* fname) {
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
                if (ship.lenght > ppp.lenght) {
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