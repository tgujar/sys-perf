#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <thread>
#include <vector>

using namespace std;

#define MESSAGE_SIZE 64
string TRANSMIT_STR(MESSAGE_SIZE, 'a'); 
#define MAXSIZE MESSAGE_SIZE + 1 // we transmit 256 bytes + 1 byte for the null terminator

#define REQUESTS 100
#define ITERATIONS 10

void create_server(uint16_t port) {
    // https://man7.org/linux/man-pages/man7/tcp.7.html
    sockaddr_in addr;
    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = 0; // bind to all interface addresses
    addr.sin_port = htons(port);   
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    int on = 1;
    setsockopt(tcp_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)); // reuse addr immidiately upon exit

    int err = bind(tcp_socket, (struct sockaddr *) &addr, sizeof(addr)); // https://man7.org/linux/man-pages/man2/bind.2.html
    if (err == -1) {
        cout << "Cannot bind to port " << port << ". Error no: " << err;
        exit(1);
    }
    err = listen(tcp_socket, 100);
    if (err == -1 ) {
        cout << "Cannot listen on port " << port << ". Error no: " << err;
        exit(1);
    }
     vector<thread> threads;
    // server runs one more time than REQUESTS*ITERATIONS to account for the initial connection check
    for(int i = 0; i <= REQUESTS*ITERATIONS; i++) {
        sockaddr_in *client = new sockaddr_in;
        socklen_t size = sizeof(*client);
        int fd = accept(tcp_socket, (struct sockaddr *) client, &size);
        if (fd == -1) {
            cout << "Connection error. Dropped!!";
        }
        thread t1([fd, client]() {
            
            char buf[MAXSIZE];
            int numbytes;
            if ((numbytes = recv(fd, buf, MAXSIZE - 1, MSG_WAITALL)) == -1) {
                cout << "Error receiving data";
                exit(1);
            }
            buf[numbytes] = '\0';
            if (send(fd, buf, strlen(buf), 0) == -1) {
                cout << "Error sending message";
            }
            close(fd);
        });
        threads.push_back(move(t1));
    }   
    for (auto& t : threads) {
        t.join();
    }
    close(tcp_socket);
}


int main(int argc, char *argv[]) {
    create_server(8080);
} 