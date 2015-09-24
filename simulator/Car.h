#ifndef CAR_H
#define CAR_H

#include <cstdint>

#include "simulator/Ui.h"

namespace simulator
{
    class Car:
        public UiElement
    {
    private:
        int32_t x_;
        int32_t y_;
        uint32_t r_;
    public:
        Car(uint32_t r);
        int32_t x(void);
        int32_t y(void);
        uint32_t r(void);

        void draw(void);
        void update(void);
    };
};

#endif
