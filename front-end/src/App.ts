import http from 'http';
import { Page } from './page';
import { Root } from './pages/root';
import { parse, HTMLElement } from 'node-html-parser';
import * as fs from 'fs';

export class App {
    server: http.Server;
    page: Page;
    port: number;
    hostname: string;
    components: { [id: string] : HTMLElement };

    constructor(hostname: string, port: number) {
        this.server = http.createServer((req, res) => {
            res.statusCode = 200;
            res.setHeader("Content-Type", "text/html");

            res.end(this.page.get());
        });

        this.port = port;
        this.hostname = hostname;

        this.components = {};

        let files: string[] = fs.readdirSync("./UI/components");
        for (let i = 0; i < files.length; i++) {
            this.components[files[i].split(".")[0]] = parse(fs.readFileSync(`./UI/components/${files[i]}`).toString());
        }

        this.page = new Root(this);
    }

    run() {
        this.server.listen(this.port, this.hostname, () => {
            console.log(`Server is listening on http://${this.hostname}:${this.port}/`);
        });
    }

    replaceTemplates(tree: HTMLElement): HTMLElement {
        if (this.components === undefined) {
            return tree;
        }

        if (this.components[tree.rawTagName] !== undefined) {
            let elem = this.components[tree.rawTagName];

            elem.parentNode = tree.parentNode;
            return elem;
        }

        for (let i = 0; i < tree.childNodes.length; i++) {
            tree.childNodes[i] = this.replaceTemplates(tree.childNodes[i] as HTMLElement)!!;
        }

        return tree;
    }
}