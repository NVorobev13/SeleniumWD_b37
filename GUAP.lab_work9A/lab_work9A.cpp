#include <iostream>
#include <locale.h>
#include <cmath>
using namespace std;
typedef int telem; //объявление типа элемента массива
typedef telem* tmas; //объявление типа "указатель на telem"
void fillArray(tmas arr, int n);//визуализация введенного массива
void showArray(tmas arr, int n);
int firstPositive(tmas arr, telem& pol, int n);
void areElem(telem& mult, int i, int j, int n);
void absoluteValueMult(tmas arr, telem& mult, int n, int i_pol);//вывод элементов с четными номерами и вычисление абсолютного произведения

int main() {
    int n, i, pr;
    setlocale(LC_ALL, "Russian");
    cout << "\nОпределить произведение абсолютных значений элементов " << endl;
    cout << "массива с чётными номерами, лежащих между первым элементом " << endl;
    cout << "массива с положительным значением и элементом с номером n." << endl;
    cout << "Введите количество элементов массива: ";
    cin >> n;
    
    tmas arr = new telem[2 * n]; /*создание переменной-указателя на telem, выделение динамической памяти под массив адрес начала области заносится в arr*/
    int i_pol; //номер первого элемента с положительным значением значением
    telem pol; //значение первого положительного элемента 
    telem mult = 1; //значение абсолютного произведения
    fillArray(arr, 2 * n);
    showArray(arr, 2 * n);
    i_pol = firstPositive(arr, pol, 2 * n); //Поиск номера первого элемента с положительным значением
    
    cout << "\nПервый элемент массива с положительным значением: " << pol << ", под номером: " << i_pol << endl;
    cout << "Элемент массива со значением: " << arr[n] << ", под номером n = " << n;
    
    areElem(mult, n, i_pol, n);
    absoluteValueMult(arr, mult, n, i_pol);
    pr = mult;

    cout << "\nПроизведение абсолютных значений элементов массива " << endl;
    cout << "с чётными номерами, лежащие между первым элементом " << endl;
    cout << "массива с положительным значением и элементом с номером n: " << sr_pr << endl;
    delete[] arr; //освобождение динамической памяти
    cout << " Повторить-1, Выход-2: ";
    cin >> i;
    if (i == 1) main();
    return 0;
}

int firstPositive(tmas arr, telem& pol, int n) {
    int i;
    int i_pol;
    for (int i = 0; i < n; i++) {
        if (*(arr + i) > 0) {
            pol = *(arr + i);
            i_pol = i;
            return i_pol;
        }
    }
    cout << "\nВ данном массиве нет положительных элементов. Выполнение программы невозможно. " << endl;
    cout << "Повторить-1, Выход-2: ";
    cin >> i;
    if (i == 1) main();
    exit(1);
    return i;
} 

void absoluteValueMult(tmas arr, telem& mult, int n, int i_pol) {
    int start{}, stop{};
    if (i_pol < n) { //Если первое положительное число стоит раньше числа с элементом n
        stop = n;
        if (i_pol % 2 == 0) {  //проверка на чётность
            start = i_pol + 2; //чётное - начать со следующего чётного
        }
        else {
            start = i_pol + 1;
        }
    }
    else if (i_pol > n) { //Если число с элементом n стоит раньше первого положительного
        stop = i_pol;
        if (n % 2 == 0) {
            start = n + 2;
        }
        else {
            start = n + 1;
        }
    }
    cout << "\nЭлементы с чётными номерами: ";
    for (int i = start; i < stop; i += 2) {
        cout << *(arr + i) << " ";
        mult *= *(arr + i);
    }
    if (mult < 0) {
        mult = -mult;
    }
    cout << endl;
} 

void fillArray(tmas arr, int n) {
    cout << "\nВведите одной строкой элементы массива из ";
    cout << n << " чисел и нажмите <Enter>" << endl;
    for (int i = 0; i < n; i++) {
        cin >> *(arr + i);
    }
}  

void showArray(tmas arr, int n) {
    cout << "Массив имеет вид: " << endl;
    for (int i = 0; i < n; i++) {
        cout << *(arr + i) << " ";
    }
    cout << endl;
} 

void areElem(telem& mult, int i, int j, int n) {
    int k;
    if (i == n && (j == n - 1 || j == n + 1)) {
        cout << "\nВ данном массиве на заложенном интервале отсутвуют элементы с чётными номерами. Произведение абсолютных значений элементов массива равно: " << mult * 0 << endl;
        mult *= 0;
        cout << "Повторить-1, Выход-2: ";
        cin >> k;
        if (k == 1) main();
        exit(1);
    }
    else if (i == j) {
        cout << "\nВ данном массиве оба элемента совпадают по номеру и значению. Выполнение программы невозможно. " << endl;
        cout << "Повторить-1, Выход-2: ";
        cin >> k;
        if (k == 1) main();
        exit(1);
    }
}
