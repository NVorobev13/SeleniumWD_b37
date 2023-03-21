#include<iostream>
#include<locale.h>
#include<math.h>
using namespace std;
float recur1(int m, float y0, float y1, float y2);
float recur2(int m, float y0, float y1, float y2);
float recur3(int m, float y0, float y1, float y2);

int main() {
    int var, m;
    float re1, re2, re3;
    float y0, y1, y2;
    setlocale(LC_ALL, "Russian");
    for (;;) {
        cout << "\n  Вид действия:" << endl;
        cout << " 1 - вычисление суммы по рекуррентной формуле" << endl;
        cout << " 2 - завершение задачи" << endl;
        cout << " Введите вид действия -> ";
        cin >> var;
        switch (var) { 
        case 1:
            cout << " Введите m -> ";
            cin >> m;
            cout << " Введите y0, y1, y2 -> ";
            cin >> y0 >> y1 >> y2;
            re1 = recur1(m, y0, y1, y2);
            re2 = recur2(m, y0, y1, y2);
            re3 = recur3(m, y0, y1, y2);

            cout.precision(3);
            cout << " Для цикла WHILE результат     = " << re1 << endl;
            cout << " Для цикла DO..WHILE результат = " << re2 << endl;
            cout << " Для цикла FOR результат       = " << re3 << endl;
            break; 
        default: return 1;
        }
    }
}

float recur1(int m, float y0, float y1, float y2) {
    int   i = 0;
    float y,
        sum = 0;
    sum += (i * (sqrt(abs(y0)))); i++;
    sum += (i * (sqrt(abs(y1)))); i++;
    sum += (i * (sqrt(abs(y2)))); i++;
    while (i <= m) {
        y = (sin(y2) * sin(y2) + cos(y0) * cos(y0)) / (((3 * i * 1.) / m) + 2);
        sum += (i * (sqrt(abs(y))));
        y0 = y1;
        y1 = y2;
        y2 = y;
        i++;
    }
    return((10 + (3. / m)) * sum);
}

float recur2(int m, float y0, float y1, float y2) {
    int   i = 0;
    float y,
        sum = 0;
    sum += (i * (sqrt(abs(y0)))); i++;
    sum += (i * (sqrt(abs(y1)))); i++;
    sum += (i * (sqrt(abs(y2)))); i++;
    do {
        y = (sin(y2) * sin(y2) + cos(y0) * cos(y0)) / (((3 * i * 1.) / m) + 2);
        sum += (i * (sqrt(abs(y))));;
        y0 = y1;
        y1 = y2;
        y2 = y;
        i++;
    } 
    while (i <= m);
    return((10 + (3. / m)) * sum);
}

float recur3(int m, float y0, float y1, float y2) {
    int   i = 0;
    float y,
        sum = 0;
    sum += (i * (sqrt(abs(y0)))); i++;
    sum += (i * (sqrt(abs(y1)))); i++;
    sum += (i * (sqrt(abs(y2)))); i++;
    for (; i <= m; i++) {
        y = (sin(y2) * sin(y2) + cos(y0) * cos(y0)) / (((3 * i * 1.) / m) + 2);
        sum += (i * (sqrt(abs(y))));
        y0 = y1;
        y1 = y2;
        y2 = y;
    }
    return((10 + (3. / m)) * sum);
}
