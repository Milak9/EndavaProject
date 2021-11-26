#include <string>
#include <map>
#include "DockDetector.h"

DockDetector::DockDetector()
{
    try
    {
        // 1. b vvvPovezivanje na server
        m_wlanWrapper = new WlanWrapper{ maxClientVersion, &curVersion };
        std::cout << "Connected to the server" << std::endl;
    }
    catch (std::string errorMsg)
    {
        std::cerr << errorMsg << std::endl;
    }
}

DockDetector::~DockDetector()
{
    if (m_wlanWrapper != nullptr)
    {
        delete m_wlanWrapper;
        m_wlanWrapper = nullptr;
    }
}

void DockDetector::AvailableNetworks()
{
    try
    {
        // 2. Lista dostupnih WLAN interfejsa na lokalu
        // Ovo ce biti unique_ptr
        auto wlanInterfaceListUniquePtr = m_wlanWrapper->WlanEnumInterfacesWLAN();
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
        auto availableNetworkUniquePtr = m_wlanWrapper->WlanGetAvailableNetworkListOnLAN(&interfaceInfo->InterfaceGuid, 0);

        int numberOfItems = availableNetworkUniquePtr->dwNumberOfItems;
        std::cout << "Number of available networks: " << numberOfItems << std::endl;

        PWLAN_AVAILABLE_NETWORK availableNet = NULL;

        for (int i = 0; i < numberOfItems; ++i)
        {
            availableNet = (WLAN_AVAILABLE_NETWORK*)&availableNetworkUniquePtr->Network[i];

            if (lstrlen(availableNet->strProfileName)) continue;

            if (availableNet->dot11Ssid.uSSIDLength == 0)
            {
                std::cout << "This network doesn't have name" << std::endl;
            }
            else
            {
                std::string networkNameString{ (char*)availableNet->dot11Ssid.ucSSID, (size_t)availableNet->dot11Ssid.uSSIDLength };
                std::cout << networkNameString << std::endl;
            }
        }
    }
    catch (const std::string errorMsg)
    {
        std::cerr << errorMsg << std::endl;
    }
}