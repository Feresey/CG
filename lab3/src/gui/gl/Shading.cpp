#include "GLWidget.hpp"

// https://stackoverflow.com/questions/15095909/from-rgb-to-hsv-in-opengl-glsl

float Clamp(float val, float min = 0, float max = 1)
{
    if (val > max) {
        return max;
    }
    if (val < min) {
        return min;
    }
    return val;
}

// Vector3f GLWidget::Phong(const Vector3f& point, const Vector3f& normal) const
// {
//     // return { .5, .5, 0 };
//     float ambient{}, diffuze{}, specular{};
//     ambient = Ka * ia;
//     Vector3f L((is_move_light ? moved_light : light * scale));
//     Vector3f distance(point - L);

//     // length of normal is always 1
//     float d(distance.Length());
//     diffuze = distance * normal * Kd * il / (d + K);
//     // std::cout << "diffuze: " << diffuze << std::endl;
//     // Vector3f R((-1 * L).CrossProduct(normal));
//     // Vector3f camera{ 100, 0, 4 * scale };

//     // float d{ camera.DistanceTo(point) + K };
//     // Vector3f L = point - light;
//     // L.Normalize();
//     // float diffuze{ Kd * il / d * scale * Clamp(L.Angle(normal), 0, 1) };

//     // float
//     //     lncos(L.Angle(normal));
//     // // diffuze((Kd * il) / (K + d) * 100 * Clamp(lncos, 0, 1));
//     // // std::cout << "diffuze: " << diffuze << std::endl;
//     // L *= -1;
//     // Vector3f
//     //     R(L - normal * L.Angle(normal) * 2),
//     //     S(L - point);
//     // R.Normalize();
//     // S.Normalize();
//     // float srcos(R.Angle(S));
//     // specular = il * Ks * scale * std::pow(Clamp(srcos, 0, 1), ip);

//     float res = ambient + Clamp(diffuze) + Clamp(specular);
//     return {
//         res * lightColor.x() * objectColor.x(),
//         res * lightColor.y() * objectColor.y(),
//         res * lightColor.z() * objectColor.z()
//     };
// }

Vector3f reflect(const Vector3f& d, const Vector3f& n) { return Vector3f{ d - 2 * d.DotProduct(n) * n }; }

Vector3f GLWidget::Guro(const Vector3f& point, const Vector3f& normal) const
{
    // Calculate normal in view space
    // Vector3f N = mat3(mv_matrix) * normal;
    // Calculate view vector (simply the negative of the view-space position)
    Vector3f V(0, 0, 3 * scale);
    // Calculate view-space light vector
    Vector3f L(light - V);

    // Normalize all three vectors
    L.Normalize();
    V.Normalize();
    // Calculate R by reflecting -L around the plane defined by N
    Vector3f R = reflect(-L, normal);

    // Calculate the diffuse and specular contributions
    float ambient = Ka * ia;
    float diffuse = Clamp(normal.DotProduct(L)) * Kd;
    float specular = pow(Clamp(R.DotProduct(V)), ip) * Ks;

    // Send the color output to the fragment shader
    float res(ambient + diffuse + specular);
    // float res = ambient + Clamp(diffuze) + Clamp(specular);
    Vector3f r{
        res * lightColor.x() * objectColor.x(),
        res * lightColor.y() * objectColor.y(),
        res * lightColor.z() * objectColor.z()
    };
    // std::cout << r << std::endl;
    return r;
}

void GLWidget::triangle(const Polygon& tr)
{
    const Vector3f& normal(tr.getNormal());
    auto v2p = [](const Vector3f& src) -> Vector2i { return { qRound(src.x()), float_to_int(src.y()) }; };
    Vector2i
        v1(v2p(tr[0])),
        v2(v2p(tr[1])),
        v3(v2p(tr[2]));

    //sort
    if (v3.y() < v2.y()) {
        std::swap(v2, v3);
    }
    if (v3.y() < v1.y()) {
        std::swap(v1, v3);
    }
    if (v2.y() < v1.y()) {
        std::swap(v2, v1);
    }

    const int total_height = v3.y() - v1.y();

    int bottom_y = std::max(v1.y(), 0),
        top_y = std::min(v3.y(), height());

    // degraded triangles
    if (bottom_y > height() || top_y < 0 || total_height == 0 || abs(normal.z()) < EPS)
        return;
    if (mode == flat) {
        Vector3f col(
            Guro(tr[0], normal)
            + Guro(tr[1], normal)
            + Guro(tr[2], normal));
        col /= 3.f;
        // float x = tr.getCenter()[0], y = tr.getCenter()[1];
        // float z(tr[0][2] + (normal.x() * (tr[0][0] - x) + normal.y() * (tr[0][1] - y)) / normal.z());
        glColor3fv(col.v);
    }

    for (int y = v1.y(); y <= v3.y(); ++y) {
        // out of screen
        if (abs(y) > height())
            continue;

        bool top = y >= v2.y() || v1.y() == v2.y();
        int segment_height = (top ? v3.y() - v2.y() : v2.y() - v1.y());
        float alpha = static_cast<float>((y - v1.y())) / float(total_height);
        float beta = static_cast<float>((y - (top ? v2.y() : v1.y()))) / float(segment_height);
        Vector2i A(v3 * alpha + v1 * (1 - alpha));
        Vector2i B((top ? v2 : v1) + (top ? v3 - v2 : v2 - v1) * beta);
        if (A.x() > B.x())
            std::swap(A, B);
        int bottom_x = std::max(A.x(), 0),
            top_x = std::min(B.x(), width());

        // out of screen
        if (bottom_x > width() || top_x < 0)
            continue;
        if (A.x() < 0)
            A[0] = (std::max(A.x(), -width()));
        else
            A[0] = (std::min(A.x(), width()));
        if (B.x() < 0)
            B[0] = (std::max(B.x(), -width()));
        else
            B[0] = (std::min(B.x(), width()));

        for (int x = A.x(); x <= B.x(); ++x) {
            // float x = tr.getCenter()[0], y = tr.getCenter()[1];
            if (mode == guro) {
                float z(tr[0][2] + (normal.x() * (tr[0][0] - x) + normal.y() * (tr[0][1] - y)) / normal.z());
                glColor3fv(Guro(Vector3f{ x, y, z }, normal).v);
            }
            glVertex2i(x, y);
        }
    }
}