#ifndef STATICOBJECT_HPP
#define STATICOBJECT_HPP

class StaticObject
{
    StaticObject() = delete;
    StaticObject(const StaticObject &rhs) = delete;
    StaticObject(StaticObject &&rhs) = delete;
    StaticObject &operator=(const StaticObject &rhs) = delete;
    StaticObject &operator=(StaticObject &&rhs) = delete;
    ~StaticObject() = delete;
};

#endif // STATICOBJECT_HPP
