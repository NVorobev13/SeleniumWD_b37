#include<iostream>
#include<locale.h>
using namespace std;
typedef int telem;		//определение типа элементов массива
typedef telem* tstr;		//определение типа "указатель на telem"
typedef tstr* tmatr;		//тип "указатель на указатель на telem"
void fillArray(tmatr, int);
void showArray(tmatr, int);
double zona_pr(tmatr arr, int n);
double zona_tr(tmatr arr, int n);

int main() 
{
    int n;				//число строк (столбцов) матрицы
    double pr, tr, sr;
    tmatr arr;				//переменная-указатель на указатель на telem
    setlocale(LC_ALL, "Russian");
    cout << " В заданной квадратной матрице размера 2n*2n \n";
    cout << " найти среднее арифметическое значений \n";
    cout << " отрицательных элементов области [5+6+7+8+1]. \n";
    cout << " Введите половину размера матрицы: n = ";
    cin >> n;
    arr = new tstr[2 * n];		/*выделение динамической памяти под массив указателей на строки массива*/
    for (int i = 0; i < 2 * n; i++)	//выделение памяти под каждую строку:
        *(arr + i) = new telem[2 * n];	/*каждому элементу массива указателей на строки присваивается адрес начала области памяти, выделяемой под строку*/
    fillArray(arr, 2 * n);
    cout << " Исходная матрица:\n";
    showArray(arr, 2 * n);
    pr = zona_pr(arr, n);
    tr = zona_tr(arr, n);
    sr = (pr + tr) / 2;

    cout << " Среднее арифметическое значений отрицательных элементов: " << sr << endl;
    cout << endl << " Для завершения нажмите <Enter>" << endl; //Освобождение динамической памяти
    for (int i = 0; i < n * 2; i++)
        delete* (arr + i);
    delete[]arr;
    return 0;
}

void fillArray(tmatr arr, int n)
{
    cout << " Значения элементов";
    cout << " массива размера " << n << "x" << n;
    cout << "\n при тестировании вводятся автоматически:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(*(arr + i) + j) = -(10 * i + j);
        }
    }
        
}

void showArray(tmatr arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout.width(3);	//ширина поля выводимого параметра
            cout << *(*(arr + i) + j) << ' ';
        }
        cout << '\n';
    }
}

double zona_pr(tmatr arr, int n)
{
    telem sum = 0;
    double avg;
    int count = 0;
    for (int i = 0; i < n * 2; i++) {
        for (int j = 0; j < n; j++) {
            if (*(*(arr + i) + j) < 0) {
                count++;    //Счётчик увеличиваем на 1
                sum += *(*(arr + i) + j);    //Сумму увеличиваем на значение элемента
            }
        }
    } 
    avg = sum * 1. / count;
    return avg;
}

double zona_tr(tmatr arr, int n)
{
    telem sum = 0;
    double avg;
    int count = 0;

    for (int i = n; i < n * 2; i++) {
        for (int j = (n * 2) - i; j < n * 2; j++) {
            if (*(*(arr + i) + j) < 0) {
                count++;    //Счётчик увеличиваем на 1
                sum += *(*(arr + i) + j);    //Сумму увеличиваем на значение элемента
            }
        }
    }
    avg = sum * 1. / count;
    return avg;
}