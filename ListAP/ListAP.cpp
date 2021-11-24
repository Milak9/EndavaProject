#include <iostream>
#include "../WlanWrapper/WlanWrapper.h"
#include <map>

int main()
{
    int retVal = 0;

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
        retVal = 1;
    }
    else
    {
        std::cout << "Num of interfaces: " << wlanInterfaceList->dwNumberOfItems << std::endl;

        WCHAR guidOfTheInterfaceString[39] = { 0 };

        PWLAN_INTERFACE_INFO interfaceInfo = wlanInterfaceList->InterfaceInfo;
        int numOfCharacters = StringFromGUID2(interfaceInfo->InterfaceGuid, (LPOLESTR)&guidOfTheInterfaceString, sizeof(guidOfTheInterfaceString) / sizeof(*guidOfTheInterfaceString));

        if (numOfCharacters == 0)
        {
            std::cout << "StringFromGUID2 failed" << std::endl;
        }
        else
        {
            std::cout << "Guid of the interface 1: " << guidOfTheInterfaceString << std::endl;
        }

        PWLAN_AVAILABLE_NETWORK_LIST netList = NULL;

        // 3. Lista dostupnih mreza
        DWORD availableNetworkResult = wlanWrapper.WlanGetAvailableNetworkListOnLAN(clientHandle, &interfaceInfo->InterfaceGuid, 0, NULL, &netList);

        if (availableNetworkResult != ERROR_SUCCESS)
        {
            std::cout << "WlanGetAvailableNetworkListOnLAN failed with error: " << availableNetworkResult << std::endl;
            retVal = 1;
        }
        else
        {
            std::cout << "Number of available networks: " << netList->dwNumberOfItems << std::endl;

            PWLAN_AVAILABLE_NETWORK availableNet = NULL;

            std::map<std::string, int> networkNames = {};

            for (int i = 0; i < netList->dwNumberOfItems; i++)
            {
                availableNet = (WLAN_AVAILABLE_NETWORK*)&netList->Network[i];

                if (availableNet->dot11Ssid.uSSIDLength == 0)
                {
                    std::cout << "This network doesn't have name" << std::endl;
                }
                else
                {
                    std::string networkNameString = "";

                    for (int j = 0; j < availableNet->dot11Ssid.uSSIDLength; j++)
                    {
                        networkNameString = networkNameString + (char)availableNet->dot11Ssid.ucSSID[j];
                    }
                    
                    if (networkNames.find(networkNameString) != networkNames.end())
                    {
                        networkNames[networkNameString] += 1;
                    }
                    else
                    {
                        networkNames[networkNameString] = 1;
                    }
                }
            }

            for (const auto pair : networkNames)
            {
                std::cout << pair.first << std::endl;
            }
        }


        if (netList != NULL)
        {
            wlanWrapper.WlanFreeAllocatedMemory(netList);
            netList = NULL;
        }
    }
    

    if (wlanInterfaceList != NULL) {
        wlanWrapper.WlanFreeAllocatedMemory(wlanInterfaceList);
        wlanInterfaceList = NULL;
    }

    return retVal;
}