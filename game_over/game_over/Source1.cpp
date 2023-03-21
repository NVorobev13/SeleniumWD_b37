#include<iostream>
#define _USE_MATH_DEFINES M_PI 3.141592653589793238462643383279502884 // for C++
#include <cmath>
#include<locale.h>
using namespace std;

typedef double(*Tfun)(double);
double integral(double, double, int, double, Tfun, double);

double fun1(double x);
double fun2(double x);
double fun3(double x);
double fun4(double x);
double fun5(double x);
double fun6(double x);
double fun7(double x);
double fun8(double x);
double fun9(double x);
double fun10(double x);
double fun11(double x);
double fun12(double x);
double fun13(double x);

int main() {
    int i = 0, n = 10; //номер области и начальное число разбиений
    double x, y, s1, s2, s3, s4, s5; //точность вычислени€ и вычисленна€ площадь области
    double eps = .0001, s = 0;
    setlocale(LC_ALL, "Russian");
    cout << "\n¬ведите координаты точки: x, y ";
    cin >> x >> y;
    if (x * x + (y - 1) * (y - 1) < 1 && x * x + y * y > 1 && (x + 1) * (x + 1) + (y - 1) * (y - 1) > 1 && (x - 1) * (x - 1) + y * y > 1) {
        cout << "“очка в области M1. " << endl;
        i = 1;
    }
    else if ((x + 1) * (x + 1) + y * y < 1 && (x + 1) * (x + 1) + (y - 1) * (y - 1) < 1 && x * x + y * y > 1) {
        cout << "“очка в области M2. " << endl;
        i = 2;
    }
    else if ((x - 1) * (x - 1) + y * y < 1 && (x - 1) * (x - 1) + (y - 1) * (y - 1) > 1 && (x - 1) * (x - 1) + (y + 1) * (y + 1) > 1 && x * x + y * y > 1) {
        cout << "“очка в области M3. " << endl;
        i = 3;
    }
    else if ((x - 1) * (x - 1) + y * y < 1 && (x - 1) * (x - 1) + (y - 1) * (y - 1) > 1 && (x - 1) * (x - 1) + (y + 1) * (y + 1) > 1 && x * x + (y - 1) * (y - 1) > 1 && x < 1) {
        cout << "“очка в области M4. " << endl;
        i = 4;
    }
    else if (x * x + (y + 1) * (y + 1) < 1 && x * x + y * y > 1 && (x + 1) * (x + 1) + y * y > 1) {
        cout << "“очка в области M5. " << endl;
        i = 5;
    }
    else {
        cout << "“очка вне выделенных областей";
    }
    cout.precision(4);
    switch (i) {
    case 1: cout << "Formula: S1 = " << (s1 = 1 * 1) << endl;
        cout << "Integral: S1 = " << (s1 = integral(-.5, 1, n, eps, fun1, s)
            - integral(-.5, 0, n, eps, fun2, s)
            - integral(0, .5, n, eps, fun3, s)
            - integral(.5, 1, n, eps, fun4, s)) << endl;
        break;
    case 2: cout << "Formula: S2 = " << (s2 = M_PI / 4) << endl;
        cout << "Integral: S2 = " << (s2 = fabs(integral(-2, -.5, n, eps, fun5, s))
            - fabs(integral(-1, -.5, n, eps, fun3, s))
            - fabs(integral(-1, -1 - sqrt(3) / 2, n, eps, fun6, s))
            - fabs(integral(-1 - sqrt(3) / 2, -2, n, eps, fun5, s))) << endl;
        break;
    case 3: cout << "Formula: S3 = " << (s3 = 2 * (M_PI / 4 - (M_PI / 3 - (sqrt(3) / 4)))) << endl;
        cout << "Integral: S3 = " << (s3 = fabs(integral(1, 1 + sqrt(3) / 2, n, eps, fun7, s))
            + fabs(integral(1 + sqrt(3) / 2, 2, n, eps, fun4, s))
            + fabs(integral(1, 1 + sqrt(3) / 2, n, eps, fun8, s))
            + fabs(integral(1 + sqrt(3) / 2, 2, n, eps, fun9, s))) << endl;
        break;
    case 4: cout << "Formula: S4 = " << (s4 = 1 - M_PI / 4) << endl;
        cout << "Integral: S4 = " << (s4 = fabs(integral(0, 1 - sqrt(3) / 2, n, eps, fun11, s))
            + fabs(integral(1 - sqrt(3) / 2, 1, n, eps, fun8, s))
            - fabs(integral(0, .5, n, eps, fun10, s))
            - fabs(integral(.5, 1, n, eps, fun7, s))) << endl;
        break;

    case 5: cout << "Formula: S5 = " << (s5 = 2 - (1 - M_PI / 4)) << endl;
        cout << "Integral: S5 = " << (s5 = fabs(integral(-1, 1, n, eps, fun12, s))
            - fabs(integral(-sqrt(3) / 2, sqrt(3) / 2, n, eps, fun11, s))
            - fabs(integral(sqrt(3) / 2, 1, n, eps, fun12, s))
            - fabs(integral(-1, -sqrt(3) / 2, n, eps, fun13, s))) << endl;

    }

    cout << "\n ѕовторить-1, ¬ыход-2: ";
    cin >> i;
    if (i == 1) main();
    return 0;
}

