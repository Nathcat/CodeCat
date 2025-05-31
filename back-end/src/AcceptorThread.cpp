#include <AcceptorThread.hpp>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <ClientThread.hpp>
using namespace CodeCat;

void AcceptorThread::log(const char* msg) {
    std::cout << "Acceptor: " << msg << std::endl;
}

void AcceptorThread::log(std::string msg) {
    std::cout << "Acceptor: " << msg << std::endl;
}

void AcceptorThread::operator()() {
    log("Setting up...");

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = INADDR_ANY;

    server = socket(AF_INET, SOCK_STREAM, 0);
    bind(server, (struct sockaddr*)&addr, sizeof(addr));
    listen(server, 5);

    log("Listening for clients...");

    while (allowAccept) {
        int c = accept(server, nullptr, nullptr);
        ClientThread ct(c);
        log("Accepting connection!");
        std::thread ct_thread(ct);
        ct_thread.join();
    }
}

AcceptorThread::~AcceptorThread() {
    allowAccept = false;
    close(server);
}