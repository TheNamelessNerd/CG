#include <iostream>
#include <algorithm>
#include <cmath>
#include <math.h>

using namespace std;

double const PI = 3.1416;
double const degRad = 60;//PI/3.0;

void RGB_CMY(double r, double g, double b){
    double c, m, y;
    c = 1 - r;
    m = 1 - g;
    y = 1 - b;

    cout << "C: " << c << endl
         << "M: " << m << endl
         << "Y: " << y << endl;
}

void RGB_CMYK(double r, double g, double b){
    double c, m, y, k;
    c = 1 - r;
    m = 1 - g;
    y = 1 - b;

    k = fmin(fmin(c, m), y);

    c = (c - k) / (1 - k);
    m = (m - k) / (1 - k);
    y = (y - k) / (1 - k);

    cout << "C: " << c << endl
         << "M: " << m << endl
         << "Y: " << y << endl
         << "K: " << k << endl;
}

void RGB_HSV(double r, double g, double b){
    double max = fmax(fmax(r, g), b);
    double min = fmin(fmin(r, g), b);

    double h, s, v;

    if (max == r && g >= b)
        h = degRad * (g - b) / (max - min);

    else if (max == r && g < b)
        h = degRad * (g - b) / (max - min) + 2*degRad*3;

    else if (max == g)
        h = degRad * (b - r) / (max - min) + 2*degRad;

    else if (max == b)
        h = degRad * (r - g) / (max - min) + 4*degRad;

    else
        h = -1;

    s = max == 0 ? 0 : 1 - min/max;
    v = max;

    cout << "H: " << h << endl
         << "S: " << s << endl
         << "V: " << v << endl;
}

void RGB_HSL(double r, double g, double b){
    double max = fmax(fmax(r, g), b);
    double min = fmin(fmin(r, g), b);

    double h, s, l;

    if (max == r && g >= b)
        h = degRad * (g - b) / (max - min);

    else if (max == r && g < b)
        h = degRad * (g - b) / (max - min) + 2*degRad*3;

    else if (max == g)
        h = degRad * (b - r) / (max - min) + 2*degRad;

    else if (max == b)
        h = degRad * (r - g) / (max - min) + 4*degRad;

    else
        h = -1;

    l = 1.0/2 * (max + min);

    if (l == 0 || l == 1 || max == min)
        s = 0;

    else if (0 < l && l <= 1.0/2)
        s = (max - min) / 2*l;

    else if (1.0/2 < l && l < 1)
        s = (max - min) / (2 - 2*l);

    cout << "H: " << h << endl
         << "S: " << s << endl
         << "L: " << l << endl;
}

void RGB_XYZ(double r, double g, double b){
    double x, y, z;
    double k = 1.0/0.17697;

    x = k * (   0.49 * r +   0.31 * g +     0.2 * b);
    y = k * (0.17697 * r + 0.8124 * g + 0.01063 * b);
    z = k * (      0 * r +   0.01 * g +    0.99 * b);

    cout << "X: " << x << endl
         << "Y: " << y << endl
         << "Z: " << z << endl;
}

double r, g, b;

void CMY_RGB(double c, double m, double y){
    ::r = 1 - c;
    ::g = 1 - m;
    ::b = 1 - y;
}

void CMYK_RGB(double c, double m, double y, double k){
    ::r = (1 - c) / (1 - k);
    ::g = (1 - m) / (1 - k);
    ::b = (1 - y) / (1 - k);
}

void HSV_RGB(double h, double s, double v){
    double c, x, m;
    double r, g, b;

    int a = h / degRad;
    int ab = abs(a % 2 - 1);

    c = v * s;
    x = c * (1.0 - ab);
    m = v - c;

    //degRad = 60 || PI.3
    if (0 <= h && h < degRad){
        r = c;
        g = x;
        b = 0;
    }
    else if (degRad <= h && h < 2*degRad){
        r = x;
        g = c;
        b = 0;
    }
    else if (2*degRad <= h && h < 3*degRad){
        r = 0;
        g = c;
        b = x;
    }
    else if (3*degRad <= h && h < 4*degRad){
        r = 0;
        g = x;
        b = c;
    }
    else if (4*degRad <= h && h < 5*degRad){
        r = x;
        g = 0;
        b = c;
    }
    else if (5*degRad <= h && h < 6*degRad){
        r = c;
        g = 0;
        b = x;
    }

    ::r = r + m;
    ::g = g + m;
    ::b = b + m;
}

void HSL_RGB(double h, double s, double l){
    double c, x, m;
    double r, g, b;

    int a = h / degRad;
    int ab = abs(a % 2 - 1);

    c = (1 - abs(2*l - 1)) * s;
    x = c * (1 - ab);
    m = l - c/2;

    //degRad = 60 || PI.3
    if (0 <= h && h < degRad){
        r = c;
        g = x;
        b = 0;
    }
    else if (degRad <= h && h < 2*degRad){
        r = x;
        g = c;
        b = 0;
    }
    else if (2*degRad <= h && h < 3*degRad){
        r = 0;
        g = c;
        b = x;
    }
    else if (3*degRad <= h && h < 4*degRad){
        r = 0;
        g = x;
        b = c;
    }
    else if (4*degRad <= h && h < 5*degRad){
        r = x;
        g = 0;
        b = c;
    }
    else if (5*degRad <= h && h < 6*degRad){
        r = c;
        g = 0;
        b = x;
    }

    ::r = r + m;
    ::g = g + m;
    ::b = b + m;
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Choose input model:\n" << "1:RGB \n2:CMY \n3:CMYK \n4:HSV \n5:HSL" << endl;
    int inp1, inp2;
    cin >> inp1;
    cout << "Output model:\n" << "1:RGB \n2:CMY \n3:CMYK \n4:HSV \n5:HSL \n6:XYZ?" << endl;
    cin >> inp2;

    cout << "Enter 3 or 4(for CMYK) components [0, 1]:\n";
    double a, b, c;

    if (inp1 == 4 || inp1 == 5)
        cout << "1 component must be 0 <= H < 360\n";
    cout << "1: ";
    cin >> a;
    cout << "2: ";
    cin >> b;
    cout << "3: ";
    cin >> c;

    switch (inp1) {
    case 1:
        r = a;
        g = b;
        ::b = c;
        break;
    case 2:
        CMY_RGB(a, b, c);
        break;
    case 3:
        cout << "4: ";
        double k;
        cin >> k;
        CMYK_RGB(a, b, c, k);
        break;
    case 4:
        HSV_RGB(a, b, c);
        break;
    case 5:
        HSL_RGB(a, b, c);
        break;
    default:
        cerr << "Error";
        return 0;
    }

    cout << endl;

    switch (inp2) {
    case 1:
        cout << "R: " << r << endl
             << "G: " << g << endl
             << "B: " << ::b << endl;
        break;
    case 2:
        RGB_CMY(r, g, ::b);
        break;
    case 3:
        RGB_CMYK(r, g, ::b);
        break;
    case 4:
        RGB_HSV(r, g, ::b);
        break;
    case 5:
        RGB_HSL(r, g, ::b);
        break;
    case 6:
        RGB_XYZ(r, g, ::b);
        break;
    default:
        break;
    }

    return 0;
}
