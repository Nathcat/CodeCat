import * as fs from 'fs';
import { parse, HTMLElement } from 'node-html-parser';
import { App } from './App';

export class Page {
    root: HTMLElement;

    constructor(app: App, file: string) {
        this.root = app.replaceTemplates(parse(fs.readFileSync(file, "utf8")));
    }

    get(): string {
        return this.root.toString();
    }
}