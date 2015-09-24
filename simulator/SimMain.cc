#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <cstdint>

#include "simulator/A4988Simulator.h"
#include "simulator/Ui.h"
#include "simulator/Car.h"
#include "base/debug.h"

const uint32_t UI_ROWS_ = 30;
const uint32_t UI_COLS_ = 30;

std::shared_ptr<simulator::Ui> UI(new simulator::Ui(UI_ROWS_, UI_COLS_));


int main()
{
    std::shared_ptr<simulator::Car> car(new simulator::Car(2));
    UI->register_element(car);
    car->associate_ui(UI);
    for(;;)
    {
        UI->update();
        UI->render();
    }
}
