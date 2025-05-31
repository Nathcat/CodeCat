#include <AuthCat.hpp>
using json = nlohmann::json;

extern "C"
{
    AuthCat::User::User(int id,
                        std::string username,
                        std::string password,
                        std::string fullName,
                        std::string email,
                        std::string pfpPath,
                        bool passwordUpdated,
                        bool verified)
    {
        this->id = id;
        this->username = username;
        this->password = password;
        this->fullName = fullName;
        this->email = email;
        this->pfpPath = pfpPath;
        this->passwordUpdated = passwordUpdated;
        this->verified = verified;
    }

    AuthCat::User::User(json data)
    {
        this->id = data["id"].template get<int>();
        this->username = data["username"].template get<std::string>();
        this->password = data["password"].template get<std::string>();
        this->fullName = data["fullName"].template get<std::string>();
        this->email = data["email"].template get<std::string>();
        this->pfpPath = data["pfpPath"].template get<std::string>();
        this->passwordUpdated = data["passwordUpdated"].template get<int>() == 1;
        this->verified = data["verified"].template get<int>() == 1;
    }

    std::string AuthCat::User::toString()
    {
        std::string s = "\tid: ";
        s
            .append(std::to_string(id))
            .append("\n\tUsername: ")
            .append(username)
            .append("\n\tPassword hash: ")
            .append(password)
            .append("\n\tFull Name: ")
            .append(fullName)
            .append("\n\tEmail: ")
            .append(email)
            .append("\n\tProfile Picture Path: ")
            .append(pfpPath)
            .append("\n\tPassword Updated: ")
            .append(passwordUpdated ? "Yes" : "No")
            .append("\n\tVerified: ")
            .append(verified ? "Yes" : "No");

        return s;
    }
}