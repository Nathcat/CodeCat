#ifndef AUTHCAT_H
#define AUTHCAT_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

/// @brief An API providing access to AuthCat services.
namespace AuthCat {
    class User {
        public:
        const int id;
        const char* username;
        const char* fullName;
        const char* email;
        const char* password;

        User(int id, const char* username, const char* password, const char* fullName, const char* email);
    };

    sockaddr_in getSocketAddr() {
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(80);
        addr.sin_addr.s_addr = INADDR_ANY;
    }
};

#endif