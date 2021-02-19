#include <windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <Psapi.h>
LPVOID __IMAGE_BASE(const HANDLE _hProc)
{
	TCHAR buff[1024];
	GetProcessImageFileName(_hProc, (LPWSTR)buff, MAX_PATH);
	HMODULE hMods[1024];
	DWORD cbNeeded;
	DWORD i;

	if (EnumProcessModules(_hProc, hMods, sizeof(hMods), &cbNeeded))
	{
		for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			WCHAR szModName[MAX_PATH];
			if (GetModuleFileNameEx(_hProc, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
			{
				std::wstring wstrModName = szModName;
				std::wstring wstrModContain = L"crackme.exe";
				if (wstrModName.find(wstrModContain) != std::string::npos)
				{

					MODULEINFO modinfo;
					if (GetModuleInformation(_hProc, hMods[i], &modinfo, sizeof(MODULEINFO)) != NULL)
					{


						return modinfo.lpBaseOfDll;
					}


				}
			}
		}
	}
}
DWORD __PID(LPCWSTR _cPE) // GetPid proc &&  
{
	HANDLE SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (SnapShot == NULL)
	{
		std::cout << "Error:" << GetLastError() << std::endl;
	}
	PROCESSENTRY32 __Proc;
	__Proc.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(SnapShot, &__Proc) == 0x1)
	{
		do
		{
			if (wcscmp(_cPE, __Proc.szExeFile) == 0x0)
			{

				return __Proc.th32ProcessID;
			}

		} while (Process32Next(SnapShot, &__Proc));
	}
	return -1;
}

int main()
{
	SetConsoleTitleA("[__keygen by blessedq]");
	const auto _hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, __PID(L"crackme.exe"));
	if (_hProc == NULL)
	{
		std::cout << "Error:" << GetLastError() << std::endl;
	}
	LPVOID IMAGE_BASE = (__IMAGE_BASE(_hProc));
	LPVOID addr_SECTION_TEXT = (LPVOID**)IMAGE_BASE + 0x400;
	int addr_data_serial_key = (int)addr_SECTION_TEXT + 0x38640;


	BYTE DATA_SERIAL_KEY[0x104] = {};

	for (DWORD i = 0; i < sizeof(DATA_SERIAL_KEY) - 1; i++)
	{
		if (ReadProcessMemory(_hProc, (LPVOID*)(addr_data_serial_key + i), &DATA_SERIAL_KEY[i], 0x1, NULL) != NULL)
		{
			if (DATA_SERIAL_KEY[i] == 0x0)
			{
				
				break;
			}
			DATA_SERIAL_KEY[i] -=0x1;
			
		}
	}
	for (DWORD i = 0; i < sizeof(DATA_SERIAL_KEY) - 1; i++)
	{
		if (DATA_SERIAL_KEY[i] == 0x0)
		{
			DATA_SERIAL_KEY[i] += 0x2;
			break;
		}
		if (i < 4)
		{
			DATA_SERIAL_KEY[i] = (int)DATA_SERIAL_KEY[i] + (int)DATA_SERIAL_KEY[i] + 0x2;
		}
		else
		{
			DATA_SERIAL_KEY[i] += 0x2;
		
		}
		
	}
	printf("key->");
	for (DWORD i = 0; i < sizeof(DATA_SERIAL_KEY) - 1; i++)
	{
		int strlen_username = strlen((char*)DATA_SERIAL_KEY);
		if (DATA_SERIAL_KEY[i] == 0x0)

			
		{
			break;
		}
		if ((INT16)DATA_SERIAL_KEY[i] < 0x000000030)
		{
			do
			{
				__asm {int 3h}
				(int)DATA_SERIAL_KEY[i]++;
			} while (DATA_SERIAL_KEY[i] < 0x30);
		}
			
		
		
		for (; DATA_SERIAL_KEY[i] > 0x39; strlen_username > 0x10 ? DATA_SERIAL_KEY[i] -= strlen_username + 0x1 : DATA_SERIAL_KEY[i] += (  0xAAAAAAAB * strlen_username ) >> 0x1)
		{
			

			if(DATA_SERIAL_KEY[i] >= 0x61)
			{
				break;
			}
		}
		if (DATA_SERIAL_KEY[i] > 0x7A) 
		{
			do
			{
				DATA_SERIAL_KEY[i] = ((int)DATA_SERIAL_KEY[i] - strlen_username) >> 0x1;
			} while (DATA_SERIAL_KEY[i] > 0x7A);
		}
	
		std::cout << DATA_SERIAL_KEY[i];
	}
	printf("\n");
	system("pause\n");
	return 0;
}