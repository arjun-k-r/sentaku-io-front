let options =
   {
    "projectId": "sentaku-io",
	"apiKey": "AIzaSyBB5CYadj9Laeb9DNXtg6DPRUVx4-kVzD4",
	"authDomain": "sentaku-io.firebaseapp.com",
	"databaseURL": "https://sentaku-io.firebaseio.com",
	"storageBucket": "sentaku-io.appspot.com",
	"messagingSenderId": "202892223524"
   };

let app = BsFirebase.ReasonFirebase.initializeApp(~options=options);

let auth = BsFirebase.ReasonFirebase.App.auth(app);
let db = BsFirebase.ReasonFirebase.App.database(app);


