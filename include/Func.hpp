/*
 * A basic function library.
 * Copyright (C) 2020  Myrrhe <email>
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

#ifndef FUNC_HPP
#define FUNC_HPP
#include "Global.hpp"
#include "Quaternion.hpp"
#include "StaticObject.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>

std::ostream &operator<<(std::ostream &os, const sf::Color &right);

std::ostream &operator<<(std::ostream &os, const sf::Vector2<int> &right);
std::ostream &operator<<(std::ostream &os, const sf::Vector2<float> &right);
std::ostream &operator<<(std::ostream &os, const sf::Vector2<double> &right);

std::ostream &operator<<(std::ostream &os, const sf::Rect<int> &right);
std::ostream &operator<<(std::ostream &os, const sf::Rect<float> &right);
std::ostream &operator<<(std::ostream &os, const sf::Rect<double> &right);

std::ostream &operator<<(std::ostream &os, const sf::Transform &right);

std::ostream &operator<<(std::ostream &os, const sf::Time &right);

std::ostream &operator<<(std::ostream &os, const std::vector<std::string> &right);
std::ostream &operator<<(std::ostream &os, const std::vector<long unsigned int> &right);
std::ostream &operator<<(std::ostream &os, const std::vector<double> &right);

sf::Rect<int> operator|(const sf::Rect<int> &left, const sf::Rect<int> &right);
sf::Rect<float> operator|(const sf::Rect<float> &left, const sf::Rect<float> &right);
sf::Rect<double> operator|(const sf::Rect<double> &left, const sf::Rect<double> &right);

sf::Rect<int> operator+(const sf::Rect<int> &left, const sf::Vector2<int> &right);
sf::Rect<float> operator+(const sf::Rect<float> &left, const sf::Vector2<float> &right);
sf::Rect<double> operator+(const sf::Rect<double> &left, const sf::Vector2<double> &right);

sf::Rect<int> &operator+=(sf::Rect<int> &left, const sf::Vector2<int> &right);
sf::Rect<float> &operator+=(sf::Rect<float> &left, const sf::Vector2<float> &right);
sf::Rect<double> &operator+=(sf::Rect<double> &left, const sf::Vector2<double> &right);

sf::Rect<int> operator-(const sf::Rect<int> &left, const sf::Vector2<int> &right);
sf::Rect<float> operator-(const sf::Rect<float> &left, const sf::Vector2<float> &right);
sf::Rect<double> operator-(const sf::Rect<double> &left, const sf::Vector2<double> &right);

sf::Rect<int> &operator-=(sf::Rect<int> &left, const sf::Vector2<int> &right);
sf::Rect<float> &operator-=(sf::Rect<float> &left, const sf::Vector2<float> &right);
sf::Rect<double> &operator-=(sf::Rect<double> &left, const sf::Vector2<double> &right);

sf::Rect<int> operator*(const sf::Rect<int> &left, int right);
sf::Rect<float> operator*(const sf::Rect<float> &left, float right);
sf::Rect<double> operator*(const sf::Rect<double> &left, double right);

sf::Rect<int> &operator*=(sf::Rect<int> &left, int right);
sf::Rect<float> &operator*=(sf::Rect<float> &left, float right);
sf::Rect<double> &operator*=(sf::Rect<double> &left, double right);

sf::Rect<int> operator/(const sf::Rect<int> &left, int right);
sf::Rect<float> operator/(const sf::Rect<float> &left, float right);
sf::Rect<double> operator/(const sf::Rect<double> &left, double right);

sf::Rect<int> &operator/=(sf::Rect<int> &left, int right);
sf::Rect<float> &operator/=(sf::Rect<float> &left, float right);
sf::Rect<double> &operator/=(sf::Rect<double> &left, double right);

sf::Rect<int> operator*(const sf::Rect<int> &left, const sf::Vector2<int> &right);
sf::Rect<float> operator*(const sf::Rect<float> &left, const sf::Vector2<float> &right);
sf::Rect<double> operator*(const sf::Rect<double> &left, const sf::Vector2<double> &right);

sf::Rect<int> &operator*=(sf::Rect<int> &left, const sf::Vector2<int> &right);
sf::Rect<float> &operator*=(sf::Rect<float> &left, const sf::Vector2<float> &right);
sf::Rect<double> &operator*=(sf::Rect<double> &left, const sf::Vector2<double> &right);

sf::Rect<int> operator/(const sf::Rect<int> &left, const sf::Vector2<int> &right);
sf::Rect<float> operator/(const sf::Rect<float> &left, const sf::Vector2<float> &right);
sf::Rect<double> operator/(const sf::Rect<double> &left, const sf::Vector2<double> &right);

sf::Rect<int> &operator/=(sf::Rect<int> &left, const sf::Vector2<int> &right);
sf::Rect<float> &operator/=(sf::Rect<float> &left, const sf::Vector2<float> &right);
sf::Rect<double> &operator/=(sf::Rect<double> &left, const sf::Vector2<double> &right);

int operator*(const sf::Vector2<int> &left, const sf::Vector2<int> &right);
unsigned int operator*(const sf::Vector2<unsigned int> &left, const sf::Vector2<unsigned int> &right);
float operator*(const sf::Vector2<float> &left, const sf::Vector2<float> &right);
double operator*(const sf::Vector2<double> &left, const sf::Vector2<double> &right);

int operator^(const sf::Vector2<int> &left, const sf::Vector2<int> &right);
float operator^(const sf::Vector2<float> &left, const sf::Vector2<float> &right);
double operator^(const sf::Vector2<double> &left, const sf::Vector2<double> &right);

#if DEBUG
#define debugLog(...)                                                                                                      \
    {                                                                                                                      \
        char debugLogStr[100];                                                                                             \
        sprintf(debugLogStr, __VA_ARGS__);                                                                                 \
        std::cout << "[" << __FILE__ << "][" << __FUNCTION__ << "][Line " << __LINE__ << "] " << debugLogStr << std::endl; \
    }
#else
#define debugLog(...)
#endif // DEBUG

class Func final : private StaticObject
{
public:
    static constexpr double m_e = 2.71828182845904523536;
    static constexpr double m_log2e = 1.44269504088896340736;
    static constexpr double m_log10e = 0.434294481903251827651;
    static constexpr double m_ln2 = 0.693147180559945309417;
    static constexpr double m_ln10 = 2.30258509299404568402;
    static constexpr double m_pi = 3.14159265358979323846;
    static constexpr double m_2pi = 6.28318530717958647692;
    static constexpr double m_pi_2 = 1.57079632679489661923;
    static constexpr double m_pi_4 = 0.785398163397448309616;
    static constexpr double m_1_pi = 0.318309886183790671538;
    static constexpr double m_2_pi = 0.636619772367581343076;
    static constexpr double m_2_sqrtpi = 1.12837916709551257390;
    static constexpr double m_sqrt2 = 1.41421356237309504880;
    static constexpr double m_1_sqrt2 = 0.707106781186547524401;
    static constexpr double m_epsilon = 0.00000000000000000001;

    static constexpr double m_1_60s = 1.0 / 60.0;

    static constexpr float m_e_f = 2.71828182845904523536f;
    static constexpr float m_log2e_f = 1.44269504088896340736f;
    static constexpr float m_log10e_f = 0.434294481903251827651f;
    static constexpr float m_ln2_f = 0.693147180559945309417f;
    static constexpr float m_ln10_f = 2.30258509299404568402f;
    static constexpr float m_pi_f = 3.14159265358979323846f;
    static constexpr float m_2pi_f = 6.28318530717958647692f;
    static constexpr float m_pi_2_f = 1.57079632679489661923f;
    static constexpr float m_pi_4_f = 0.785398163397448309616f;
    static constexpr float m_1_pi_f = 0.318309886183790671538f;
    static constexpr float m_2_pi_f = 0.636619772367581343076f;
    static constexpr float m_2_sqrtpi_f = 1.12837916709551257390f;
    static constexpr float m_sqrt2_f = 1.41421356237309504880f;
    static constexpr float m_1_sqrt2_f = 0.707106781186547524401f;
    static constexpr float m_epsilon_f = 0.00000000000000000001f;

    static constexpr float m_1_60sf = 1.0f / 60.0f;

    enum class Interp : long unsigned int
    {
        LIN,
        ACC,
        BRA,
        SIN,
        SFO,

        SIN0
    };

    static sf::Vector2<float> floor(const sf::Vector2<float> &v);

    static float getNorm(const sf::Vector2<float> &v);
    static double getNorm(const sf::Vector2<double> &v);

    static float getNormSquared(const sf::Vector2<float> &v);
    static double getNormSquared(const sf::Vector2<double> &v);

    static sf::Vector2<int> getInverted(const sf::Vector2<int> &v);
    static sf::Vector2<float> getInverted(const sf::Vector2<float> &v);
    static sf::Vector2<double> getInverted(const sf::Vector2<double> &v);

    static sf::Vector2<float> getNormalized(const sf::Vector2<float> &v);
    static sf::Vector2<double> getNormalized(const sf::Vector2<double> &v);

    static float radToDeg(float radians);
    static double radToDeg(double radians);

    static float degToRad(float degree);
    static double degToRad(double degree);

    static float getRotationAngle(const sf::Vector2<float> &v);   // Angle in radians
    static double getRotationAngle(const sf::Vector2<double> &v); // Angle in radians

    static float getAngleBetween(const sf::Vector2<float> &v1, const sf::Vector2<float> &v2);    // Angle in radians
    static double getAngleBetween(const sf::Vector2<double> &v1, const sf::Vector2<double> &v2); // Angle in radians

    static sf::Vector2<float> getRotated(const sf::Vector2<float> &vec, float angle);
    static sf::Vector2<double> getRotated(const sf::Vector2<double> &vec, double angle);

    static double getCoeff(double coeff, Interp interp = Interp::LIN, bool limiter = true);
    static double getCoeff(double x, double X, Interp interp = Interp::LIN, bool limiter = true);

    static sf::Color colorBalance(const sf::Color &color1, const sf::Color &color2, double coeff, Interp interp = Interp::LIN);

    static std::string getStringHourPrecise();
    static std::string getStringHourVeryPrecise();
    static std::array<long unsigned int, 4> getHourVeryPrecise();

    static std::vector<std::string> split(const std::string &s, char delim);

    static const std::vector<std::string> &split(const std::string_view &s, const std::string_view &delim);

    static std::vector<std::u32string> split(const std::u32string &s, char32_t delim);

    static const std::vector<std::u32string> &split(const std::u32string_view &s, const std::u32string_view &delim);

    static long unsigned int imod(long int i1, long int i2);

    static double dmod(double numer, double denom);

    static float f_mod(float numer, float denom);

    static long unsigned int power(long unsigned int base, long unsigned int exponent);

    static sf::String stringTosfString(const std::string_view &str);

    static sf::String evaluateSpecialChars(const sf::String &str);

    static std::vector<std::string> getDir(const std::string &dir);

    static bool fileExist(const std::string &path);

    static std::string getKeyWordLine(const std::string_view &line);

    static std::string getValueLine(const std::string_view &line);

    static std::pair<std::string, std::string> getKeyValueLine(const std::string_view &line);

    static std::u32string getKeyWordLine(const std::u32string_view &line);

    static std::u32string getValueLine(const std::u32string_view &line);

    static std::pair<std::u32string, std::u32string> getKeyValueLine(const std::u32string_view &line);

    static bool isFloat(const std::string &s);

    static bool isFloat(const std::u32string &s);

    static bool isPosInt(const std::string_view &s);

    static bool isPosInt(const std::u32string_view &s);

    static float str32ToF(const std::u32string &s);

    static long unsigned int str32ToLui(const std::u32string &s);

    static long unsigned int str32HexToLui(const std::u32string &s);

    static std::u32string luiTo32Str(long unsigned int n);

    static std::u32string luiTo32StrHex(long unsigned int n);

    static std::u32string fTo32Str(float n);

    static sf::Rect<int> getTextureRect(const sf::Texture *texture);

    enum class RotSeq : long unsigned int
    {
        zyx,
        zyz,
        zxy,
        zxz,
        yxz,
        yxy,
        yzx,
        yzy,
        xyz,
        xyx,
        xzy,
        xzx
    };

    static Quaternion getQuatRot(double angle, const sf::Vector3<double> &axe);

    static Quaternion euler2Quaternion(const sf::Vector3<double> &angle, RotSeq rotSeq);

    static sf::Vector3<double> twoaxisrot(double r11, double r12, double r21, double r31, double r32);

    static sf::Vector3<double> threeaxisrot(double r11, double r12, double r21, double r31, double r32);

    static sf::Vector3<double> quaternion2Euler(const Quaternion &q, RotSeq rotSeq);

    static std::back_insert_iterator<std::u32string> utf8ToUtf32(
        std::string_view::const_iterator be,
        std::string_view::const_iterator en,
        std::back_insert_iterator<std::u32string> output
    );

    static std::back_insert_iterator<std::string> utf32ToUtf8(
        std::u32string_view::const_iterator be,
        std::u32string_view::const_iterator en,
        std::back_insert_iterator<std::string> output
    );

    static std::u32string str8Tostr32(const std::string_view &s);

    static std::string str32Tostr8(const std::u32string_view &s);
};

#endif // FUNC_HPP
