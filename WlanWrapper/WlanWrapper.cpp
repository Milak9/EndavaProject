// WlanWrapper.cpp : Defines the functions for the static library.
//
#include <iostream>
#include "WlanWrapper.h"

WlanWrapper::WlanWrapper(DWORD dwVersion, PVOID pReserved, PDWORD  pdwNegotiatedVersion, PHANDLE phClientHandle)
	: m_dwVersion(dwVersion),m_pReserved(pReserved), m_pdwNegotiatedVersion(pdwNegotiatedVersion), m_phClientHandle(phClientHandle)
{
	DWORD openHandleResult = WlanOpenHandle(m_dwVersion, m_pReserved, m_pdwNegotiatedVersion, m_phClientHandle);

	if (openHandleResult != ERROR_SUCCESS)
	{
		throw "WlanOpenHandle failed with error: " + openHandleResult;
	}
}

WlanWrapper::~WlanWrapper()
{
	DWORD closeHandleResult = WlanCloseHandle(m_phClientHandle, m_pReserved);

	if (closeHandleResult != ERROR_SUCCESS)
	{
		throw "WlanCloseHandle failed with error: " + closeHandleResult;
	}
}


DWORD WlanWrapper::WlanGetAvailableNetworkListOnLAN(HANDLE hClientHandle, const GUID* pInterfaceGuid, DWORD dwFlags, PVOID pReserved, PWLAN_AVAILABLE_NETWORK_LIST* ppAvailableNetworkList)
{
	return WlanGetAvailableNetworkList(hClientHandle, pInterfaceGuid, dwFlags, pReserved, ppAvailableNetworkList);
}


DWORD WlanWrapper::WlanEnumInterfacesWLAN(HANDLE hClientHandle, PVOID pReserved, PWLAN_INTERFACE_INFO_LIST* ppInterfaceList)
{
	return WlanEnumInterfaces(hClientHandle, pReserved, ppInterfaceList);
}

void WlanWrapper::WlanFreeAllocatedMemory(PVOID pMemory)
{
	WlanFreeMemory(pMemory);
}
