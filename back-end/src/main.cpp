#include <iostream>
#include <thread>
#include <CodeCat.hpp>

int main() {
    std::cout << "----- CodeCat -----" << std::endl 
        << "CodeCat © Nathcat 2025" << std::endl << std::endl
        << "Starting front end..." << std::endl;

    CodeCat::FrontEndThread frontEnd;

    std::thread frontEndThread(frontEnd);

    std::cout << "Starting back end..." << std::endl;
    CodeCat::AcceptorThread acceptor;
    
    std::thread acceptorThread(acceptor);
    
    frontEndThread.join();
    acceptorThread.join();

    return 0;
}