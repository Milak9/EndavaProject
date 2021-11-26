#include <iostream>
#include "../WlanWrapper/WlanWrapper.h"
#include <map>
#include <memory>
#include "DockDetector.h"

int main() {
    DockDetector dockDetector{};
    /*auto networks = */ dockDetector.AvailableNetworks();
    //for (auto& network : networks) {
    //    std::cout << network.SSID << std::endl;
    //}

    return 0;
}
