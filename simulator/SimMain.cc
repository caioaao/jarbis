#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <cstdint>

#include "simulator/A4988Simulator.h"
#include "simulator/Ui.h"
#include "simulator/Car.h"
#include "base/debug.h"

std::shared_ptr<simulator::Ui> UI(new simulator::SdlUi());


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
