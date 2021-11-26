#include "DockDetector.h"

DockDetector::DockDetector()
{
    try
    {
        // 1. Povezivanje na server
        m_wlanWrapper = new WlanWrapper{ maxClientVersion, &curVersion };
        std::cout << "Connected to the server" << std::endl;
    }
    catch (const WlanWrapperException &ex)
    {
        std::cerr << ex.what() << std::endl;
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

std::vector<std::string> DockDetector::AvailableNetworks()
{
    try
    {
        GUID guid = GetGuidOfTheInterface();

        // 3. Lista dostupnih mreza
        auto availableNetworkUniquePtr = m_wlanWrapper->WlanGetAvailableNetworkListOnLAN(&guid, 0);

        int numberOfItems = availableNetworkUniquePtr->dwNumberOfItems;
        std::cout << "Number of available networks: " << numberOfItems << std::endl;

        PWLAN_AVAILABLE_NETWORK availableNet = NULL;

        std::vector<std::string> networkNames;

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
                networkNames.push_back(networkNameString);
            }
        }

        return networkNames;
    }
    catch (const WlanWrapperException &ex)
    {
        std::cerr << ex.what() << std::endl;
        return std::vector<std::string>{};
    }
}

GUID DockDetector::GetGuidOfTheInterface()
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

    return interfaceInfo->InterfaceGuid;
}