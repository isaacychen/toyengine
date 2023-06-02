#include <iostream>
#include "tgaimage.h"
#include "model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
Model *model = nullptr;
const int width = 800;
const int height = 800;

/**
 * Assume error2 = error * dx * 2
 *
 * todo: We can separate the cases of steep and not steep to avoid transpose.
 *
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 * @param image
 * @param color
 */
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    // float derror = std::abs(dy/float(dx));
    // float error = 0;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = y0;
    if (steep) {
        for (int x = x0; x <= x1; x++) {
            image.set(y, x, color);
            // error += derror;
            // if (error>.5) {
            error2 += derror2;
            if (error2 > dx) {
                y += (y1 > y0 ? 1 : -1);
                error2 -= dx * 2;
            }
        }
    } else {
        for (int x = x0; x <= x1; x++) {
            image.set(x, y, color);
            // error += derror;
            // if (error>.5) {
            error2 += derror2;
            if (error2 > dx) {
                y += (y1 > y0 ? 1 : -1);
                error2 -= dx * 2;
            }
        }
    }
}

/**
 * ABC is a triangle, P is a point
 *
 * @param pts Triangle vertices
 * @param P   Point
 * @return
 */
Vec3f barycentric(const Vec3f &a, const Vec3f &b, const Vec3f &c, const Vec3f &p) {
    // uAB + vAC + PA = 0
    const Vec3f x(
            b.x - a.x, // ABx
            c.x - a.x, // ACx
            a.x - p.x  // PAx
    );

    const Vec3f y(
            b.y - a.y, // ABy
            c.y - a.y, // ACy
            a.y - p.y  // PAy
    );

    const Vec3f &u = x ^ y;

    /* `pts` and `P` has integer value as coordinates
       so `abs(u[2])` < 1 means `u[2]` is 0, that means
       triangle is degenerate, in this case return something with negative coordinates */
    if (std::abs(u.z) <= 1e-2) return {-1, 1, 1};

    return {1.f - (u.x + u.y) / u.z, u.x / u.z, u.y / u.z};
}

void triangle(Vec3f *pts, float *zBuffer, TGAImage &image, const TGAColor &color) {
    Vec2i borderBoxMin(image.get_width() - 1, image.get_height() - 1);
    Vec2i borderBoxMax(0, 0);
    for (int i = 0; i < 3; i++) {
        borderBoxMin.x = std::min(borderBoxMin.x, static_cast<int>(pts[i].x));
        borderBoxMin.y = std::min(borderBoxMin.y, static_cast<int>(pts[i].y));
        borderBoxMax.x = std::max(borderBoxMax.x, static_cast<int>(pts[i].x));
        borderBoxMax.y = std::max(borderBoxMax.y, static_cast<int>(pts[i].y));
    }
    for (int x = borderBoxMin.x; x <= borderBoxMax.x; x++) {
        for (int y = borderBoxMin.y; y <= borderBoxMax.y; y++) {
            Vec3f p(x, y, 0);
            Vec3f barycentricCoord = barycentric(pts[0], pts[1], pts[2], p);
            // If barycentricCoord has negative value, it means the point is outside the triangle
            if (barycentricCoord.x < 0 || barycentricCoord.y < 0 || barycentricCoord.z < 0) continue;
            float z = pts[0].z * barycentricCoord.x + pts[1].z * barycentricCoord.y + pts[2].z * barycentricCoord.z;
            if (zBuffer[x + y * width] >= z) continue;
            zBuffer[x + y * width] = z;
//            image.set(x, y, TGAColor(255 * z, 255 * z, 255 * z, 255));
            image.set(x, y, color);
        }
    }
}

Vec3f world2screen(Vec3f v) {
    return Vec3f(int((v.x + 1.) * width / 2. + .5), int((v.y + 1.) * height / 2. + .5), (v.z + 1)/ 2 );
}

//int main(int argc, char **argv) {
//    auto v = barycentric(Vec3f(0, 0, 10), Vec3f(0, 10, 10), Vec3f(10, 10, 999), Vec3f(1, 5, 999));
//    std::cout << v << std::endl;
//}

int main(int argc, char **argv) {
    if (2 == argc) {
        model = new Model(argv[1]);
    } else {
        model = new Model("assets/african_head.obj");
//        model = new Model("assets/textured_output.obj");
    }


    TGAImage image(width, height, TGAImage::RGB);

//    for (int i = 0; i < model->nfaces(); i++) {
//        std::vector<int> face = model->face(i);
//        for (int j = 0; j < 3; j++) {
//            Vec3f v0 = model->vert(face[j]);
//            Vec3f v1 = model->vert(face[(j + 1) % 3]);
//            int x0 = static_cast<int>((v0.x + 1.) * width / 2.);
//            int y0 = static_cast<int>((v0.y + 1.) * height / 2.);
//            int x1 = static_cast<int>((v1.x + 1.) * width / 2.);
//            int y1 = static_cast<int>((v1.y + 1.) * height / 2.);
//            line(x0, y0, x1, y1, image, white);
//        }
//    }

//    Vec2i pts[3] = {Vec2i(10, 10), Vec2i(100, 30), Vec2i(190, 160)};
//    triangle(pts, image, TGAColor(255, 0, 0, 255));

    // Lighting Vector
    Vec3f lightingVector(0, 0, -1);

    auto *zBuffer = new float[width * height];
    for (int i=width*height; i--; zBuffer[i] = -std::numeric_limits<float>::max());

    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec3f screen_coords[3];
        Vec3f world_coords[3];

        for (int j = 0; j < 3; j++) {
            world_coords[j] = model->vert(face[j]);
            screen_coords[j] = world2screen(world_coords[j]);
        }

        // Calculate normal vector
        Vec3f normalVector = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);

        // Normalize normal vector
        normalVector.normalize();

        // Calculate light intensity
        float intensity = normalVector * lightingVector;

        if (intensity <= 0) continue;

        triangle(screen_coords, zBuffer, image, TGAColor(255 * intensity, 255 * intensity, 255 * intensity, 255));
    }

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}
