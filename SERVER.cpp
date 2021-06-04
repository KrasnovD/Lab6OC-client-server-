#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	HANDLE hSlots;
	BOOL bReadfile;
	DWORD dwNoBytesRead;
	char szReadFileBuffer[1023];
	DWORD dwReadFileBufferSize = sizeof(szReadFileBuffer);
	hSlots = CreateMailslot(
		L"\\\\.\\mailslot\\MYMAILSLOTS",
		0,
		MAILSLOT_WAIT_FOREVER,
		NULL);
	if (hSlots == INVALID_HANDLE_VALUE)
	{
		cout << "MailSlots Creation Failed and Error No - " << GetLastError() << endl;
	}
	cout << "MailSlots Creation Success" << endl;
	bReadfile = ReadFile(
		hSlots,
		szReadFileBuffer,
		dwReadFileBufferSize,
		&dwNoBytesRead,
		NULL
	);
	if (bReadfile == FALSE)
	{
		cout << "ReadFile Failed Error No - " << GetLastError() << endl;
	}
	cout << "ReadFile Success" << endl;
	cout << "MESSAGE FROM CLIENT -> " << szReadFileBuffer << endl;
	CloseHandle(hSlots);
	system("Pause");
}
