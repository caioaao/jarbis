#ifndef CAR_H
#define CAR_H

#include "simulator/Ui.h"

namespace simulator
{
    class Car:
        public UiElement
    {
    private:
        int x_;
        int y_;
        unsigned int r_;
    public:
        Car(unsigned int r);
        int x(void);
        int y(void);
        unsigned int r(void);

        void draw(void);
        void update(void);
    };
};

#endif
