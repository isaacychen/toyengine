#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char *filename) {
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line);
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (float &i: v.raw) iss >> i;
            verts_.push_back(v);
        } else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            Vec2f v;
            for (float &i: v.raw) iss >> i;
            uvs.push_back(v);
        } else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            Vec3f v;
            for (float &i: v.raw) iss >> i;
            norms.push_back(v);
        } else if (!line.compare(0, 2, "f ")) {
            std::vector<int> f;
            std::vector<int> fUv;
            int itrash, idx, faceUvIndex;
            iss >> trash;
            while (iss >> idx >> trash >> faceUvIndex >> trash >> itrash) {
                idx--; // in wavefront obj all indices start at 1, not zero
                faceUvIndex--;
                f.push_back(idx);
                fUv.push_back(faceUvIndex);
            }
            faces_.push_back(f);
            faceUvs.push_back(fUv);
        }
    }
    std::cerr << "# v# " << verts_.size() << " vt# " << uvs.size() << " vn# " << norms.size() << " f# " << faces_.size() << std::endl;
}

Model::~Model() {
}

int Model::nverts() {
    return (int) verts_.size();
}

int Model::nfaces() {
    return (int) faces_.size();
}

std::vector<int> Model::face(int idx) {
    return faces_[idx];
}

Vec3f Model::vert(int i) {
    return verts_[i];
}

Vec2f Model::uv(int i) {
    return uvs[i];
}

std::vector<int> Model::faceUv(int uvIndex) {
    return faceUvs[uvIndex];
}

