#include <stdio.h>
#include <Windows.h>
#define PATH L"DLL.dll"
typedef int(_cdecl* Zadanie1)(int n1, int n2);
typedef int(_cdecl* Zadanie2)(int n1, int n2, int n3);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	HINSTANCE hMyDLL;
	if ((hMyDLL = LoadLibrary(PATH)) == NULL) return 1;
	Zadanie1 zad1 = GetProcAddress(hMyDLL, "Zadan1");
	zad1(1,1000);
	Zadanie2 zad2 = GetProcAddress(hMyDLL, "Zadan2");
	zad2(1, 1000, 5);
	FreeLibrary(hMyDLL);
	return 0;
}