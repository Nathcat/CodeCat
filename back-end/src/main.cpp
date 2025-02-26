#include <iostream>
#include <thread>
#include <CodeCat.hpp>

int main() {
    std::cout << "----- CodeCat -----" << std::endl 
        << "CodeCat © Nathcat 2025" << std::endl << std::endl
        << "Starting front end..." << std::endl;

    CodeCat::FrontEndThread frontEnd;

    std::thread frontEndThread(frontEnd);

    frontEndThread.join();
    return 0;
}