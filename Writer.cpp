#include "Writer.h"
#include <windows.h>
#include <ctime>

using namespace std;

void Writer() {

    HANDLE freeSem = OpenSemaphore(SYNCHRONIZE | SEMAPHORE_MODIFY_STATE, false, "freeSemaphore");
    HANDLE usedSem = OpenSemaphore(SYNCHRONIZE | SEMAPHORE_MODIFY_STATE, false, "usedSemaphore");
    HANDLE mutex = OpenMutex(SYNCHRONIZE | MUTEX_MODIFY_STATE, false, "mutex");

    //
    srand(time(nullptr));

    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    int page = -1;
    DWORD
}
