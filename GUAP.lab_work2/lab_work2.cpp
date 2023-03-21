#include<iostream>
#include<locale.h>
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;

int main() {
    int i = 0;
    float x, y, s1, s2, s3, s4, s5;
    setlocale(LC_ALL, "Russian");
    cout << "\nВведите координаты точки: x, y ";
    cin >> x >> y;
    if (x * x + (y - 1) * (y - 1) < 1 && x * x + y * y > 1 && (x + 1) * (x + 1) + (y - 1) * (y - 1) > 1 && (x - 1) * (x - 1) + y * y > 1) {
        cout << "Точка в области M1. "; i = 1;
    }
    else if ((x + 1) * (x + 1) + y * y < 1 && (x + 1) * (x + 1) + (y - 1) * (y - 1) < 1 && x * x + y * y > 1) {
        cout << "Точка в области M2. "; i = 2;
    }
    else if ((x - 1) * (x - 1) + y * y < 1 && (x - 1) * (x - 1) + (y - 1) * (y - 1) > 1 && (x - 1) * (x - 1) + (y + 1) * (y + 1) > 1 && x * x + y * y > 1) {
        cout << "Точка в области M3. "; i = 3;
    }
    else if ((x - 1) * (x - 1) + y * y < 1 && (x - 1) * (x - 1) + (y - 1) * (y - 1) > 1 && (x - 1) * (x - 1) + (y + 1) * (y + 1) > 1 && x * x + (y - 1) * (y - 1) > 1 && x < 1) {
        cout << "Точка в области M4. "; i = 4;
    }
    else if (x * x + (y + 1) * (y + 1) < 1 && x * x + y * y > 1 && (x + 1) * (x + 1) + y * y > 1) {
        cout << "Точка в области M5. "; i = 5;
    }
    else {
        cout << "Точка вне выделенных областей";
    }
    cout.precision(4);
    switch (i) {
    case 1:
        cout << "S1 = " << (s1 = 1 * 1);
        break;
    case 2:
        cout << "S2 = " << (s2 = M_PI / 4);
        break;
    case 3:
        cout << "S3 = " << (s3 = 2 * (M_PI / 4 - (M_PI / 3 - (sqrt(3) / 4))));
        break;
    case 4:
        cout << "S4 = " << (s4 = 1 - M_PI / 4);
        break;
    case 5:
        cout << "S5 = " << (s5 = 2 - (1 - M_PI / 4));
    }
    cout << "\n Повторить-1, Выход-2: ";
    cin >> i;
    if (i == 1) main();
    return 0;
}