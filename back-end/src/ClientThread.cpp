#include <ClientThread.hpp>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <string>
using namespace CodeCat;

void ClientThread::log(const char* msg) {
    std::cout << "ClientThread: " << msg << std::endl;
}

void ClientThread::log(std::string msg) {
    std::cout << "ClientThread: " << msg << std::endl;
}

ClientThread::ClientThread(int socket) {
    this->socket = socket;
}

ClientThread::~ClientThread() {
    close(this->socket);
}

void ClientThread::operator()() {
    log("Client opened!");
    char buffer[1024] = { 0 };
    memset(buffer, 0, sizeof(buffer));
    int n;

    log("Ready to receive!");
    while ((n = recv(this->socket, buffer, sizeof(buffer), 0)) != -1) {
        std::string o = "Message from client: ";
        o.append(buffer);
        log(o);
        send(this->socket, buffer, sizeof(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
    }

    log("Failed to receive!");
}
