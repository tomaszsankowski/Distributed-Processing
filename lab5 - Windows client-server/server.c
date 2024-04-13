#include <winsock2.h>
#include <stdio.h>

#define DEFAULT_PORT 5000
#define DEFAULT_BUFFER 4096

#pragma comment(lib, "ws2_32.lib")

DWORD WINAPI ClientThread(LPVOID lpParam) {
    SOCKET sock = (SOCKET)lpParam;
    char szBuf[DEFAULT_BUFFER];
    int ret, nLeft, idx;

    while(1) {
        ret = recv(sock, szBuf, DEFAULT_BUFFER, 0);
        if (ret == 0)
            break;
        else if (ret == SOCKET_ERROR) {
            printf("blad funkcji recv(): %d\n", WSAGetLastError());
            break;
        }

        szBuf[ret] = '\0';
        printf("RECV: '%s'\n", szBuf);

        nLeft = ret;
        idx = 0;
        while(nLeft > 0) {
            ret = send(sock, &szBuf[idx], nLeft, 0);
            if (ret == 0)
                break;
            else if (ret == SOCKET_ERROR) {
                printf("blad funkcji send(): %d\n", WSAGetLastError());
                break;
            }
            nLeft -= ret;
            idx += ret;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    WSADATA wsd;
    SOCKET sListen, sClient;
    int iAddrSize;
    HANDLE hThread;
    DWORD dwThreadID;
    struct sockaddr_in local, client;
    struct hostent *host = NULL;

    if (WSAStartup(MAKEWORD(2,2), &wsd) != 0) {
        printf("Blad ladowania Winsock 2.2!\n");
        return 1;
    }

    sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (sListen == SOCKET_ERROR) {
        printf("Blad funkcji socket(): %d\n", WSAGetLastError());
        return 1;
    }

    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_family = AF_INET;
    local.sin_port = htons(DEFAULT_PORT);
    if (bind(sListen, (struct sockaddr *)&local, sizeof(local)) == SOCKET_ERROR) {
        printf("Blad funkcji bind(): %d\n", WSAGetLastError());
        return 1;
    }

    host = gethostbyname("localhost");
    if (host == NULL) {
        printf("Nie udalo się wydobyc nazwy serwera\n");
        return 1;
    }

    listen(sListen, 8);
    printf("Serwer nasluchuje.\n");
    printf("Adres: %s, port: %d\n", host->h_name, DEFAULT_PORT);

    while (1) {
        iAddrSize = sizeof(client);
        sClient = accept(sListen, (struct sockaddr *)&client, &iAddrSize);
        if (sClient == INVALID_SOCKET) {
            printf("Blad funkcji accept(): %d\n", WSAGetLastError());
            return 1;
        }
        printf("Zaakceptowano polaczenie: serwer %s, port %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        hThread = CreateThread(NULL, 0, ClientThread, (LPVOID)sClient, 0, &dwThreadID);
        if (hThread == NULL) {
            printf("Blad funkcji CreateThread(): %d\n", WSAGetLastError());
            return 1;
        }
        CloseHandle(hThread);
    }

    closesocket(sListen);
    WSACleanup();
    return 0;
}