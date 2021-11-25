#include <iostream>
#include "../WlanWrapper/WlanWrapper.h"
#include <map>
#include <memory>

int main()
{
    int retVal = 0;

    DWORD maxClientVersion = 2;
    DWORD curVersion = 0;
    HANDLE clientHandle = NULL;

    WlanWrapper* wlanWrapper = nullptr;

    try
    {
        // Povezivanje na server
        wlanWrapper = new WlanWrapper(maxClientVersion, &curVersion);
        std::cout << "Connected to the server" << std::endl;;
        
        // 2. Lista dostupnih WLAN interfejsa na lokalu
        // Ovo ce biti unique_ptr
        auto wlanInterfaceListUniquePtr = wlanWrapper->WlanEnumInterfacesWLAN();
        std::cout << "Num of interfaces: " << wlanInterfaceListUniquePtr->dwNumberOfItems << std::endl;

        WCHAR guidOfTheInterfaceString[39] = { 0 };

        PWLAN_INTERFACE_INFO interfaceInfo = wlanInterfaceListUniquePtr->InterfaceInfo;
        int numOfCharacters = StringFromGUID2(interfaceInfo->InterfaceGuid, (LPOLESTR)&guidOfTheInterfaceString, sizeof(guidOfTheInterfaceString) / sizeof(*guidOfTheInterfaceString));

        if (numOfCharacters == 0)
        {
            std::cout << "StringFromGUID2 failed" << std::endl;
        }
        else
        {
            std::cout << "Guid of the interface 1: " << guidOfTheInterfaceString << std::endl;
        }

        // 3. Lista dostupnih mreza
        auto availableNetworkUniquePtr = wlanWrapper->WlanGetAvailableNetworkListOnLAN(&interfaceInfo->InterfaceGuid, 0);

        std::cout << "Number of available networks: " << availableNetworkUniquePtr->dwNumberOfItems << std::endl;

        PWLAN_AVAILABLE_NETWORK availableNet = NULL;

        std::map<std::string, int> networkNames = {};
         
        int numberOfItems = availableNetworkUniquePtr->dwNumberOfItems;

        for (int i = 0; i < numberOfItems; i++)
        {
            availableNet = (WLAN_AVAILABLE_NETWORK*)&availableNetworkUniquePtr->Network[i];

            if (availableNet->dot11Ssid.uSSIDLength == 0)
            {
                std::cout << "This network doesn't have name" << std::endl;
            }
            else
            {
                std::string networkNameString = "";

                for (auto j = 0; j < availableNet->dot11Ssid.uSSIDLength; j++)
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

        for (const auto &pair : networkNames)
        {
            std::cout << pair.first << std::endl;
        }

        delete wlanWrapper;
        wlanWrapper = nullptr;
    }
    catch (const std::string errorMsg)
    {
        std::cerr << errorMsg << std::endl;

        if (wlanWrapper != nullptr)
            delete wlanWrapper;

        return 1;
    }

    return 0;
}
