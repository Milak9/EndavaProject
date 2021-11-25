// WlanWrapper.cpp : Defines the functions for the static library.
//
#include <iostream>
#include <memory>
#include "WlanWrapper.h"

WlanWrapper::WlanWrapper(DWORD dwVersion, PDWORD  pdwNegotiatedVersion)
	: m_dwVersion(dwVersion), m_pdwNegotiatedVersion(pdwNegotiatedVersion)
{
	DWORD openHandleResult = WlanOpenHandle(m_dwVersion, NULL, m_pdwNegotiatedVersion, &m_phClientHandle);

	if (openHandleResult != ERROR_SUCCESS)
	{
		throw "WlanOpenHandle failed with error: " + openHandleResult;
	}
}

WlanWrapper::~WlanWrapper()
{
	DWORD closeHandleResult = WlanCloseHandle(m_phClientHandle, NULL);

	if (closeHandleResult != ERROR_SUCCESS)
	{
		throw "WlanCloseHandle failed with error: " + closeHandleResult;
	}
}

std::unique_ptr<WLAN_INTERFACE_INFO_LIST, WlanWrapper::Deleter> WlanWrapper::WlanEnumInterfacesWLAN()
{
	PWLAN_INTERFACE_INFO_LIST wlanInterfaceList = NULL;
	DWORD enumInterfacesResult = WlanEnumInterfaces(m_phClientHandle, NULL, &wlanInterfaceList);

	if (enumInterfacesResult != ERROR_SUCCESS)
	{
		throw "WlanEnumInterfaces failed with error: " + enumInterfacesResult;
	}

	std::unique_ptr<WLAN_INTERFACE_INFO_LIST, Deleter> uniqueList(wlanInterfaceList, Deleter());

	return std::move(uniqueList);
}

std::unique_ptr<WLAN_AVAILABLE_NETWORK_LIST, WlanWrapper::Deleter> WlanWrapper::WlanGetAvailableNetworkListOnLAN(const GUID* pInterfaceGuid, DWORD dwFlags)
{
	PWLAN_AVAILABLE_NETWORK_LIST netList = NULL;

	DWORD availableNetworkResult = WlanGetAvailableNetworkList(m_phClientHandle, pInterfaceGuid, dwFlags, NULL, &netList);

	if (availableNetworkResult != ERROR_SUCCESS)
	{
		throw "WlanGetAvailableNetworkList failed with error: " + availableNetworkResult;
	}

	std::unique_ptr<WLAN_AVAILABLE_NETWORK_LIST, Deleter> uniqueNetworkList(netList, Deleter());

	return std::move(uniqueNetworkList);
}