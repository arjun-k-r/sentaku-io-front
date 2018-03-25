/**
 * This component reprensents the main layout of the website. It contains the menu and its content changes depending on the url
 */
open Model;
open FirebaseConfig;
open RoleDecode;
open BsFirebase.ReasonFirebase.Auth;

type page =
  | Index
  | Trainings
  | Training(string)
  | Login
  | Register;

/* | NewTraining; */
type state = {
  nowShowing: page,
  connection: connectionState,
  userInfos: option(user)
};

type action =
  | Login(User.t, string, role)
  | ShowIndex
  | ShowTraining(string)
  | ShowTrainings;

/* | ShowNewTraining; */
let component = ReasonReact.reducerComponent("PageLayout");

let make = _children => {
  ...component,
  initialState: () => {nowShowing: Index, connection: NotLogged, userInfos: None},
  reducer: (action, state) => {
    switch action {
    /* router actions */
    | ShowIndex => ReasonReact.Update({...state, nowShowing: Index})
    | ShowTrainings => ReasonReact.Update({...state, nowShowing: Trainings})
    | ShowTraining(id) => ReasonReact.Update({...state, nowShowing: Training(id)})
    | Login(user, token, role) => {
      [%bs.debugger];
      ReasonReact.Update({...state, connection: Logged, 
          userInfos: Some({
            id: User.uid(user),
            email: switch(Js.Nullable.toOption(User.email(user))) {
            | Some(email) => email
            | None => ""
            },
            token: token,
            role: role
          })
        });
      }
    }
  },
    didMount: ( self ) => {
      onAuthStateChanged(FirebaseConfig.auth, 
        ~nextOrObserver = (user) => 
        {
          let opt = Js.Null.toOption(user);
          Js.log(opt);
          switch opt {
            | Some(userValue) => {
                Js.Promise.(User.getIdToken(userValue)
                |> then_(
                    token => {
                      let optToken = Js.Nullable.toOption(token);
                      switch optToken {
                      | Some(valueToken) => {
                          BsFirebase.ReasonFirebase.Database.Reference.once(
                            BsFirebase.ReasonFirebase.Database.ref(FirebaseConfig.db, ~path="users/" ++ User.uid(userValue), ()),
                            ~eventType="value",
                            ()
                          )
                          |> Js.Promise.then_(
                            (roleInfos) => {
                              BsFirebase.ReasonFirebase.Database.DataSnapshot.val_(roleInfos)
                              |> (role) => parseRole(role) |> getRole
                              |> (role) => {
                                Js.log(role);
                                self.send(Login(userValue, valueToken, role));
                                ReasonReact.Router.push("/trainings") |> resolve
                              }
                            }
                          );
                        }
                        | None => Js.Promise.resolve()
                      }
                    }
                  ) |> ignore
                )
            }
            | None => Js.log();
          };
          
        },
        ~error = (err) => Js.log(err),
        ~completed = (u) => {
          Js.log("completed");
          Js.log(u);
        }
      );
      ReasonReact.NoUpdate;
    },
  render: ({ state }) =>
    <div>
      <Header userInfos=state.userInfos connection=state.connection/>
      <div className="row content">
        <div className="">
          <ul id="slide-out" className="col m2 side-nav fixed">
            <div className="brand-sidebar">
              <h1 className="logo-wrapper">
                <a className="brand-logo">
                  <img src="images/logo.png" className="responsive-img" />
                  <span className="logo-text" />
                </a>
              </h1>
            </div>
            <li> <div className="divider" /> </li>
            <li className="no-padding">
              <a href="/trainings" className="waves-effect waves-teal">
                (str("Formations"))
              </a>
            </li>
            <li>
              <a className="waves-effect waves-teal" href="#newtrainings">
                (str("Creer une formation"))
              </a>
            </li>
            <li>
              <a className="waves-effect waves-teal" href="#roles">
                (str("Liste des contacts"))
              </a>
            </li>
          </ul>
          (
            ReasonReact.cloneElement(
              <a href="#" className="button-collapse">
                <i className="material-icons"> (str("menu")) </i>
              </a>,
              ~props={"data-activates": "slide-out"},
              [||]
            )
          )
        </div>
        /***
         * Here add the component to show depending on the state of the current layout
         */
        <div className="col m8 offset-m2">
          <Router>
            ...(
                 (url: ReasonReact.Router.url) =>
                   <div>
                     (
                       switch url.path {
                       | ["training", id] => <Training id=id userInfos=state.userInfos connection=state.connection />
                       | ["login"] => <Login />
                       | ["disconnect"] => <Disconnect />
                       | ["register"] => <Register />
                       | _ => switch state.connection {
                          | Logged => <Trainings userInfos=state.userInfos connection=state.connection />
                          | NotLogged => <div> (str("Connexion en cours")) </div>
                       };
                       
                       }
                     )
                   </div>
               )
          </Router>
        </div>
        <div className="col m2">
          <div className="col m12 pub">
            <img src="images/pub1.jpg" className="responsive-img" />
          </div>
          <div className="col m12 pub">
            <img src="images/pub2.jpg" className="responsive-img" />
          </div>
        </div>
      </div>
    </div>
};