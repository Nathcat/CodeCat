export type User = {
    id: number, 
    username: string, 
    password: string,
    email: string,
    fullName: string,
    pfpPath: string,
    verified: boolean,
    passwordUpdated: boolean
} | null;