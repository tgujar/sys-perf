#define _DEFAULT_SOURCEs
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "timer.hpp"
#include "stats.hpp"
#include "proc.hpp"
#include <iostream>
#include <arpa/inet.h>
using namespace std;

const int N_RUNS = 100;

// Server hostent struct
struct hostent *server;
int port;

// Returns time to close TCP connection in micro seconds
double get_teardown_overhead_time()
{
    int sock_fd, n;
    // Create TCP socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        cerr << "Error opening socket" << endl;
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in serv_addr; // server address
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    Timer t;
    if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error connecting\n");
    }
    // cout<<"Connected to server "<< inet_ntoa(serv_addr.sin_addr)<< endl;
    t.begin(); // start timer
    close(sock_fd);
    t.end(); // end timer
    return t.time_diff_micro();
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage %s hostname, port\n", argv[0]);
        exit(0);
    }
    server = gethostbyname(argv[1]); // return entry for host with NAME
    port = atoi(argv[2]);
    cout << "Server " << server << " Port " << port << endl;
    Stats<double> s(N_RUNS);
    s.run_func(get_teardown_overhead_time);
    cout << "Mean : " << s.mean() << " micro seconds" << endl;
    cout << "Variance : " << s.variance() << " micro seconds" << endl;
    cout << "Median : " << s.median() << " micro seconds" << endl;
    cout << "Std dev : " << s.std_dev() << " micro seconds" << endl;
}