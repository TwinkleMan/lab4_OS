#include <iostream>
#include <windows.h>
#include <string>

#define PAGE_SIZE 4096  //размер страницы
#define PAGE_COUNT 15 //количество страниц

using namespace std;

int main() {

    const int writerCount = PAGE_COUNT / 2 + 1;
    const int readerCount = PAGE_COUNT / 2 + 1;
    const int N = PAGE_COUNT - 1;
    int fileSize = N * PAGE_SIZE;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    HANDLE freeSemaphore = CreateSemaphore(NULL, N, N,"freeSemaphore");
    HANDLE usedSemaphore = CreateSemaphore(NULL, 0, N,"usedSemaphore");
    HANDLE mutex = CreateMutex(NULL, false, "mutex");

    HANDLE mapHandle;

    cout << "Данная программа представляет собой решение задачи о читателях и писателях (используя семафоры и мьютексы)\n";

    HANDLE fHandle = CreateFileA("C:\\Users\\Artem\\Desktop\\file.txt", GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    CHAR mappingName[MAX_PATH] = "Mapping";
    mapHandle = CreateFileMapping(fHandle, NULL, PAGE_READWRITE, 0, 0, mappingName);
    LPVOID mapView = MapViewOfFile(mapHandle, FILE_MAP_ALL_ACCESS, 0, 0, fileSize);
    VirtualLock(mapView, fileSize);
    HANDLE processHandles[PAGE_COUNT];

    for (int i = 0; i < writerCount; ++i)
    {

        string writerLogPath = "C:\\Users\\Artem\\Desktop\\Logs\\Writers\\WriterLog" + to_string(i + 1) + ".txt";

        STARTUPINFO sysInfo;
        PROCESS_INFORMATION procInfo;
        SECURITY_ATTRIBUTES secureAttr = { sizeof(secureAttr), NULL, TRUE };

        ZeroMemory(&sysInfo, sizeof(sysInfo));

        HANDLE outHandle = CreateFile(writerLogPath.data(), GENERIC_WRITE, FILE_SHARE_WRITE, &secureAttr,
                                      OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        sysInfo.cb = sizeof(sysInfo);
        sysInfo.hStdOutput = outHandle;
        sysInfo.hStdError = NULL;
        sysInfo.hStdInput = NULL;
        sysInfo.dwFlags |= STARTF_USESTDHANDLES;

        ZeroMemory(&procInfo, sizeof(procInfo));

        int writerProcess = CreateProcess("C:\\Users\\Artem\\CLionProjects\\lab4_OS\\cmake-build-debug\\Writer.exe", NULL, NULL, NULL, TRUE, 0, NULL, NULL, &sysInfo, &procInfo);

        if (writerProcess)
            processHandles[i] = procInfo.hProcess;
    }


    for (int i = 0; i < readerCount; ++i)
    {
        string readerLogPath = "C:\\Users\\Artem\\Desktop\\Logs\\Readers\\ReaderLog" + to_string(i + 1) + ".txt";

        STARTUPINFO sysInfo;
        PROCESS_INFORMATION procInfo;
        SECURITY_ATTRIBUTES secureAttr = { sizeof(secureAttr), NULL, TRUE };

        ZeroMemory(&sysInfo, sizeof(sysInfo));

        sysInfo.hStdOutput = CreateFile(readerLogPath.data(), GENERIC_WRITE, FILE_SHARE_WRITE, &secureAttr,
                                        OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        sysInfo.cb = sizeof(sysInfo);
        sysInfo.hStdError = NULL;
        sysInfo.hStdInput = NULL;
        sysInfo.dwFlags |= STARTF_USESTDHANDLES;
        ZeroMemory(&procInfo, sizeof(procInfo));

        int readerProcess = CreateProcess("C:\\Users\\Artem\\CLionProjects\\lab4_OS\\cmake-build-debug\\Reader.exe", NULL, NULL, NULL, TRUE, 0, NULL, NULL, &sysInfo, &procInfo);

        if (readerProcess != 0)
            processHandles[writerCount + i] = procInfo.hProcess;
    }

    WaitForMultipleObjects(PAGE_COUNT, processHandles, true, INFINITE);

    for (int i = 0; i < PAGE_COUNT; ++i)
        CloseHandle(processHandles[i]);

    CloseHandle(mapHandle);
    UnmapViewOfFile(mapView);
    CloseHandle(fHandle);
    CloseHandle(mutex);
    CloseHandle(freeSemaphore);
    CloseHandle(usedSemaphore);

    cout << endl << "Готово, можно выходить." << endl;
    system("pause");

    return 0;
}
