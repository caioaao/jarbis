#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <cstdint>
#include <csignal>
#include <cstdlib>
// #include <cunistd>


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

    while(!UI->ui_exited())
    {
        UI->render();
    }
    cleanup_and_exit(0);
}
