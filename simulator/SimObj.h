#ifndef SIMOBJ_H
#define SIMOBJ_H

namespace simulator {
    class SimObj {
    public:
        virtual void update(void)=0;
    };
}

#endif
