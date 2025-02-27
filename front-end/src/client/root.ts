/**
 * The root page prompts the user to login, if they are already logged in they should be redirected to the
 * main page, otherwise they should login.
 */
import { AuthCatSSOReply } from '../types/AuthCatSSOReply';
import { User } from '../types/User';

/**
 * Attempt to login with AuthCat
 * @param username The username to login with
 * @param password The password to login with
 * @param successCallback Callback to be executed on success
 * @param failCallback Callback to be executed on failiure
 */
function login(
    username: string,
    password: string, 
    successCallback: (user: User) => void, 
    failCallback: (msg: string) => void
) {
    fetch("https://data.nathcat.net/sso/try-login.php", {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify({"username": username, "password": password})
    }).then((r) => r.json()).then((r: AuthCatSSOReply) => {
        if (r.status === "success") {
            successCallback(r.user!!);
        }
        else {
            failCallback(r.message!!);
        }
    })
}

/**
 * Find existing login info and attempt to use that
 */
if (localStorage.getItem("user") !== null) {
    var user: User = JSON.parse(localStorage.getItem("user")!!) as User;

    login(user?.username!!, user?.password!!, 
        (u: User) => {
            localStorage.setItem("user", JSON.stringify(user));
        },

        (msg: string) => {
            alert("Failed to login with the stored information! " + msg);
            localStorage.removeItem("user");
        }
    );
}