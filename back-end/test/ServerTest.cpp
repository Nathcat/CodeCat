#include <AuthCat.hpp>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace AuthCat;

int main() {
    int server = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server, (struct sockaddr*) &addr, sizeof(addr));

    listen(server, 5);

    int client = accept(server, nullptr, nullptr);

    char buffer[1024] = { 0 };
    recv(client, buffer, sizeof(buffer), 0);
    std::cout << buffer << std::endl;
    
    close(server);

    return 0;
}