#include "simulator/Car.h"

namespace simulator
{
    Car::Car(unsigned int r)
    {
        r_ = r;
        x_ = y_ = 0;
    }

    int
    Car::x(void)
    {
        return x_;
    }


    int
    Car::y(void)
    {
        return y_;
    }


    unsigned int
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
        for(int i = x_ - (int)r_; i <= x_ + (int)r_; ++i)
        {
            ui_->update_pixel(i, y_, 1);
        }

        for(int i = y_ - (int)r_; i <= y_ + (int)r_; ++i)
        {
            ui_->update_pixel(x_, i, 1);
        }
    }
};
