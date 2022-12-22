#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

extern BOOL WINAPI DllMain(
    HINSTANCE const instance,  
    DWORD     const reason,    
    LPVOID    const reserved)  
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern __declspec(dllimport) int Zadan1(int n1, int n2);
extern __declspec(dllimport) int Zadan2(int n1, int n2, int n3);

int Zadan1(int n1, int n2)
{
    int rez = 0;
    int ch;
    for (int i = n1;i <= n2;i++)
    {       
        if (i == 1)
            ch = 0;
        for (int d = 2; d * d <= i; d++)
            if (i % d == 0)
            {
                ch = 0;
                break;
            }
        if (ch < 0) ch = 1;
        if (ch)
            rez++;
        ch = -1;
    }
    char* d = (char*)calloc(100, sizeof(char));
    sprintf(d, " %d", rez);
    MessageBoxA(NULL, d, "×èñeë", NULL);
    return rez;
}
struct Paralel
{
    int* a;
    int* b;
};
void prost_num(struct Paralel paral)
{
    int n1 = paral.a;
    int n2 = paral.b;
    int rez2 = 0;
    int ch;
    for (int i = n1; i <= n2; i++)
    {
        if (i == 1)
            ch = 0;
        for (int d = 2; d * d <= i; d++)
            if (i % d == 0)
            {
                ch = 0;
                break;
            }
        if (ch < 0) ch = 1;
        if (ch)
            rez2++;
        ch = -1;
    }
    char* d = (char*)calloc(100, sizeof(char));
    sprintf(d, " %d", rez2);
    MessageBoxA(NULL, d, "×èñeë", NULL);
}
int Zadan2(int n1, int n2, int n3)
{
    //int rez2 = 0;
    HANDLE hTread[5];
    CRITICAL_SECTION s = { 0 };
    int arr1[] = { n1,n1,n1,n1,n1 };
    int arr2[] = { n2,n2,n2,n2,n2 };
    arr1[0] = n1;
    arr2[0] = n2;
    struct Paralel paral[5];
    for (int i = 0; i < n3; i++)
    {
        paral[i].a = arr1[i];
        paral[i].b = arr2[i];
    }
    InitializeCriticalSection(&s);
    for (size_t i = 0; i < n3; i++)
    {
        EnterCriticalSection(&s);
        hTread[i] = CreateThread(NULL, 0, prost_num, &paral[i], NULL, NULL);
        LeaveCriticalSection(&s);
        WaitForMultipleObjects(n3, hTread, TRUE, INFINITE);
    }
    DeleteCriticalSection(&s);
    /*char* d = (char*)calloc(100, sizeof(char));
    sprintf(d, " %d", rez2);
    MessageBoxA(NULL, d, "×èñeë", NULL);
    return rez2;*/
}