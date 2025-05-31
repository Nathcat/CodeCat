import { User } from './User';

export type AuthCatSSOReply = {
    status: string,
    user: User | undefined,
    message: string | undefined
};