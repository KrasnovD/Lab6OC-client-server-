#include <windows.h>
#include <stdio.h>
#include <string.h>
#define BUFSIZE 1024 * 5

LPWSTR CharToLPWSTR(LPCSTR char_string)
{
	LPWSTR res;
	DWORD res_len = MultiByteToWideChar(1251, 0, char_string, -1, NULL, 0);
	res = (LPWSTR)GlobalAlloc(GPTR, (res_len + 1) * sizeof(WCHAR));
	MultiByteToWideChar(1251, 0, char_string, -1, res, res_len);
	return res;
}

STARTUPINFO si;
HANDLE hReadPipe, hWrPipe, hRePipe, hWritePipe;

int main()
{
	char     buff[BUFSIZE] = { 0 };
	int      ret;


	SECURITY_ATTRIBUTES sa;

	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = 0;
	sa.bInheritHandle = TRUE;

	CreatePipe(&hRePipe, &hWritePipe, &sa, 0);
	CreatePipe(&hReadPipe, &hWrPipe, &sa, 0);

	//memset(&si, 0, sizeof(si));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.wShowWindow = SW_HIDE;
	si.hStdOutput = hWritePipe;
	si.hStdInput = hReadPipe;


	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));

	char cmdLine[] = "cmd.exe";
	CreateProcess(NULL, CharToLPWSTR(cmdLine), NULL, NULL, 1, 0, NULL, NULL, &si, &pi);
	unsigned long lBytesWrite;
	DWORD buffer;


	WriteFile(hWrPipe, "dir C:\\ \n", sizeof("dir C:\\ \n"), &buffer, NULL);

	while (ReadFile(hRePipe, buff, BUFSIZE, &buffer, NULL))
	{
		printf("%s", buff);
		memset(&buff, 0, sizeof(buff));
	}

	WriteFile(hWritePipe, "exit\n", sizeof("exit\n"), &buffer, NULL);
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(hRePipe);
	CloseHandle(hWrPipe);
	return 0;
}