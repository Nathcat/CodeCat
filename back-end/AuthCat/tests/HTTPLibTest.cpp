#include <iostream>
#include <AuthCat.hpp>

int main()
{

    char username[256];
    char password[256];

    std::cout << "Username > ";
    std::cin >> username;
    std::cout << "Password > ";
    std::cin >> password;

    try {
        AuthCat::User user = AuthCat::login(username, password);
        std::cout << "Successfully authenticated!" << std::endl << user.toString() << std::endl;
    }
    catch (int err) {
        if (err == AuthCat::AUTH_FAILED) {
            std::cout << "Failed to authenticate!" << std::endl;
            return 0;
        }
        else {
            std::cout << "Unknown HTTP error! " << err << std::endl;
        }
    }

    /**char body[1024];
    std::strcat(body, "{\"username\": \"");
    std::strcat(body, username);
    std::strcat(body, "\", \"password\": \"");
    std::strcat(body, password);
    std::strcat(body, "\"}");

    httplib::Client HOST("https://data.nathcat.net");
    
    auto res = HOST.Post(
        "/sso/try-login.php", strlen(body),
        [body](size_t offset, size_t length, httplib::DataSink &sink)
        {
            sink.write(body + offset, length);
            return true;
        },
        "application/json");

    if (res->status == 200)
    {
        json data = json::parse(res->body);

        std::cout << "Status: " << data["status"] << std::endl;

        json user = data["user"].template get<json>();

        std::cout << "Full name: " << user["fullName"] << std::endl;
    }
    else
    {
        std::cout << "Status: " << res->status << std::endl;
    }**/

    return 0;
}