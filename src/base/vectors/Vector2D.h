//
// Created by daniel on 14/04/23.
//

#ifndef VECTORGRAPHICS_VECTOR2D_H
#define VECTORGRAPHICS_VECTOR2D_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>

template<class T>
struct Vector2D {
public:
    T x, y;

    Vector2D(T x, T y);

    Vector2D();

    Vector2D<T> operator+(Vector2D<T> v2);

    Vector2D<T> operator-(Vector2D<T> v2);

    Vector2D<T> operator*(T v);

    Vector2D<T> operator/(T v);

    Vector2D<T> operator+=(Vector2D<T> v1);

    Vector2D<T> operator-=(Vector2D<T> v1);

    Vector2D<T> operator/=(T v);

    Vector2D<T> operator*=(T v);

    bool operator==(Vector2D<T> v);

    T &operator[](int idx);

    T distance(Vector2D<T> v1);

    T modulo();

    T dot(Vector2D<T> v1);

    T angle(Vector2D<T> v1);

    Vector2D<T> unit();
};

template<class T>
Vector2D<T>::Vector2D(T x, T y): x{x}, y{y} {}

template<class T>
Vector2D<T>::Vector2D() : x{0}, y{0} {

}

template<class T>
Vector2D<T> Vector2D<T>::operator+(Vector2D<T> v2) {
    return Vector2D<T>(x + v2.x, y + v2.y);
}

template<class T>
Vector2D<T> Vector2D<T>::operator-(Vector2D<T> v2) {
    return Vector2D<T>(x - v2.x, y - v2.y);
}

template<class T>
Vector2D<T> Vector2D<T>::operator*(T v) {
    return Vector2D<T>(x * v, y * v);
}

template<class T>
Vector2D<T> Vector2D<T>::operator/(T v) {
    return Vector2D<T>(x / v, y / v);
}

template<class T>
Vector2D<T> Vector2D<T>::operator+=(Vector2D<T> v1) {
    x += v1.x;
    y += v1.y;
}

template<class T>
Vector2D<T> Vector2D<T>::operator-=(Vector2D<T> v1) {
    x -= v1.x;
    y -= v1.y;
}

template<class T>
Vector2D<T> Vector2D<T>::operator/=(T v) {
    x /= v;
    y /= v;
}

template<class T>
Vector2D<T> Vector2D<T>::operator*=(T v) {
    x *= v;
    y *= v;
}

template<class T>
bool Vector2D<T>::operator==(Vector2D<T> v) {
    return v.x == x && v.y == y;
}

template<class T>
T &Vector2D<T>::operator[](int idx) {
    if (idx == 0) return x;
    if (idx == 1) return y;
    throw std::out_of_range("Index out of bounds");
}

template<class T>
T Vector2D<T>::distance(Vector2D<T> v1) {
    return sqrt(pow(x - v1.x, 2) + pow(y - v1.y, 2));
}

template<class T>
T Vector2D<T>::modulo() {
    return sqrt(pow(x, 2) + pow(y, 2));
}

template<class T>
T Vector2D<T>::dot(Vector2D<T> v1) {
    return x*v1.x + y*v1.y;
}

template<class T>
T Vector2D<T>::angle(Vector2D<T> v1) {
    auto dp = dot(v1);
    auto angle = acos(dp/(modulo()*v1.modulo()));
    if (v1.y*x > v1.x*y) {
        return angle;
    }
    return -angle;
}

template<class T>
Vector2D<T> Vector2D<T>::unit() {
    return Vector2D{x/modulo(), y/modulo()};
}

typedef Vector2D<int> ivec2;
typedef Vector2D<double> dvec2;
typedef Vector2D<float> fvec2;

#endif //VECTORGRAPHICS_VECTOR2D_H
