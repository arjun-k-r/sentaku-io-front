// Server for cutii-desktop browser app
const express = require('express');
const path = require('path');
const fs = require('fs');
const compression = require('compression');
const helmet = require('helmet');

const app = express();
const PORT = process.env.PORT || 3000;
// variable ci dessous à adapter à votre projet
const DIST = path.join(__dirname, '..', 'public');

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

app.listen(PORT, () =>
  process.stdout.write(`cutii-desktop server started on port ${PORT}\n`)
);