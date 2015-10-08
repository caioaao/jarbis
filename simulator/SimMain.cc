#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>

#include <cstdint>
#include <csignal>
#include <cstdlib>

#include "base/Logger.h"
#include "simulator/A4988Simulator.h"
#include "simulator/OpenglUi.h"

std::shared_ptr<simulator::Ui> UI(new simulator::OpenglUi());

static void cleanup_and_exit_(int exit_code);
static void sigint_handler_(int s);

int main() {
    struct sigaction sigint_action;

    sigint_action.sa_handler = sigint_handler_;
    sigemptyset(&sigint_action.sa_mask);
    sigint_action.sa_flags = 0;
    sigaction(SIGINT, &sigint_action, NULL);

    std::vector<base::Matrix<float, 2, 1> > pol(
        5, base::Matrix<float, 2, 1>());

    pol[0][0][0] = 0;
    pol[0][1][0] = 0;

    pol[1][0][0] = 100;
    pol[1][1][0] = 0;

    pol[2][0][0] = 100;
    pol[2][1][0] = 100;

    pol[3][0][0] = 50;
    pol[3][1][0] = 200;

    pol[4][0][0] = 0;
    pol[4][1][0] = 100;

    std::shared_ptr<simulator::UiElement> test_ui =
        UI->create_polygon(pol, simulator::UiColor(255, 0, 255));

    while(!UI->ui_exited()) {
        UI->render();
    }

    cleanup_and_exit_(0);
}


void
sigint_handler_(int s) {
    base::corelog() << base::log_level(base::LOG_CRIT)
                    << "SIGINT(" << s << ") captured\n";
    cleanup_and_exit_(0);
}


void
cleanup_and_exit_(int exit_code) {
    base::corelog() << base::log_level(base::LOG_CRIT) <<
        "Cleaning up and exiting...\n";
    exit(exit_code);
}
