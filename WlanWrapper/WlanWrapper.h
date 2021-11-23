#include <windows.h>
#include <wlanapi.h>

class WlanWrapper
{
public:
 
	WlanWrapper();
	~WlanWrapper();

	// Otvaranje konekcije ka serveru
	DWORD WlanOpenHandleToServer(DWORD dwVersion, PVOID pReserved, PDWORD  pdwNegotiatedVersion, PHANDLE phClientHandle);

	// Zatvaranje konekcije
	DWORD WlanCloseHandleToServer(HANDLE hClientHandle, PVOID  pReserved);

	DWORD WlanEnumLANInterfaces(HANDLE hClientHandle, PVOID pReserved, PWLAN_INTERFACE_INFO_LIST* ppInterfaceList);


};