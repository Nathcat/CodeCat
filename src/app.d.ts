// See https://svelte.dev/docs/kit/types#app.d.ts
// for information about these interfaces
import { User } from "$lib/User";

declare global {
	namespace App {
		// interface Error {}
		// interface Locals {}
		interface PageData {
			user: User
		}
		// interface PageState {}
		// interface Platform {}
	}
}

export {};
