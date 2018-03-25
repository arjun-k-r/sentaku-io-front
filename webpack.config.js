const path = require('path');

module.exports = {
  entry: './lib/js/src/App.bs.js',
  resolve: {
    alias: {
      bs: path.join(__dirname, 'lib', 'js', 'src'),
      js: path.join(__dirname, 'js'),
    }
  },
  output: {
    publicPath: "/public/",
    path: path.join(__dirname, 'public', 'js'),
    filename: 'bundle.js',
  }
};
