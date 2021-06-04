#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	cout << "\t\t....MAILSLOTS CLIENT...." << endl;
	HANDLE hCreatefile;
	BOOL bWriteFile;
	DWORD dwNoBytesWrite;
	char szWriteFileBuffer[1023];
	DWORD dwWriteFileBufferSize = sizeof(szWriteFileBuffer);
	hCreatefile = CreateFile(
		L"\\\\.\\mailslot\\MYMAILSLOTS",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (INVALID_HANDLE_VALUE == hCreatefile)
	{
		cout << "File Creation Failde Error No - " << GetLastError() << endl;
	}
	cout << "File Creation Success" << endl;
	cout << "Write Your Message" << endl;
	fgets(szWriteFileBuffer, dwWriteFileBufferSize, stdin);
	bWriteFile = WriteFile(
		hCreatefile,
		szWriteFileBuffer,
		dwWriteFileBufferSize,
		&dwNoBytesWrite,
		NULL
	);
	if (bWriteFile == FALSE)
	{
		cout << "WriteFile Failed Error No - " << GetLastError() << endl;
	}
	cout << "WriteFile Success" << endl;
	CloseHandle(hCreatefile);
	system("Pause");
}
