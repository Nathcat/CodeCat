#include <FrontEndThread.hpp>
using namespace CodeCat;

void FrontEndThread::log(const char* m) {
    std::cout << "Front end thread > " << m << std::endl;
}

void FrontEndThread::operator()() {

    log("Started.");
    log("npm run start");

    system("cd front-end && npm run start");
}