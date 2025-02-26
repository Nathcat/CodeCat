#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <iostream>

int main() {

    httplib::Client cli("https://nathcat.net");

    auto res = cli.Get("/");
    std::cout << "Status: " << res->status << std::endl;
    std::cout << res->body << std::endl;
    
    return 0;
}