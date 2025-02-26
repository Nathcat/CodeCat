#ifndef AUTHCAT_H
#define AUTHCAT_H
#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <httplib.h>

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
};

#endif