#include <iostream>
#include "../tgaimage/tgaimage.h"
#include <algorithm>
#include <cmath>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

// отрезок Брезенхема
void BrezenhemLine(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{

    // Инициальзация переменных
    int x = x0, y = y0;
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int s1, s2;

    int swap;

    //Sign x
    if ((x1 - x0) > 0)
        s1 = 1;
    else if ((x1 - x0) < 0)
        s1 = -1;
    else
        s1 = 0;

    //Sign y
    if ((y1 - y0) > 0)
        s2 = 1;
    else if ((y1 - y0) < 0)
        s2 = -1;
    else
        s2 = 0;

    /*
    Обмен значениями dx и dy в зависимости от углового коэффициента
    наклона отрезка
    */
    if (dy > dx)
    {
        std::swap(dx, dy);
        swap = 1;
    }
    else
        swap = 0;

    //Инициализация d с поправкой на половину пиксела
    int d = 2 * dy - dx;

    //Основной цикл
    for (int i = x0; i < dx; i++)
    {
        image.set(x, y, color);
        while (d >= 0) {
            if (swap == 1)
                x += s1;
            else
                y += s2;
            d = d - 2 * dx;
        }
        if (swap == 1)
            y += s2;
        else
            x += s1;
        d = d + 2 * dy;
    }
}

// ЦДА для отрезка
void DrawLineDDA(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
    if (x1 < x0 && y1 < y0) {
        std::swap(x1, x0);
        std::swap(y1, y0);
    }

    double x = x0, y = y0;
    double y10 = abs(y1 - y0);
    double x10 = abs(x1 - x0);
    double dx = 1,
            dy = y10 / x10;

    while (x <= x1) {
        image.set(x, y, color);
        if (x1 < x0)
            x -= dx;
        else
            x += dx;
        if (y1 < y0)
            y -= dy;
        else
            y += dy;
    }
}

void Circle_Pixel(int x0, int y0, int x, int y, TGAImage& image, TGAColor color) {
    image.set(x0 + x, y0 + y, color);
    image.set(x0 + y, y0 + x, color);
    image.set(x0 + y, y0 - x, color);
    image.set(x0 + x, y0 - y, color);
    image.set(x0 - x, y0 - y, color);
    image.set(x0 - y, y0 - x, color);
    image.set(x0 - y, y0 + x, color);
    image.set(x0 - x, y0 + y, color);
}

// Просто окружность
void Circle(int x0, int y0, int R, TGAImage& image, TGAColor color) {
    for (int x = 0; x <= R / sqrt(2); x++) {
        int y = (int)(sqrt(pow(R, 2) - pow(x, 2)));
        Circle_Pixel(x0, y0, x, y, image, color);
    }
}

void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
    for (double t = 0.; t < 1.; t += .01) {
        int x = x0 * (1. - t) + x1 * t;
        int y = y0 * (1. - t) + y1 * t;
        image.set(x, y, color);
    }
}

// Параметрическая окружность
void parametricCircle(int x, int y, int R, TGAImage& image, TGAColor color) {
    int x1, x2, y1, y2;
    x2 = x + R;
    y2 = y;

    for (int i = 1; i <= 360; i++) {
        x1 = x2;
        y1 = y2;
        x2 = round(R * cos(i)) + x;
        y2 = round(R * sin(i)) + x;
        line(x1, y1, x2, y2, image, color);
    }
}

// Окружность Брезенхема
void BrezenhemCircle(int x0, int y0, int R, TGAImage& image, TGAColor color) {
    int d = 1 - 2 * R,
            x = 0,
            y = R,
            error = 0;

    while (y >= 0) {
        image.set(x0 + x, y0 + y, color);
        image.set(x0 + x, y0 - y, color);
        image.set(x0 - x, y0 + y, color);
        image.set(x0 - x, y0 - y, color);

        error = 2 * (d + y) - 1;
        if ((d < 0) && (error < 0)) {
            d += (2 * ++x + 1);
            continue;
        }
        if ((d > 0) && (error > 0)) {
            d -= (2 * --y + 1);
            continue;
        }
        d += (2 * (++x - --y));
    }
}

int main()
{
    TGAImage image(1000, 1000, TGAImage::RGB);

    //BrezenhemLine(200, 500, 250, 200, image, white);
    //DrawLineDDA(250, 500, 200, 0, image, white);
    //parametricCircle(500, 500, 150, image, white);
    Circle(500, 500, 150, image, white);
    //BrezenhemCircle(500, 500, 150, image, white);

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}

