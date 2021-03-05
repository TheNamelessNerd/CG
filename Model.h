#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "geometry.h"

class Model
{
private:
	std::vector<Vec3d> verts_;
	std::vector<std::vector<int>> faces_;
public:
	Model(const char* filename);
	~Model();
	int nverts();
	int nfaces();
	Vec3d vert(int i);
	std::vector<int> face(int idx);
};