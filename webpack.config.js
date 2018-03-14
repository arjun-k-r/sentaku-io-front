const path = require('path');

module.exports = {
  entry: './lib/js/src/App.bs.js',
  output: {
    path: path.join(__dirname, 'public', 'js'),
    filename: 'bundle.js',
  }
};
