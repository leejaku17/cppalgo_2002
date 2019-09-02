#include <stdio.h>
#include <windows.h>

void FindFile(const char *szMask)
{
	char szPath[MAX_PATH];	// 현재의 경로를 저장할 공간
	WIN32_FIND_DATA fd;
	HANDLE hFile;

	if ((hFile = FindFirstFile(szMask, &fd)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			GetCurrentDirectory(sizeof(szPath), szPath);
			printf("%s\\%s\n", szPath, fd.cFileName);
		} while (FindNextFile(hFile, &fd));
		FindClose(hFile);
	}
	if ((hFile = FindFirstFile("*.*", &fd)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (fd.cFileName[0] == '.' || (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
				continue;
			SetCurrentDirectory(fd.cFileName);
			FindFile(szMask);
			SetCurrentDirectory("..");
		} while (FindNextFile(hFile, &fd));
		FindClose(hFile);
	}
}

int main(int argc, char** argv)
{
	if (argc < 3) {
		printf("Usage : rff [File Mask] [From Directory]\n");
		exit(0);
	}

	char szCurDir[MAX_PATH];
	GetCurrentDirectory(sizeof(szCurDir), szCurDir);
	SetCurrentDirectory(argv[2]);
	FindFile(argv[1]);
	SetCurrentDirectory(szCurDir);

	return 1;
}