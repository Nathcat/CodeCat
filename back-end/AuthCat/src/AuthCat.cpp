#include <AuthCat.hpp>
using namespace AuthCat;
using json = nlohmann::json;

extern "C"
{
    User login(const char *username, const char *password)
    {
        char body[1024];
        memset(body, 0, 1024);
        std::strcat(body, "{\"username\": \"");
        std::strcat(body, username);
        std::strcat(body, "\", \"password\": \"");
        std::strcat(body, password);
        std::strcat(body, "\"}");

        httplib::Client HOST("http://data.nathcat.net");

        auto res = HOST.Post(
            "/sso/try-login.php", 
            body,
            "application/json");

        if (res->status == 200)
        {
            json data = json::parse(res->body);
            
            if (data["status"] == "success")
            {
                return {data["user"].template get<json>()};
            }
            else
            {
                throw AUTH_FAILED;
            }
        }
        else
        {
            throw res->status;
        }
    }
}