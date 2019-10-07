#ifndef VECTOR3I_HPP
#define VECTOR3I_HPP

#include <QVector3D>

class Vector3I {
    int coord[3];

public:
    Vector3I(int x = 0, int y = 0, int z = 0);
    Vector3I(int coord[3]);
    Vector3I(const QVector3D& src);

    Vector3I(const Vector3I& src);
    Vector3I(Vector3I&& src);

    Vector3I& operator=(const Vector3I& src);
    Vector3I& operator=(Vector3I&& src);

    int x() const;
    int y() const;
    int z() const;

    int& operator[](size_t pos);
    int operator[](size_t pos) const;

    Vector3I& operator+=(const Vector3I& src);
    Vector3I& operator-=(const Vector3I& src);
    Vector3I& operator*=(float value);

    Vector3I operator+(const Vector3I& src) const;
    Vector3I operator-(const Vector3I& src) const;
    Vector3I operator*(float value) const;

    friend std::ostream& operator<<(std::ostream& os, const Vector3I& src);
};

#endif /* VECTOR3I_H */