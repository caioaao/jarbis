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

static void cleanup_and_exit_(int exit_code);
static void sigint_handler_(int s);

int main()
{
    struct sigaction sigint_action;

    sigint_action.sa_handler = sigint_handler_;
    sigemptyset(&sigint_action.sa_mask);
    sigint_action.sa_flags = 0;
    sigaction(SIGINT, &sigint_action, NULL);

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

    cleanup_and_exit_(0);
}


void
sigint_handler_(int s)
{
    base::corelog() << base::log_level(base::LOG_CRIT)
                    << "SIGINT(" << s << ") captured\n";
    cleanup_and_exit_(0);
}


void
cleanup_and_exit_(int exit_code)
{
    base::corelog() << base::log_level(base::LOG_CRIT) <<
        "Cleaning up and exiting...\n";
    exit(exit_code);
}
