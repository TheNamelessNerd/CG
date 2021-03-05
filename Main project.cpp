#include <iostream>
#include "../tgaimage/tgaimage.h"
#include <algorithm>
#include <cmath>
#include "geometry.h"
#include "Model.h"

using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

Model* model = NULL;

const int WIDTH = 1000;
const int HEIGHT = 1000;

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

int main()
{
    TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

    model = new Model("african_head.obj");

    for (int i = 0; i < model->nfaces(); i++)
    {
        vector<int> face = model->face(i);
        for (int j = 0; j < 3; j++)
        {
            Vec3d v0 = model->vert(face[j]);
            Vec3d v1 = model->vert(face[(j + 1) % 3]);
            int x0 = (v0.x + 1.) * WIDTH / 2.;
            int y0 = (v0.y + 1.) * HEIGHT / 2.;
            int x1 = (v1.x + 1.) * WIDTH / 2.;
            int y1 = (v1.y + 1.) * HEIGHT / 2.;
    
            BrezenhemLine(x0, y0, x1, y1, image, white);
        }
    }
    
    image.flip_vertically();
    image.write_tga_file("output.tga");
    delete model;
    system("pause");
    return 0;
}

