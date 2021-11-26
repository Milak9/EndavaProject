#pragma once

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

    GUID GetGuidOfTheInterface();

private:

    DWORD maxClientVersion = 2;
    DWORD curVersion = 0;
    HANDLE clientHandle = NULL;

    WlanWrapper *m_wlanWrapper = nullptr;
};
