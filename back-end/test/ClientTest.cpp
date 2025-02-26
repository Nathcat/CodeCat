#include <AuthCat.hpp>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
using namespace AuthCat;

int main() {
    int client = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = INADDR_ANY;

    connect(client, (struct sockaddr*)&addr, sizeof(addr));
    
    const char* msg = "Hello, server!";
    send(client, msg, strlen(msg), 0);

    close(client);

    return 0;
}