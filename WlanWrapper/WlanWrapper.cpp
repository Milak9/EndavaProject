// WlanWrapper.cpp : Defines the functions for the static library.
//
#include <iostream>
#include "WlanWrapper.h"

WlanWrapper::WlanWrapper(DWORD dwVersion, PDWORD  pdwNegotiatedVersion)
	: m_dwVersion(dwVersion), m_pdwNegotiatedVersion(pdwNegotiatedVersion)
{
	DWORD openHandleResult = WlanOpenHandle(m_dwVersion, NULL, m_pdwNegotiatedVersion, m_phClientHandle);

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

// VRACAJU UNIQUE_PTR KOJU IMAJU DOLE DEFINISAN DELETER
DWORD WlanWrapper::WlanGetAvailableNetworkListOnLAN(HANDLE hClientHandle, const GUID* pInterfaceGuid, DWORD dwFlags, PVOID pReserved, PWLAN_AVAILABLE_NETWORK_LIST* ppAvailableNetworkList)
{
	return WlanGetAvailableNetworkList(hClientHandle, pInterfaceGuid, dwFlags, pReserved, ppAvailableNetworkList);
}


DWORD WlanWrapper::WlanEnumInterfacesWLAN(HANDLE hClientHandle, PVOID pReserved, PWLAN_INTERFACE_INFO_LIST* ppInterfaceList)
{
	return WlanEnumInterfaces(hClientHandle, pReserved, ppInterfaceList);
}

void WlanWrapper::deleter(void* resource)
{
	WlanFreeMemory(resource);
}