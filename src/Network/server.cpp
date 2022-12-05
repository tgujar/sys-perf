#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char **argv)
{
    int sock_fd, port;
    port = stoi(argv[1]);
    struct sockaddr_in serv_addr; // server address
    bzero((char *)&serv_addr, sizeof(serv_addr));

    // create TCP socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    int iSetOption = 1;
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&iSetOption, sizeof(iSetOption));
    if (sock_fd < 0)
    {
        cerr << "ERROR opening socket";
        exit(EXIT_FAILURE);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    // bind socket to current IP address on given port
    if (bind(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        cerr << "ERROR on binding" << endl;
        exit(EXIT_FAILURE);
    }

    if (listen(sock_fd, 10) < 0)
    {
        cerr << "Listen failure" << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Listening on port " << port << endl;

    struct sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);
    while (true)
    {
        int newsock_fd = accept(sock_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_size);
        //cout << "Connected to client " << inet_ntoa(client_addr.sin_addr) << endl;
        if (newsock_fd < 0)
        {
            cerr << "Error on accept" << endl;
            exit(EXIT_FAILURE);
        }
        close(newsock_fd); // close client socket
    }
    close(sock_fd); // close server socket
    return 0;
}