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

	// Funkcija za dohvatanje liste dostupnih mreza
	DWORD WlanGetAvailableNetworkListOnLAN(HANDLE hClientHandle, const GUID* pInterfaceGuid, DWORD dwFlags, PVOID pReserved, PWLAN_AVAILABLE_NETWORK_LIST* ppAvailableNetworkList);

	// Funkcija da se dobije enum svih WLAN interfejsa koji su dostupni na lokalnom kompjuteru
	DWORD WlanEnumInterfacesWLAN(HANDLE hClientHandle, PVOID pReserved, PWLAN_INTERFACE_INFO_LIST* ppInterfaceList);

	// Funkcija za oslobadjanje memorije
	void WlanFreeAllocatedMemory(PVOID pMemory);
};