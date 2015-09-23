#include <iostream>
#include <string>
#include <map>
#include <memory>

#include "simulator/A4988Simulator.h"
#include "simulator/Ui.h"
#include "base/debug.h"

const unsigned int UI_ROWS_ = 30;
const unsigned int UI_COLS_ = 30;

std::shared_ptr<simulator::Ui> UI(new simulator::Ui(UI_ROWS_, UI_COLS_));


int main()
{
    for(;;)
    {
        UI->update();
        UI->render();
    }
}
