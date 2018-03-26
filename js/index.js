// Server for cutii-desktop browser app
const express = require('express');
const path = require('path');
const fs = require('fs');
const compression = require('compression');
const helmet = require('helmet');
const http = require('http');
var https = require('https');

const app = express();
const PORT = process.env.PORT || 5000;
// variable ci dessous à adapter à votre projet
const DIST = path.join(__dirname, '..', 'public');

const key = fs.readFileSync(__dirname + '/encrypt/server.key');
const cert = fs.readFileSync(__dirname + '/encrypt/server.crt');

const options = {
    key: key,
    cert: cert
  };

app.enable('trust proxy');

app.use(compression());
app.disable('x-powered-by');
app.use(
  helmet.hsts({
    // Must be at least 18 weeks to be approved by Google
    maxAge            : 10886400,
    // Must be enabled to be approved by Google
    includeSubDomains : true,
    preload           : true,
  })
);

app.get('*', (req, res, next) => {
  return res.redirect(308, 'https://' + req.headers.host + req.originalUrl);
});
app.use(express.static(DIST));

app.get('*', (req, res) =>
  fs.createReadStream(path.join(DIST, 'index.html')).pipe(res)
);

https.createServer(options, app).listen(PORT, () =>
  process.stdout.write(`cutii-desktop server started on port ${PORT}\n`)
);