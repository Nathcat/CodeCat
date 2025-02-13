import { Page } from '../page';
import * as fs from 'fs';
import { App } from '../App';

export class Root extends Page {
    constructor(app: App) {
        super(app, "UI/index.html");
    }
}