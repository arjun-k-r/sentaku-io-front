open BsFirebase.ReasonFirebase.Auth;

let component = ReasonReact.statelessComponent("Disconnect");

let make = (_children) => {
  ...component,
  didMount: _self => {
      Js.Promise.(
        signOut(FirebaseConfig.auth)
        |> then_(() =>
          ReasonReact.Router.push("/trainings")
          |> resolve
          )
          |> ignore
      );
      ReasonReact.NoUpdate;
  },
  render: _self => <div> </div>
};