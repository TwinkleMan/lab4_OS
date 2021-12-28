#include <windows.h>
#include <iostream>

using namespace std;

void WINAPI Callback(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped) {
    cout << "Информация получена" << endl;
}

int main()
{
    system("chcp 1251");
    system("cls");

    CHAR buffer[512];
    BOOL isConnected = FALSE;
    LPCTSTR pipename = TEXT("\\\\.\\pipe\\oslab4_2");

    HANDLE Event = CreateEvent(NULL, FALSE, FALSE, NULL);
    HANDLE Pipe = CreateFile(pipename, GENERIC_READ | GENERIC_WRITE, 0,
                             NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);

    int flag;
    OVERLAPPED overlapped = OVERLAPPED();

    if (Event != INVALID_HANDLE_VALUE && Pipe != INVALID_HANDLE_VALUE)
    {
        do
        {
            system("cls");
            cout << "1) Принять сообщение" << endl;
            cout << "2) Отсоединиться от именованного канала" << endl;
            cout << "0) Выйти" << endl;

            cin >> flag;

            switch (flag) {

                case 1:

                    overlapped.hEvent = Event;
                    isConnected = ReadFileEx(Pipe, (LPVOID)buffer, 512, &overlapped, Callback);

                    if (isConnected)
                    {
                        cout << buffer << endl;
                        system("pause");
                    }
                    else
                    {
                        cout << "Чтение не удалось!" << endl;
                        system("pause");
                    }
                    break;

                case 2:

                    isConnected = CloseHandle(Pipe);	//Закрытие именованного канала

                    if (isConnected)
                        cout << "Вы были отсоединены от именованного канала!" << endl;
                    else
                        cout << "Не удалось отсоединиться!" << endl;

                    isConnected = FALSE;

                    system("pause");

                    break;

                case 0:

                    break;

                default:

                    break;
            }

        } while (flag);
    }
    else
        cout << "Не удалось создать именованный канал, перезапустите программу!" << endl;

    return 0;
}