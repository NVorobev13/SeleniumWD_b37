#include <stdio.h>
#include <iostream>
using namespace std;

int main(){
    unsigned char a, b, c, d;
    a = 81 & 34;
    cout << "81 AND 34 = (0) = %i\n" << a;
    b = 81 ^ 34;
    cout << "81 XOR 34  = (115) = %i\n" << b;
    c = 81 << 1;
    cout << "81 << 1 = (162) = %i\n" << c;
    d = 70 ^ -81 & (~36 | 55);
    cout << "70 XOR -80 (NOT 36 | 55) = (233) = %i\n" << d;
    return 0;
}
