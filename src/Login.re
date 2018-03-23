open Model;
open Aliases;
open FirebaseConfig;

type mState =
    | Loading
    | Error
    | Loaded
    | NothingToDo;

type state = {
    mState : mState,
    mCredentials: credential
};

type action = 
  | PostLogin
  | PostedLogin
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
  initialState: () => {mState: NothingToDo, mCredentials: {email:"", password:""}},
  reducer: (action, {mState, mCredentials}) =>
    switch action {
        | PostLogin => 
            BsFirebase.ReasonFirebase.Auth.signInAndRetrieveDataWithEmailAndPassword(auth,~email=mCredentials.email, ~password=mCredentials.password)
            |> Js.Promise.then_(
            (user) => Js.log(user)
            |> Js.Promise.resolve
            );
            ReasonReact.NoUpdate;
        | PostedLogin => ReasonReact.NoUpdate;
        | FailedLogin => ReasonReact.NoUpdate;
        | EditedEmail(email) => ReasonReact.Update({mState, mCredentials: {...mCredentials, email}});
        | EditedPassword(password) => ReasonReact.Update({mState, mCredentials: {...mCredentials, password}});
    },
  render: self =>
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
};

/*

<!--onSubmit={this.handleSubmit}-->

*/