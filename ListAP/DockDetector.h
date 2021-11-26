#ifndef _DOCK_DETECTOR_H
#define _DOCK_DETECTOR_H

#include <iostream>
#include "../WlanWrapper/WlanWrapper.h"

class DockDetector
{
public:

    DockDetector();

    ~DockDetector();

    void AvailableNetworks();

private:

    DWORD maxClientVersion = 2;
    DWORD curVersion = 0;
    HANDLE clientHandle = NULL;

    WlanWrapper *m_wlanWrapper = nullptr;
};

#endif // _DOCK_DETECTOR_H