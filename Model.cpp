#include "Model.h"

using namespace std;

Model::Model(const char* filename) : verts_(), faces_()
{
    ifstream in(filename);
    if (!in) 
    {
        cerr << "Error" << endl;
        return;
    }
        
    string line;
    while (getline(in, line))
    {
        if (line.substr(0, 2) == "v ")
        {
            istringstream s(line.substr(2));
            Vec3d v;
            for (int i = 0; i < 3; i++)
                s >> v.raw[i];
            verts_.push_back(v);
        }
        else if (line.substr(0, 2) == "f ")
        {
            vector<int> f;
            istringstream s(line.substr(2));
            char trash;
            int idx, itrash;
            while (s >> idx >> trash >> itrash >> trash >> itrash)
            {
                idx--;
                f.push_back(idx);
            }
            faces_.push_back(f);
        }
    }
    cout << "v# " << verts_.size() << " f# " << faces_.size() << endl;
}

Model::~Model(){}

int Model::nverts() 
{
    return (int)verts_.size();
}

int Model::nfaces()
{
    return (int)faces_.size();
}

vector<int> Model::face(int idx)
{
    return faces_[idx];
}

Vec3d Model::vert(int i)
{
    return verts_[i];
}