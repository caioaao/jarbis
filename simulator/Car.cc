#include "simulator/Car.h"

#include <cstdint>

namespace simulator
{
    Car::Car(uint32_t r)
    {
        r_ = r;
        x_ = y_ = 0;
    }

    int32_t
    Car::x(void)
    {
        return x_;
    }


    int32_t
    Car::y(void)
    {
        return y_;
    }


    uint32_t
    Car::r(void)
    {
        return r_;
    }


    void
    Car::update(void)
    {
        // stub
    }


    void
    Car::draw(void)
    {
        // stub
    }
};
