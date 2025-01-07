/**
 * A user as represented in the AuthCat SSO database.
 * This class also provides some basic static functions to provide integration with AuthCat.
 * @author Nathan Baines
 */
export class User {
    id: number;
    username: string;
    fullName: string;
    email: string;
    password: string | undefined;
    pfpPath: string;
    verified: boolean;
    passwordUpdated: boolean;

    constructor(
        id: number,
        username: string,
        password: string | undefined,
        email: string,
        fullName: string,
        pfpPath: string,
        verified: boolean,
        passwordUpdated: boolean,
    ) {
        this.id = id;
        this.username = username;
        this.password = password;
        this.email = email;
        this.fullName = fullName;
        this.pfpPath = pfpPath;
        this.verified = verified;
        this.passwordUpdated = passwordUpdated;
    }

    /**
     * Attempt to autenticate a set of user credentials with AuthCat
     * @param username Username to send
     * @param password Password to send
     * @param onFinish Called when the request has returned a result
     */
    static async AuthenticateUser(
        username: string,
        password: string,
        onFinish: (result: User | string) => void
    ) {
        let r = await fetch("https://data.nathcat.net/sso/try-login.php", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify({
                "username": username,
                "password": password
            })
        })
        .then((f) => f.json());

        if (r.status === "fail") {
            onFinish(r.message);
        }
        else {
            onFinish(new User(
                r.user.id,
                r.user.username,
                r.user.password,
                r.user.email,
                r.user.fullName,
                r.user.pfpPath,
                r.user.verified,
                r.user.passwordUpdated
            ));
        }
    }
}