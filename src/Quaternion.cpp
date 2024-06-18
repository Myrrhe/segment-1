/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2017  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Quaternion.hpp"
#include <cmath>

const double Quaternion::epsilon = 0.000000000001;

Quaternion::Quaternion(double newX, double newY, double newZ, double newT) : x(newX),
                                                                             y(newY),
                                                                             z(newZ),
                                                                             t(newT)
{
}

Quaternion::Quaternion(std::complex<double> newXY, std::complex<double> newZT) : x(newXY.real()),
                                                                                 y(newXY.real()),
                                                                                 z(newZT.imag()),
                                                                                 t(newZT.imag())
{
}

Quaternion::Quaternion(const Quaternion &newXYZT) = default;

Quaternion::~Quaternion() = default;

Quaternion &Quaternion::operator=(const Quaternion &right) = default;

bool operator==(const Quaternion &left, const Quaternion &right)
{
    return (std::abs(left.x - right.x) <= Quaternion::epsilon && std::abs(left.y - right.y) <= Quaternion::epsilon && std::abs(left.z - right.z) <= Quaternion::epsilon && std::abs(left.t - right.t) <= Quaternion::epsilon);
}

bool operator!=(const Quaternion &left, const Quaternion &right)
{
    return (std::abs(left.x - right.x) > Quaternion::epsilon || std::abs(left.y - right.y) > Quaternion::epsilon || std::abs(left.z - right.z) > Quaternion::epsilon || std::abs(left.t - right.t) > Quaternion::epsilon);
}

bool operator>(const Quaternion &left, const Quaternion &right)
{
    return (left.x > right.x && left.y > right.y && left.z > right.z && left.t > right.t);
}

bool operator<(const Quaternion &left, const Quaternion &right)
{
    return (left.x < right.x && left.y < right.y && left.z < right.z && left.t < right.t);
}

bool operator>=(const Quaternion &left, const Quaternion &right)
{
    return (left.x >= right.x && left.y >= right.y && left.z >= right.z && left.t >= right.t);
}

bool operator<=(const Quaternion &left, const Quaternion &right)
{
    return (left.x <= right.x && left.y <= right.y && left.z <= right.z && left.t <= right.t);
}

const double &Quaternion::operator[](long unsigned int i) const
{
    long unsigned int index = i % 4UL;
    if (index == 0UL)
    {
        return x;
    }
    else if (index == 1UL)
    {
        return y;
    }
    else if (index == 2UL)
    {
        return z;
    }
    else
    {
        return t;
    }
}

double &Quaternion::operator[](long unsigned int i)
{
    long unsigned int index = i % 4UL;
    if (index == 0UL)
    {
        return x;
    }
    else if (index == 1UL)
    {
        return y;
    }
    else if (index == 2UL)
    {
        return z;
    }
    else
    {
        return t;
    }
}

Quaternion Quaternion::operator+() const
{
    Quaternion res(x, y, z, t);
    return res;
}

Quaternion Quaternion::operator-() const
{
    Quaternion res(-x, -y, -z, -t);
    return res;
}

Quaternion &Quaternion::operator++()
{
    x += 1.0;
    return *this;
}

Quaternion Quaternion::operator++(int)
{
    Quaternion res(*this);
    ++(*this);
    return res;
}

Quaternion &Quaternion::operator--()
{
    x -= 1.0;
    return *this;
}

Quaternion Quaternion::operator--(int)
{
    Quaternion res(*this);
    --(*this);
    return res;
}

Quaternion &Quaternion::operator+=(const Quaternion &right)
{
    x += right.x;
    y += right.y;
    z += right.z;
    t += right.t;
    return *this;
}

Quaternion &Quaternion::operator-=(const Quaternion &right)
{
    x -= right.x;
    y -= right.y;
    z -= right.z;
    t -= right.t;
    return *this;
}

Quaternion &Quaternion::operator*=(const Quaternion &right)
{
    double newX = x * right.x - y * right.y - z * right.z - t * right.t;
    double newY = x * right.y + y * right.x + z * right.t - t * right.z;
    double newZ = x * right.z - y * right.t + z * right.x + t * right.y;
    double newT = x * right.t + y * right.z - z * right.y + t * right.x;
    x = newX;
    y = newY;
    z = newZ;
    t = newT;
    return *this;
}

