#include <windows.h>
#include <iostream>

using namespace std;

void WINAPI Callback(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped) {
    cout << "Èíôîðìàöèÿ ïîëó÷åíà" << endl;
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
            cout << "1) Ïðèíÿòü ñîîáùåíèå" << endl;
            cout << "2) Îòñîåäèíèòüñÿ îò èìåíîâàííîãî êàíàëà" << endl;
            cout << "0) Âûéòè" << endl;

            cin >> flag;

            switch (flag) {

                case 1:

                    overlapped.hEvent = Event;
                    isConnected = ReadFileEx(Pipe, buffer, 512, &overlapped, Callback);
                    SleepEx(INFINITE, true);

                    if (isConnected)
                    {
                        cout << buffer << endl;
                        system("pause");
                    }
                    else
                    {
                        cout << "×òåíèå íå óäàëîñü!" << endl;
                        system("pause");
                    }
                    break;

                case 2:

                    isConnected = CloseHandle(Pipe);	//Çàêðûòèå èìåíîâàííîãî êàíàëà

                    if (isConnected)
                        cout << "Âû áûëè îòñîåäèíåíû îò èìåíîâàííîãî êàíàëà!" << endl;
                    else
                        cout << "Íå óäàëîñü îòñîåäèíèòüñÿ!" << endl;

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
        cout << "Íå óäàëîñü ñîçäàòü èìåíîâàííûé êàíàë, ïåðåçàïóñòèòå ïðîãðàììó!" << endl;

    return 0;
}
