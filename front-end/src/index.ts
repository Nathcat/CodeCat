import http from 'http';
import { App } from './App';

const hostname = "127.0.0.1";
const port = 8080;

const app = new App(hostname, port);
app.run();