Quaternion &Quaternion::operator/=(const Quaternion &right)
{
    *this = *this / right;
    return *this;
}

Quaternion operator+(const Quaternion &left, const Quaternion &right)
{
    return Quaternion(left.x + right.x, left.y + right.y, left.z + right.z, left.t + right.t);
}

Quaternion operator-(const Quaternion &left, const Quaternion &right)
{
    return Quaternion(left.x - right.x, left.y - right.y, left.z - right.z, left.t - right.t);
}

Quaternion operator*(const Quaternion &left, const Quaternion &right)
{
    return Quaternion(left.x * right.x - left.y * right.y - left.z * right.z - left.t * right.t,
                      left.x * right.y + left.y * right.x + left.z * right.t - left.t * right.z,
                      left.x * right.z - left.y * right.t + left.z * right.x + left.t * right.y,
                      left.x * right.t + left.y * right.z - left.z * right.y + left.t * right.x);
}

Quaternion operator/(const Quaternion &left, const Quaternion &right)
{
    return Quaternion(left.x, left.y, left.z, left.t) * (right.getReciprocal());
}

double Quaternion::getNormSquare() const
{
    return x * x + y * y + z * z + t * t;
}

double Quaternion::getNorm() const
{
    return std::sqrt(x * x + y * y + z * z + t * t);
}

Quaternion Quaternion::getConjugation() const
{
    return Quaternion(x, -y, -z, -t);
}

Quaternion Quaternion::getReciprocal() const
{
    double div = x * x + y * y + z * z + t * t;
    return Quaternion(x / div, y / div, z / div, t / div);
}

Quaternion &Quaternion::setNorm(double newNorm)
{
    double mul = newNorm / std::sqrt(x * x + y * y + z * z + t * t);
    x *= mul;
    y *= mul;
    z *= mul;
    t *= mul;
    return *this;
}

Quaternion &Quaternion::conjugate()
{
    y *= -1.0;
    z *= -1.0;
    z *= -1.0;
    return *this;
}

Quaternion &Quaternion::reciproc()
{
    double div = x * x + y * y + z * z + t * t;
    x /= div;
    y /= -div;
    z /= -div;
    t /= -div;
    return *this;
}

double Quaternion::getX() const
{
    return x;
}

double Quaternion::getY() const
{
    return y;
}

double Quaternion::getZ() const
{
    return z;
}

double Quaternion::getT() const
{
    return t;
}

std::complex<double> Quaternion::getXY() const
{
    return std::complex<double>(x, y);
}

std::complex<double> Quaternion::getZT() const
{
    return std::complex<double>(z, t);
}

void Quaternion::setX(double newX)
{
    x = newX;
}

void Quaternion::setY(double newY)
{
    y = newY;
}

void Quaternion::setZ(double newZ)
{
    z = newZ;
}

void Quaternion::setT(double newT)
{
    t = newT;
}

void Quaternion::setXY(double newX, double newY)
{
    x = newX;
    y = newY;
}

void Quaternion::setXY(std::complex<double> newXY)
{
    x = newXY.real();
    y = newXY.imag();
}

void Quaternion::setXYZT(double newX, double newY, double newZ, double newT)
{
    x = newX;
    y = newY;
    z = newZ;
    t = newT;
}

void Quaternion::setXYZT(std::complex<double> newXY, std::complex<double> newZT)
{
    x = newXY.real();
    y = newXY.imag();
    z = newZT.real();
    t = newZT.imag();
}

void Quaternion::setXYZT(const Quaternion &newXYZT)
{
    x = newXYZT.x;
    y = newXYZT.y;
    z = newXYZT.z;
    t = newXYZT.t;
}

std::ostream &operator<<(std::ostream &os, const Quaternion &q)
{
    os << '(' << q.x << ", " << q.y << ", " << q.z << ", " << q.t << ')';
    return os;
}