//нахождение определенного интеграла методом криволинейных трапеций
double integral(double a, double b, int n, double eps, Tfun fun, double s1) {
    double x, h, s = 0;
    int i;
    h = (b - a) / n;
    for (i = 0; i < n; i++) {
        x = a + i * h + h / 2;
        s += fun(x);
    }
    s *= h;
    if (fabs(s - s1) > eps)
        s = integral(a, b, 2 * n, eps, fun, s);
    return s;
}

/*описание вида интегрируемой функции є1 дл€ линии: x^2+(y-1)^2=1 (верхн€€ полуокружность)*/
double fun1(double x) {
    return(sqrt(1 - x * x) + 1);
}
/*описание вида интегрируемой функции є2 дл€ линии: (x+1)^2+(y-1)^2=1 (верхн€€ полуокружность)*/
double fun2(double x) {
    return(sqrt(1 - (x + 1) * (x + 1)) + 1);
}
/*описание вида интегрируемой функции є3 дл€ линии: x^2+(y-1)^2=1 (верхн€€ полуокружность)*/
double fun3(double x) {
    return(sqrt(1 - x * x));
}
/*описание вида интегрируемой функции є4 дл€ линии: (x-1)^2+y^2=1 (верхн€€ полуокружность)*/
double fun4(double x) {
    return(sqrt(1 - (x - 1) * (x - 1)));
}
/*описание вида интегрируемой функции є5 дл€ линии: (x+1)^2+y^2=1 (верхн€€ полуокружность)*/
double fun5(double x) {
    return(sqrt(1 - (x + 1) * (x + 1)));
}
/*описание вида интегрируемой функции є6 дл€ линии: (x+1)^2+y^2=1 (нижн€€ полуокружность)*/
double fun6(double x) {
    return(-sqrt(1 - (x + 1) * (x + 1)) + 1);
}
/*описание вида интегрируемой функции є7 дл€ линии: (x-1)^2+(y-1)^2=1 (нижн€€ полуокружность)*/
double fun7(double x) {
    return(-sqrt(1 - (x - 1) * (x - 1)) + 1);
}
/*описание вида интегрируемой функции є8 дл€ линии: (x-1)^2+(y+1)^2=1 (верхн€€ полуокружность)*/
double fun8(double x) {
    return(sqrt(1 - (x - 1) * (x - 1)) - 1);
}
/*описание вида интегрируемой функции є9 дл€ линии: (x-1)^2+y^2=1 (нижн€€ полуокружность)*/
double fun9(double x) {
    return(-sqrt(1 - (x - 1) * (x - 1)));
}
/*описание вида интегрируемой функции є10 дл€ линии: x^2+(y-1)^2=1 (нижн€€ полуокружность)*/
double fun10(double x) {
    return(-sqrt(1 - x * x) + 1);
}
/*описание вида интегрируемой функции є11 дл€ линии: x^2+(y-1)^2=1 (нижн€€ полуокружность)*/
double fun11(double x) {
    return(-sqrt(1 - x * x));
}
/*описание вида интегрируемой функции є12 дл€ линии: x^2+(y-1)^2=1 (нижн€€ полуокружность)*/
double fun12(double x) {
    return(-sqrt(1 - x * x) - 1);
}
/*описание вида интегрируемой функции є13 дл€ линии: (x+1)^2+y^2=1 (нижн€€ полуокружность)*/
double fun13(double x) {
    return(-sqrt(1 - (x + 1) * (x + 1)));
}