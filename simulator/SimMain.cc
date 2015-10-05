#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <utility>

#include <cstdint>
#include <csignal>
#include <cstdlib>

#include "base/Logger.h"
#include "simulator/A4988Simulator.h"
#include "simulator/OpenglUi.h"

std::shared_ptr<simulator::Ui> UI(new simulator::OpenglUi());

void cleanup_and_exit(int s)
{
    base::corelog() << base::log_level(base::LOG_CRIT) <<
        "Cleaning up and exiting...\n";
    exit(0);
}


int main()
{
    struct sigaction sigint_handler;

    sigint_handler.sa_handler = cleanup_and_exit;
    sigemptyset(&sigint_handler.sa_mask);
    sigint_handler.sa_flags = 0;
    sigaction(SIGINT, &sigint_handler, NULL);

    std::vector<std::pair<int64_t, int64_t>> pol;

    pol.push_back(std::make_pair(0, 0));
    pol.push_back(std::make_pair(100, 0));
    pol.push_back(std::make_pair(100, 100));
    pol.push_back(std::make_pair(50, 200));
    pol.push_back(std::make_pair(0, 100));
    std::shared_ptr<simulator::UiElement> test_ui =
        UI->create_polygon(pol, simulator::UiColor(255, 0, 255));

    while(!UI->ui_exited())
    {
        UI->render();
    }
    cleanup_and_exit(0);
}
