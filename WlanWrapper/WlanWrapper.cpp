// WlanWrapper.cpp : Defines the functions for the static library.
//
#include "WlanWrapper.h"

WlanWrapper::WlanWrapper()
{
}

WlanWrapper::~WlanWrapper()
{
}

DWORD WlanWrapper::WlanOpenHandleToServer(DWORD dwVersion, PVOID pReserved, PDWORD  pdwNegotiatedVersion, PHANDLE phClientHandle)
{
	return WlanOpenHandle(dwVersion, pReserved, pdwNegotiatedVersion, phClientHandle);
}

DWORD WlanWrapper::WlanCloseHandleToServer(HANDLE hClientHandle, PVOID  pReserved)
{
	return WlanCloseHandle(hClientHandle, pReserved);
}

DWORD WlanWrapper::WlanEnumLANInterfaces(HANDLE hClientHandle, PVOID pReserved, PWLAN_INTERFACE_INFO_LIST *ppInterfaceList)
{
	return WlanEnumInterfaces(hClientHandle, pReserved, ppInterfaceList);
}