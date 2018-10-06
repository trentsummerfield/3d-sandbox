#include "grid.h"

OpenGLGeo
make_grid()
{
    float half_width = 0.003f;
    std::vector<float> verts;

    // back to front
    verts.push_back(0.f + half_width);
    verts.push_back(0.f);
    verts.push_back(1.f);

    verts.push_back(0.f + half_width);
    verts.push_back(0.f);
    verts.push_back(-1.f);

    verts.push_back(0.f - half_width);
    verts.push_back(0.f);
    verts.push_back(-1.f);

    verts.push_back(0.f - half_width);
    verts.push_back(0.f);
    verts.push_back(1.f);

    verts.push_back(1.f + half_width);
    verts.push_back(0.f);
    verts.push_back(1.f);

    verts.push_back(1.f + half_width);
    verts.push_back(0.f);
    verts.push_back(-1.f);

    verts.push_back(1.f - half_width);
    verts.push_back(0.f);
    verts.push_back(-1.f);

    verts.push_back(1.f - half_width);
    verts.push_back(0.f);
    verts.push_back(1.f);

    verts.push_back(-1.f + half_width);
    verts.push_back(0.f);
    verts.push_back(1.f);

    verts.push_back(-1.f + half_width);
    verts.push_back(0.f);
    verts.push_back(-1.f);

    verts.push_back(-1.f - half_width);
    verts.push_back(0.f);
    verts.push_back(-1.f);

    verts.push_back(-1.f - half_width);
    verts.push_back(0.f);
    verts.push_back(1.f);

    //
    verts.push_back(1.f);
    verts.push_back(0.f);
    verts.push_back(0.f + half_width);

    verts.push_back(-1.f);
    verts.push_back(0.f);
    verts.push_back(0.f + half_width);

    verts.push_back(-1.f);
    verts.push_back(0.f);
    verts.push_back(0.f - half_width);

    verts.push_back(1.f);
    verts.push_back(0.f);
    verts.push_back(0.f - half_width);

    verts.push_back(1.f);
    verts.push_back(0.f);
    verts.push_back(1.f + half_width);

    verts.push_back(-1.f);
    verts.push_back(0.f);
    verts.push_back(1.f + half_width);

    verts.push_back(-1.f);
    verts.push_back(0.f);
    verts.push_back(1.f - half_width);

    verts.push_back(1.f);
    verts.push_back(0.f);
    verts.push_back(1.f - half_width);

    verts.push_back(1.f);
    verts.push_back(0.f);
    verts.push_back(-1.f + half_width);

    verts.push_back(-1.f);
    verts.push_back(0.f);
    verts.push_back(-1.f + half_width);

    verts.push_back(-1.f);
    verts.push_back(0.f);
    verts.push_back(-1.f - half_width);

    verts.push_back(1.f);
    verts.push_back(0.f);
    verts.push_back(-1.f - half_width);

    return { verts,
             {},
             {
               0,  1,  2,  0,  3,  2,

               4,  5,  6,  4,  7,  6,

               8,  9,  10, 8,  11, 10,

               12, 13, 14, 12, 15, 14,

               16, 17, 18, 16, 19, 18,

               20, 21, 22, 20, 23, 22,
             } };
}