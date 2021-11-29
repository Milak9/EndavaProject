// WlanWrapper.cpp : Defines the functions for the static library.
//
#include <iostream>
#include <memory>
#include <vector>
#include "WlanWrapper.h"

WlanWrapper::WlanWrapper(DWORD dwVersion, PDWORD  pdwNegotiatedVersion)
	: m_dwVersion(dwVersion), m_pdwNegotiatedVersion(pdwNegotiatedVersion)
{
	DWORD openHandleResult = WlanOpenHandle(m_dwVersion, NULL, m_pdwNegotiatedVersion, &m_phClientHandle);

	if (openHandleResult != ERROR_SUCCESS)
	{
		throw WlanWrapperException("WlanOpenHandle failed with error: " + openHandleResult);
	}
}

WlanWrapper::~WlanWrapper()
{
	DWORD closeHandleResult = WlanCloseHandle(m_phClientHandle, NULL);
}

std::unique_ptr<WLAN_INTERFACE_INFO_LIST, WlanWrapper::Deleter> WlanWrapper::WlanEnumInterfacesWLAN()
{
	PWLAN_INTERFACE_INFO_LIST wlanInterfaceList = NULL;
	DWORD enumInterfacesResult = WlanEnumInterfaces(m_phClientHandle, NULL, &wlanInterfaceList);

	if (enumInterfacesResult != ERROR_SUCCESS)
	{
		throw WlanWrapperException("WlanEnumInterfaces failed with error: " + enumInterfacesResult);
	}

	std::unique_ptr<WLAN_INTERFACE_INFO_LIST, Deleter> uniqueList(wlanInterfaceList, Deleter());

	return uniqueList;
}

std::unique_ptr<WLAN_AVAILABLE_NETWORK_LIST, WlanWrapper::Deleter> WlanWrapper::WlanGetAvailableNetworkListOnLAN(const GUID* pInterfaceGuid, DWORD dwFlags)
{
	PWLAN_AVAILABLE_NETWORK_LIST netList = NULL;

	DWORD availableNetworkResult = WlanGetAvailableNetworkList(m_phClientHandle, pInterfaceGuid, dwFlags, NULL, &netList);

	if (availableNetworkResult != ERROR_SUCCESS)
	{
		throw WlanWrapperException("WlanGetAvailableNetworkList failed with error: " + availableNetworkResult);
	}

	std::unique_ptr<WLAN_AVAILABLE_NETWORK_LIST, Deleter> uniqueNetworkList(netList, Deleter());

	return uniqueNetworkList;
}

std::unique_ptr<WLAN_BSS_LIST, WlanWrapper::Deleter> WlanWrapper::WlanWrapperGetNetworkBssList(const GUID* guid)
{
	PWLAN_BSS_LIST ppWlanBssList = NULL;
	DWORD networkBssResult = WlanGetNetworkBssList(m_phClientHandle, guid, NULL, dot11_BSS_type_any, false, NULL, &ppWlanBssList);

	if (networkBssResult != ERROR_SUCCESS)
	{
		throw WlanWrapperException("WlanWrapperGetNetworkBssList failed with error: " + networkBssResult);
	}

	std::unique_ptr<WLAN_BSS_LIST, Deleter> networkBssList(ppWlanBssList, Deleter());

	return networkBssList;
}

WlanWrapperException::WlanWrapperException(const std::string& errorMsg)
	: m_errorMsg(errorMsg)
{
}

const char* WlanWrapperException::what() const noexcept
{
	return m_errorMsg.c_str();
}