#include <iostream>
#include "../WlanWrapper/WlanWrapper.h"

int main()
{
    DWORD maxClientVersion = 2;
    DWORD curVersion = 0;
    HANDLE clientHandle = NULL;

    WlanWrapper wlanWrapper;

    // 1. Povezivanje
    DWORD openHandleResult = wlanWrapper.WlanOpenHandleToServer(maxClientVersion, NULL, &curVersion, &clientHandle);

    if (openHandleResult != ERROR_SUCCESS)
    {
        std::cout << "WlanOpenHandleToServer failed with error: " << openHandleResult << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Connected to the server" << std::endl;
    }

    PWLAN_INTERFACE_INFO_LIST wlanInterfaceList = NULL;

    // 2. Lista dostupnih WLAN interfejsa na lokalu
    DWORD enumInterfacesResult = wlanWrapper.WlanEnumInterfacesWLAN(clientHandle, NULL, &wlanInterfaceList);
    
    if (enumInterfacesResult != ERROR_SUCCESS)
    {
        std::cout << "WlanEnumInterfacesWLAN failed with error: " << enumInterfacesResult << std::endl;
        return 1;
    }
    else
    {

    }

    if (wlanInterfaceList != NULL) {
        wlanWrapper.WlanFreeAllocatedMemory(wlanInterfaceList);
        wlanInterfaceList = NULL;
    }

    return 0;
}