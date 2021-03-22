/**
 * @authored by Xayah, BFU
 */
#ifndef ASSIGNMENT2_CAMERA_H
#define ASSIGNMENT2_CAMERA_H

#include "Eigen/Eigen"

class camera2D {
public:

    Eigen::Vector2f convert_screen_to_world(const Eigen::Vector2f &screen_point) {
        float w = float(screen_width);
        float h = float(screen_height);
        float u = screen_point.x() / w;
        float v = (h - screen_point.y()) / h;

        float ratio = w / h;
        Eigen::Vector2f extents(ratio * 25.0f, 25.0f);
        extents *= zoom;

        Eigen::Vector2f lower = center - extents;
        Eigen::Vector2f upper = center + extents;

        Eigen::Vector2f pw((1.0f - u) * lower.x() + u * upper.x(), (1.0f - v) * lower.y() + v * upper.y());
        return pw;
    }
    Eigen::Vector2f convert_world_to_screen(const Eigen::Vector2f &world_point) {
        float w = float(screen_width);
        float h = float(screen_height);
        float ratio = w / h;
        Eigen::Vector2f extents(ratio * 25.0f, 25.0f);
        extents *= zoom;

        Eigen::Vector2f lower = center - extents;
        Eigen::Vector2f upper = center + extents;

        float u = (world_point.x() - lower.x()) / (upper.x() - lower.x());
        float v = (world_point.y() - lower.y()) / (upper.y() - lower.y());

        Eigen::Vector2f ps(u * w, (1.0f - v) * h);
        return ps;
    }
    void build_projection_matrix(float* m, float zBias) {
        float w = float(screen_width);
        float h = float(screen_height);
        float ratio = w / h;
        Eigen::Vector2f extents(ratio * 25.0f, 25.0f);
        extents *= zoom;

        Eigen::Vector2f lower = center - extents;
        Eigen::Vector2f upper = center + extents;

        m[0] = 2.0f / (upper.x() - lower.x());
        m[1] = 0.0f;
        m[2] = 0.0f;
        m[3] = 0.0f;

        m[4] = 0.0f;
        m[5] = 2.0f / (upper.y() - lower.y());
        m[6] = 0.0f;
        m[7] = 0.0f;

        m[8] = 0.0f;
        m[9] = 0.0f;
        m[10] = 1.0f;
        m[11] = 0.0f;

        m[12] = -(upper.x() + lower.x()) / (upper.x() - lower.x());
        m[13] = -(upper.y() + lower.y()) / (upper.y() - lower.y());
        m[14] = zBias;
        m[15] = 1.0f;
    }

    Eigen::Vector2f center;
    float zoom;
    int screen_width;
    int screen_height;
};

//Eigen::Vector2f camera2D::convert_screen_to_world(const Eigen::Vector2f &screen_point) {
//    float w = float(screen_width);
//    float h = float(screen_height);
//    float u = screen_point.x() / w;
//    float v = (h - screen_point.y()) / h;
//
//    float ratio = w / h;
//    Eigen::Vector2f extents(ratio * 25.0f, 25.0f);
//    extents *= zoom;
//
//    Eigen::Vector2f lower = center - extents;
//    Eigen::Vector2f upper = center + extents;
//
//    Eigen::Vector2f pw((1.0f - u) * lower.x() + u * upper.x(), (1.0f - v) * lower.y() + v * upper.y());
//    return pw;
//}

//Eigen::Vector2f camera2D::convert_world_to_screen(const Eigen::Vector2f &world_point) {
//    float w = float(screen_width);
//    float h = float(screen_height);
//    float ratio = w / h;
//    Eigen::Vector2f extents(ratio * 25.0f, 25.0f);
//    extents *= zoom;
//
//    Eigen::Vector2f lower = center - extents;
//    Eigen::Vector2f upper = center + extents;
//
//    float u = (world_point.x() - lower.x()) / (upper.x() - lower.x());
//    float v = (world_point.y() - lower.y()) / (upper.y() - lower.y());
//
//    Eigen::Vector2f ps(u * w, (1.0f - v) * h);
//    return ps;
//}

// Convert from world coordinates to normalized device coordinates.
// http://www.songho.ca/opengl/gl_projectionmatrix.html
//void camera2D::build_projection_matrix(float* m, float zBias) {
//    float w = float(screen_width);
//    float h = float(screen_height);
//    float ratio = w / h;
//    Eigen::Vector2f extents(ratio * 25.0f, 25.0f);
//    extents *= zoom;
//
//    Eigen::Vector2f lower = center - extents;
//    Eigen::Vector2f upper = center + extents;
//
//    m[0] = 2.0f / (upper.x() - lower.x());
//    m[1] = 0.0f;
//    m[2] = 0.0f;
//    m[3] = 0.0f;
//
//    m[4] = 0.0f;
//    m[5] = 2.0f / (upper.y() - lower.y());
//    m[6] = 0.0f;
//    m[7] = 0.0f;
//
//    m[8] = 0.0f;
//    m[9] = 0.0f;
//    m[10] = 1.0f;
//    m[11] = 0.0f;
//
//    m[12] = -(upper.x() + lower.x()) / (upper.x() - lower.x());
//    m[13] = -(upper.y() + lower.y()) / (upper.y() - lower.y());
//    m[14] = zBias;
//    m[15] = 1.0f;
//}


#endif //ASSIGNMENT2_CAMERA_H