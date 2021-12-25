#include <iostream>
#include <windows.h>
#include <string>

#define PAGE_SIZE 4096  //размер страницы
#define PAGE_COUNT 15 //количество страниц

using namespace std;

int main() {

    int N = PAGE_COUNT - 1;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    HANDLE freeSemaphore = CreateSemaphore(NULL, N, N,"freeSemaphore");
    HANDLE usedSemaphore = CreateSemaphore(NULL, 0, N,"usedSemaphore");
    HANDLE mutex = CreateMutex(NULL, false, "mutex");

    return 0;
}
