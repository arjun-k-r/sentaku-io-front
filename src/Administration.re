open Aliases;
open FirebaseConfig;
open UserDecode;

type action = 
    | LoadUsers;
type mState = 
  | NothingToDo
  | LoadingUsers;

type state = {
    mState : mState
};

let component = ReasonReact.reducerComponent("Administration");

/*
Testing the database 

Js.log("wesh la miff");
        (self => 
                    BsFirebase.ReasonFirebase.Database.Reference.once(
                        BsFirebase.ReasonFirebase.Database.ref(db, ~path="users", ()), 
                        ~eventType="value", 
                        ()
                    ) 
                    |> Js.Promise.then_(
                        (watisthis) => BsFirebase.ReasonFirebase.Database.DataSnapshot.val_(watisthis)
                            |> (user) => parseUser(user)
                            |> (jsonUser) => Js.log(jsonUser)
                            |> Js.Promise.resolve
                    )
                );*/

let make = _children => {...component, 
    initialState: () => {
        mState: NothingToDo
    },
    reducer: (action, {mState}) => {
        switch action {
        | LoadUsers => 
            ReasonReact.UpdateWithSideEffects({mState: LoadingUsers}, 
                (self => 
                Js.Promise.(BsFirebase.ReasonFirebase.Database.Reference.once(
                            BsFirebase.ReasonFirebase.Database.ref(db, ~path="users", ()), 
                            ~eventType="value", 
                            ()
                        ) 
                        |> then_(
                            (data) => BsFirebase.ReasonFirebase.Database.DataSnapshot.val_(data)
                            |> (user) => parseUser(user)
                            |> (jsonUser) => Js.log(jsonUser)
                            |> Js.Promise.resolve
                            /*
                            (watisthis) => BsFirebase.ReasonFirebase.Database.DataSnapshot.val_(watisthis)
                            |> (user) => parseMinimalUser(user)
                            |> (_null) => Js.log("Je suis passé par là")
                            |> (jsonUser) => Js.log(jsonUser)
                            |> Js.Promise.resolve*/
                        )
                        |> ignore
                )
                )
            )
        }
    },
    render: self => 
    <div>
    <h3>(str("Liste des utilisateurs"))</h3>
    <div className="form-group">
            <button onClick=(_evt => self.send(LoadUsers)) className="btn btn-primary">(str("Load users"))</button>
        </div>
    </div>
};