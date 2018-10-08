#include "Loader.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <cstdio>

std::optional<OpenGLGeo>
load_obj_file(std::string const& filename)
{
    auto vertices = std::vector<float>{};
    auto normals = std::vector<float>{};
    auto indices = std::vector<uint32_t>{};
    auto normal_indices = std::vector<uint32_t>{};
    auto obj = std::ifstream{ filename };
    std::string line;
    if (obj.is_open()) {
        while (getline(obj, line)) {
            if (line.size() >= 2) {
                auto prefix = line.substr(0, 2);
                if (prefix == "v ") {
                    float x, y, z;
                    auto matched =
                      sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
                    if (matched != 3) {
                        std::cerr
                          << R"(Expected a line like "v f f f" but got ")"
                          << line << R"(")" << std::endl;
                        return {};
                    }
                    vertices.push_back(x);
                    vertices.push_back(y);
                    vertices.push_back(z);
                } else if (prefix == "vn") {
                    float x, y, z;
                    auto matched =
                      sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z);
                    if (matched != 3) {
                        std::cerr <<
                          R"(Expected a line like "vn f f f" but got ")" << line
                                  << R"(")" << std::endl;
                        return {};
                    }
                    normals.push_back(x);
                    normals.push_back(y);
                    normals.push_back(z);
                } else if (prefix == "f ") {
                    int v1, t1, n1;
                    int v2, t2, n2;
                    int v3, t3, n3;
                    auto matched = sscanf(line.c_str(),
                                          "f %d/%d/%d %d/%d/%d %d/%d/%d",
                                          &v1,
                                          &t1,
                                          &n1,
                                          &v2,
                                          &t2,
                                          &n2,
                                          &v3,
                                          &t3,
                                          &n3);
                    if (matched != 9) {
                        std::cerr
                          << R"(Expected a line like "f d/d/d d/d/d d/d/d" but got ")"
                          << line << R"(")" << std::endl;
                        return {};
                    }
                    indices.push_back(v1 - 1);
                    indices.push_back(v2 - 1);
                    indices.push_back(v3 - 1);
                    normal_indices.push_back(n1 - 1);
                    normal_indices.push_back(n2 - 1);
                    normal_indices.push_back(n3 - 1);
                }
            }
        }
    } else {
        std::cerr << "Couldn't open file " << filename << std::endl;
        return {};
    }

    std::vector<float> real_normals{};
    real_normals.resize(vertices.size());
    for (size_t i = 0; i < indices.size(); i++) {
        auto vi = indices[i] * 3;
        auto ni = normal_indices[i] * 3;
        real_normals[vi] = normals[ni];
        real_normals[vi + 1] = normals[ni + 1];
        real_normals[vi + 2] = normals[ni + 2];
    }

    return std::make_optional<OpenGLGeo>(vertices, real_normals, indices);
}
