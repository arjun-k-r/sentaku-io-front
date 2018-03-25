open Aliases;
open FirebaseConfig;
open RoleDecode;
open Model;

type action = 
    | LoadUsers
    | LoadedUsers(array(roleInfo));
type mState = 
  | NothingToDo
  | LoadingUsers;

type state = {
    mState : mState,
    mUsers : list(roleInfo)
};

let component = ReasonReact.reducerComponent("Administration");

let users : ref(list(roleInfo)) = ref([]);

let addRoleToUsers = (roleInfo) => {
    users := (users^)@roleInfo;
};

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
                            |> (user) => parseRole(user)
                            |> (jsonUser) => Js.log(jsonUser)
                            |> Js.Promise.resolve
                    )
                );*/

let make = _children => {...component, 
    initialState: () => {
        mState: NothingToDo,
        mUsers: []
    },
    reducer: (action, {mState, mUsers}) => {
        switch action {
        | LoadUsers =>  
            ReasonReact.UpdateWithSideEffects({mState: LoadingUsers, mUsers : []}, 
                (self => 
                    Js.Promise.(BsFirebase.ReasonFirebase.Database.Reference.once(
                                BsFirebase.ReasonFirebase.Database.ref(db, ~path="users", ()), 
                                ~eventType="value", 
                                ()
                            ) 
                            |> then_(
                                (data) => {
                                    [%bs.debugger];
                                    BsFirebase.ReasonFirebase.Database.DataSnapshot.foreach(BsFirebase.ReasonFirebase.Database.DataSnapshot.val_(data), (
                                        d =>  { BsFirebase.ReasonFirebase.Database.DataSnapshot.val_(d)
                                        |> (value) => parseRole(value)
                                        |> (role) => { email : role.email, role: role.role }
                                        |> (minimalUser) => addRoleToUsers([minimalUser]);
                                        true
                                        }))
                                
                                    /*Js.log(BsFirebase.ReasonFirebase.Database.DataSnapshot.foreach(data, (d => {[%bs.debugger]; true})));
                                    Js.log(BsFirebase.ReasonFirebase.Database.DataSnapshot.key(data));
                                    Js.log(BsFirebase.ReasonFirebase.Database.DataSnapshot.ref(data));
                                    Js.log(BsFirebase.ReasonFirebase.Database.DataSnapshot.child(data, ~path="EDm6vaIgOjXxAPmcctjswctBBcE2")));
                                    Js.log(BsFirebase.ReasonFirebase.Database.DataSnapshot.exists(data));
                                    Js.log(BsFirebase.ReasonFirebase.Database.DataSnapshot.exportVal(data));
                                    Js.log(BsFirebase.ReasonFirebase.Database.DataSnapshot.foreach(data));
                                    Js.log(BsFirebase.ReasonFirebase.Database.DataSnapshot.hasChild(data));
                                    Js.log(BsFirebase.ReasonFirebase.Database.DataSnapshot.hasChildren(data));
                                    Js.log(BsFirebase.ReasonFirebase.Database.DataSnapshot.toJson(data));
                                    BsFirebase.ReasonFirebase.Database.DataSnapshot.val_(data)*/
                                    |> 
                                    (data) => { 
                                        [%bs.debugger];
                                        Js.log(users);
                                        users;
                                    }
                                    
                                    /*
                                    {
  "EDm6vaIgOjXxAPmcctjswctBBcE2": {
    "email": "bfamchon@gmail.com",
    "role": "evaluator"
  },
  "QcW3puXHuaY3bBhJAU5PCm23Krq1": {
    "email": "sentakumobile@sentaku.io",
    "role": "admin"
  },
  "hVLrlQHRAyW9kVyTzEJOaVEqzYw1": {
    "email": "dsi.sentakuio@gmail.com",
    "role": "admin"
  },
  "rrRaybWNQvQKKOs0XnRNdkTuSSv1": {
    "email": "maws@test.fr",
    "role": "admin"
  }
}
                                    */
                                 /*|> Array.map(data => Js.log(data))*/
                                }
                                |> resolve
                                /*
                                (data) => {BsFirebase.ReasonFirebase.Database.DataSnapshot.val_(data)
                                |> (users) => parseRoles(users)
                                |> (users) => {
                                    Js.log(users);
                                    self.send(LoadedUsers(users)) |> resolve
                                }
                            }*/
                            )
                            |> ignore
                    )
                )
            )
        | LoadedUsers(users) => {Js.log(users); ReasonReact.NoUpdate}
                   
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