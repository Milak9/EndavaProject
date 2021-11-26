#ifndef _DOCK_DETECTOR_H
#define _DOCK_DETECTOR_H

#include <iostream>
#include <vector>
#include <string>
#include "../WlanWrapper/WlanWrapper.h"

class DockDetector
{
public:

    DockDetector();

    ~DockDetector();

    std::vector<std::string> AvailableNetworks();

private:

    DWORD maxClientVersion = 2;
    DWORD curVersion = 0;
    HANDLE clientHandle = NULL;

    WlanWrapper *m_wlanWrapper = nullptr;
};

#endif // _DOCK_DETECTOR_H