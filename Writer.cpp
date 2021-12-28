#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <Windows.h>

using namespace std;

int main() {

    HANDLE freeSemaphore = OpenSemaphore(SYNCHRONIZE | SEMAPHORE_MODIFY_STATE, false, "freeSemaphore");
    HANDLE usedSemaphore = OpenSemaphore(SYNCHRONIZE | SEMAPHORE_MODIFY_STATE, false, "usedSemaphore");
    HANDLE mutex = OpenMutex(SYNCHRONIZE | MUTEX_MODIFY_STATE, false, "mutex");

    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    LONG page = -1;
    DWORD written = 0;
    string outputString;

    CHAR mappingName[MAX_PATH] = "Mapping";
    HANDLE mapHandle = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, mappingName);
    if (mapHandle)
    {
        for (int i = 0; i < 3; ++i)
        {
            WaitForSingleObject(freeSemaphore, INFINITE);
            outputString = "Take | Free semaphore | " + to_string(GetTickCount()) + '\n';
            WriteFile(hStdout, outputString.data(), outputString.length(), &written, NULL);

            WaitForSingleObject(mutex, INFINITE);
            outputString = "Take | Mutex | " + to_string(GetTickCount()) + '\n';
            WriteFile(hStdout, outputString.data(), outputString.length(), &written, NULL);

            Sleep(rand() % 1000 + 500);
            outputString = "Write | Page | " + to_string(page + 1) + " | " + to_string(GetTickCount()) + "\n";
            WriteFile(hStdout, outputString.data(), outputString.length(), &written, NULL);

            if (ReleaseMutex(mutex))
            {
                outputString = "Free | Mutex | " + to_string(GetTickCount()) + '\n';
                WriteFile(hStdout, outputString.data(), outputString.length(), &written, NULL);
            }
            else
            {
                string str = to_string(GetLastError()) + " CODE mutex\n";
                WriteFile(hStdout, str.data(), str.length(), &written, NULL);
            }

            if (ReleaseSemaphore(usedSemaphore, 1, &page))
            {
                outputString = "Free | Used semaphore | " + to_string(GetTickCount()) + '\n';
                WriteFile(hStdout, outputString.data(), outputString.length(), &written, NULL);
//                string str = "PAGE | NUMBER = " + to_string(page + 1) + " | " + to_string(GetTickCount()) + "\n\n";
//                WriteFile(hStdout, str.data(), str.length(), &written, NULL);
            }
            else
            {
                string str = to_string(GetLastError()) + " CODE semaphore\n";
                WriteFile(hStdout, str.data(), str.length(), &written, NULL);
            }

            outputString = "\n";
            WriteFile(hStdout, outputString.data(), outputString.length(), &written, NULL);
        }
    }
    else
    {
        WriteFile(hStdout, "Mapping creation failed\n", strlen("Mapping creation failed\n"), &written, NULL);
    }

    CloseHandle(hStdout);
}
