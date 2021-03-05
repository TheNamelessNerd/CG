#include <iostream>
#include "tgaimage.h"
#include <algorithm>
#include <cmath>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

const int WIDTH = 100;
const int HEIGHT = 100;

// Отрезка Брезенхема
void BrezenhemLine(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
    bool steep = false;

    // Смотрим крутизну линии
    // Если она > 45 градусов, то будем строить по-другому
    if (abs(x0 - x1) < abs(y0 - y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    double deltaErr = abs(dy) * 2;
    double err = 0;
    int y = y0;

    for (int x = x0; x <= x1; x++)
    {
        if (steep)
            image.set(y, x, color);
        else
            image.set(x, y, color);

        err += deltaErr;

        if (err > dx)
        {
            y += (y1 > y0 ? 1 : -1);
            err -= (dx * 2);
        }
    }
}

void modifBrezenhem(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
    bool steep = false;

    // Смотрим крутизну линии
    // Если она > 45 градусов, то будем строить по-другому
    if (abs(x0 - x1) < abs(y0 - y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    const int I = 8;
    int x = x0,
            y = y0;
    int dx = x1 - x0;
    int dy = y1 - y0;

    double m = (I * dy) / dx;
    double w = I - m;
    double e = 0.5;

    if (steep)
        image.set(y, x, color);
    else
        image.set(x, y, color);

    while (x < x1)
    {
        if (e < w)
        {
            x++;
            e += m;
        }
        else
        {
            x++;
            y++;
            e -= w;
        }
        int pixColor = (int)(255 / e);
        if (steep)
            image.set(y, x, TGAColor(pixColor, pixColor, pixColor, 255));
        else
            image.set(x, y, TGAColor(pixColor, pixColor, pixColor, 255));
    }
}

double fpart(double x)
{
    return x - (int)x;
}

void Vu(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;

    if (dy < dx)
    {
        double grad = (double)dy / dx;
        double intery = y0 + grad;

        image.set(x0, y0, color);

        for (int x = x0 + 1; x < x1; x++)
        {
            int pixelColorUp = 255 - (int)(fpart(intery) * 255);
            int pixelColorDown = (int)(fpart(intery)) * 255;
            //Верхняя точка
            image.set(x, (int)intery, TGAColor(pixelColorUp, pixelColorUp, pixelColorUp, 255));
            //Нижняя точка
            image.set(x, (int)intery + 1, TGAColor(pixelColorDown, pixelColorDown, pixelColorDown, 255));
            //Изменение координаты Y
            intery += grad;
        }
        image.set(x1, y1, color);
    }
        //Для Y-линии (коэффициент наклона > 1)
    else
    {
        //Относительное изменение координаты X
        double grad = (double)dx / dy;
        //Промежуточная переменная для X
        double interx = x0 + grad;

        image.set(x0, y0, color);

        for (int y = y0 + 1; y < y1; y++)
        {
            int pixelColorUp = 255 - (int)(fpart(interx) * 255);
            int pixelColorDown = (int)(fpart(interx)) * 255;
            //Верхняя точка
            image.set((int)interx, y, TGAColor(pixelColorUp, pixelColorUp, pixelColorUp, 255));
            //Нижняя точка
            image.set((int)interx + 1, y, TGAColor(pixelColorDown, pixelColorDown, pixelColorDown, 255));
            //Изменение координаты X
            interx += grad;
        }
        image.set(x1, y1, color);
    }
}

int main()
{
    TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

    //modifBrezenhem(0, 0, 80, 15, image, white);
    //modifBrezenhem(0, 0, 80, 80, image, white);

    Vu(0, 0, 80, 80, image, white);
    Vu(0, 0, 15, 80, image, white);

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}
