#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <thread>
#include "timer.hpp"
#include "stats.hpp"
#include "proc.hpp"
#include "csvfile.h"

using namespace std;

#define MESSAGE_SIZE 64
string TRANSMIT_STR(MESSAGE_SIZE, 'a'); 
#define MAXSIZE MESSAGE_SIZE + 1 // we transmit 256 bytes + 1 byte for the null terminator

#define REQUESTS 1000
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

bool create_client(const char* server_addr, uint16_t server_port) {
    sockaddr_in addr;
    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, server_addr, &(addr.sin_addr.s_addr));
    addr.sin_port = htons(server_port);
    int client = socket(AF_INET, SOCK_STREAM, 0);

    int err = connect(client, (struct sockaddr *) &addr, sizeof(addr)); // https://man7.org/linux/man-pages/man2/connect.2.html
    if (err == -1) {
        cout << "Cannot connect to server. Error no: " << err << endl;
        return false;
    }
    
    int numbytes;
    char buf[MAXSIZE];

    if (send(client, TRANSMIT_STR.c_str(), TRANSMIT_STR.size(), 0) == -1) {
        cout << "Error sending message";
    }
    if ((numbytes = recv(client, buf, MAXSIZE - 1, MSG_WAITALL)) == -1) {
        cout << "Error receiving data";
        exit(1);
    }
    buf[numbytes] = '\0';
    //cout << buf << endl;
    close(client);
    return true;
}

double measure_rtt(string ip, uint16_t port) {
    Timer t;
    t.begin();
    for(int i = 0; i < REQUESTS; i++) {
        create_client(ip.c_str(), port);
    }
    t.end();
    cout << "..." << flush;
    return REQUESTS / (t.time_diff_nano()); // return total time
}


int main(int argc, char *argv[]) {
    int chid = fork();
    if (chid == 0 ) {
        create_server(8080);
        exit(0);
    } 

    while(!create_client("0.0.0.0", 8080)) {
        cout << "Waiting for server to start ..." << endl;
        sleep(1);
    }
    cout << "Server started" << endl;
    Stats<double> r(ITERATIONS);
    r.run_func([]() {return measure_rtt("0.0.0.0", 8080);});
    cout << endl << "Local RTT (64 bytes)" << endl <<"Mean: "<< r.mean() <<"ns" << endl << "Std dev: " << r.std_dev() << endl;
    wait(NULL);

    r.reset_vals();

    #ifdef REMOTE_IP
    #ifdef REMOTE_PORT
        while(!create_client(REMOTE_IP, REMOTE_PORT)) {
            cout << "Waiting for server to start ..." << endl;
            sleep(1);
        }
        cout << "Remote Server started" << endl;
        r.run_func([]() {return measure_rtt(REMOTE_IP, REMOTE_PORT);});
        cout << endl << "Remote RTT (64 bytes)" << endl <<"Mean: "<< r.mean() <<"ns" << endl << "Std dev: " << r.std_dev() << endl;
    #endif
    #endif
} 