open Model;
open BsFirebase.ReasonFirebase.Auth;
open FirebaseConfig;

type mState =
    | Loading
    | Error
    | NothingToDo;

type state = {
    mState : mState,
    mCredentials: credential
};

type action = 
  | PostLogin
  | FailedLogin
  | EditedEmail(string)
  | EditedPassword(string);

let valueFromEvent = (evt) : string => (
    evt
    |> ReactEventRe.Form.target
    |> ReactDOMRe.domElementToObj
  )##value;

  let component = ReasonReact.reducerComponent("Login");

let make = (_children) => {
  ...component,
  initialState: () => { mState: NothingToDo, mCredentials: {email:"", password:""} },
  reducer: (action, {mState, mCredentials}) =>
    switch action {
        | PostLogin =>
        ReasonReact.UpdateWithSideEffects({mState: Loading, mCredentials},
            (
                self =>
                    Js.Promise.(
                        signInAndRetrieveDataWithEmailAndPassword(auth,~email=mCredentials.email, ~password=mCredentials.password)
                        |> then_(
                            (_user) => 
                            {
                                Js.log("connected");
                            }
                            |> resolve
                            )
                        |> catch(_err =>
                            Js.Promise.resolve(self.send(FailedLogin))
                        
                        )
                        |> ignore
                    )
            )
        )
        | FailedLogin => ReasonReact.Update({mState: Error, mCredentials});
        | EditedEmail(email) => ReasonReact.Update({mState, mCredentials: {...mCredentials, email}});
        | EditedPassword(password) => ReasonReact.Update({mState, mCredentials: {...mCredentials, password}});
    },
  render: self =>
  switch self.state {
  | {mState: NothingToDo} => 
    <div className="col-md-6 col-md-offset-3 little-content">
    <h2>(str("Login"))</h2>
    <form name="form" > 
        <div className="user-name">
            <label htmlFor="username">(str("Username"))</label>
            <input _type="text" onChange=((evt) => self.send(EditedEmail(valueFromEvent(evt)))) className="form-control" name="username"/>
        </div>
        <div className="passwd">
            <label htmlFor="password">(str("Password"))</label>
            <input _type="password" onChange=((evt) => self.send(EditedPassword(valueFromEvent(evt)))) className="form-control" name="password" />
        </div>
        <div className="form-group">
            <button onClick=(_evt => self.send(PostLogin)) className="btn btn-primary">(str("Login"))</button>
            <a className="margin-left" href="/register"> (str("S'enregistrer")) </a>
        </div>
    </form>
    </div>
    | {mState: Loading} => <div> (str("Connexion en cours")) </div>
    | {mState: Error} => <div> (str("Vos identifiant ne sont pas bon")) </div>
  }
};

/*

<!--onSubmit={this.handleSubmit}-->

*/