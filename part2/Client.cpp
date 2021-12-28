#include <windows.h>
#include <iostream>

using namespace std;

void WINAPI Callback(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped) {
    cout << "���������� ��������" << endl;
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
            cout << "1) ������� ���������" << endl;
            cout << "2) ������������� �� ������������ ������" << endl;
            cout << "0) �����" << endl;

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
                        cout << "������ �� �������!" << endl;
                        system("pause");
                    }
                    break;

                case 2:

                    isConnected = CloseHandle(Pipe);	//�������� ������������ ������

                    if (isConnected)
                        cout << "�� ���� ����������� �� ������������ ������!" << endl;
                    else
                        cout << "�� ������� �������������!" << endl;

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
        cout << "�� ������� ������� ����������� �����, ������������� ���������!" << endl;

    return 0;
}