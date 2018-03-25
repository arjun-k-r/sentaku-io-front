// ajax call
const proxy = 'https://sentaku-api-prod.herokuapp.com/api/v1/'

function makeRequest (method, url, token) {
  return new Promise(function (resolve, reject) {
    var xhr = new XMLHttpRequest();
    xhr.open(method, proxy + url);
    xhr.setRequestHeader("authorization", token);
    xhr.onload = function () {
      if (this.status >= 200 && this.status < 300) {
        resolve(xhr.response);
      } else {
        reject({
          status: this.status,
          statusText: xhr.statusText
        });
      }
    };
    xhr.onerror = function () {
      reject({
        status: this.status,
        statusText: xhr.statusText
      });
    };
    xhr.send();
  });
}

module.exports.getTrainings = (url, token) => {
  debugger;
  return makeRequest("GET", url, token)
    .then(trainings => {
      debugger;
      
      trainings
    
    });
};
