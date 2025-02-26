#ifndef AUTHCAT_H
#define AUTHCAT_H
#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <httplib.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

extern "C"
{
    /// @brief An API providing access to AuthCat services.
    namespace AuthCat
    {
        class User
        {
        public:
            int id;
            std::string username;
            std::string fullName;
            std::string email;
            std::string password;
            std::string pfpPath;
            bool passwordUpdated;
            bool verified;

            /// @brief Construct a user from provided information
            /// @param id The user's id
            /// @param username Their username
            /// @param password Their password
            /// @param fullName Their fullName
            /// @param email Their email
            /// @param pfpPath Their profile picture path
            /// @param passwordUpdated Whether or not their password has been updated
            /// @param verified Whether or not they are verified
            User(int id, std::string username, std::string password, std::string fullName, std::string email, std::string pfpPath, bool passwordUpdated, bool verified);

            /// @brief Construct a user from a JSON object
            /// @param data The JSON object containing the user data
            User(json data);

            /// @brief Create a string representation of the user
            /// @return The string representation of this user
            std::string toString();
        };

        const int AUTH_FAILED = 1000;

        /// @brief Attempt to login with the given information
        /// @param username The provided username
        /// @param password The provided password
        /// @return A user if successful
        /// @throws HTTP error codes other than 200, or AUTH_FAILED if authentication failed
        User login(const char *username, const char *password);
    };
}
#endif