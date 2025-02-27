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
    components: { [id: string]: HTMLElement };

    constructor(hostname: string, port: number) {
        this.server = http.createServer((req, res) => {
            console.log(req.method + " " + req.url);

            if (req.url === "/") {
                res.statusCode = 200;
                res.setHeader("Content-Type", "text/html");

                res.end(this.page.get());
            }
            else if (req.url === "/favicon.ico") {
                res.statusCode = 404;
                res.end("Could not find icon file!");
                return;
            }
            else {
                // Check the URL path and handle accordingly
                let path = req.url?.split("/");
                path?.shift();

                if (path!![0] === "js") {
                    console.log("JS file requested");

                    // Requesting a JS file
                    path?.shift();
                    let jsPath = path?.join("/");

                    console.log("JS path is " + jsPath);

                    try {
                        let content = fs.readFileSync("./dist/client/" + jsPath);
                        res.statusCode = 200;
                        res.setHeader("Content-Type", "text/javascript");
                        res.end(content.toString());
                        return;
                    }
                    catch (err: any) {
                        if (err.code === "ENOENT") {
                            res.statusCode = 404;
                            res.end("Could not find JS file!");
                            return;
                        }
                        else {
                            throw err;
                        }
                    }

                }
            }
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