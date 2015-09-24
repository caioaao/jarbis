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
        for(int32_t i = x_ - r_; i <= (int32_t)(x_ + r_); ++i)
        {
            ui_->update_pixel(i, y_, 1);
        }

        for(int32_t i = y_ - r_; i <= (int32_t)(y_ + r_); ++i)
        {
            ui_->update_pixel(x_, i, 1);
        }
    }
};
