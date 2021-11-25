#include <windows.h>
#include <wlanapi.h>

class WlanWrapper
{
public:
 
	// Otvara konekciju
	WlanWrapper(DWORD dwVersion, PDWORD  pdwNegotiatedVersion);
	
	// Zatvara konekciju
	~WlanWrapper();

	struct Deleter
	{
		void operator()(void* resource)
		{
			WlanFreeMemory(resource);
		}
	};

	// Funkcija da se dobije enum svih WLAN interfejsa koji su dostupni na lokalnom kompjuteru
	// Vraca unique_ptr sa custom deleter-om, kada se unisti unique poziva se taj deleter
	std::unique_ptr<WLAN_INTERFACE_INFO_LIST, Deleter> WlanEnumInterfacesWLAN();

	// Funkcija za dohvatanje liste dostupnih mreza
	// Vraca unique_ptr sa custom deleter-om, kada se unisti unique poziva se taj deleter
	std::unique_ptr<WLAN_AVAILABLE_NETWORK_LIST, Deleter> WlanGetAvailableNetworkListOnLAN(const GUID* pInterfaceGuid, DWORD dwFlags);

private:
	DWORD m_dwVersion;
	PDWORD  m_pdwNegotiatedVersion;
	HANDLE m_phClientHandle;
};