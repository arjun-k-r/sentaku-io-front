/**
 * This component reprensents the main layout of the website. It contains the menu and its content changes depending on the url
 */
open Model;

type page =
  | Index
  | Trainings
  | Training;
  /* | NewTraining; */

type state = {nowShowing: page};

type action =
  | ShowIndex
  | ShowTraining
  | ShowTrainings;
  /* | ShowNewTraining; */

let component = ReasonReact.reducerComponent("PageLayout");

let make = _children => {
  ...component,
  initialState: () => {nowShowing: Index},
  reducer: (action, _state) =>
    switch action {
    /* router actions */
    | ShowIndex => ReasonReact.Update({nowShowing: Index})
    | ShowTrainings => ReasonReact.Update({nowShowing: Trainings})
    | ShowTraining => ReasonReact.Update({nowShowing: Training})
    },
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url =>
          switch url.hash {
          | "trainings" => self.send(ShowTrainings)
          | "training" => self.send(ShowTraining)
          | _ => self.send(ShowIndex)
          }
        ),
      ReasonReact.Router.unwatchUrl
    )
  ],
  render: self => {
    <div>
        <header>
            <nav>
                <div className="nav-wrapper">
                    <a href="#" className="brand-logo">(str("Sentaku.io"))</a>
                    (
                        ReasonReact.cloneElement(
                            <a href="#"  className="button-collapse"><i className="material-icons">(str("menu"))</i></a>,
                            ~props={"data-activates": "mobile-demo"},
                            [||]
                        )
                    )
                    
                    <ul className="right hide-on-med-and-down">
                        <li><a href="badges.html">(str("FAQ"))</a></li>
                        <li><a href="collapsible.html">(str("A propos"))</a></li>
                        <li><a href="mobile.html">(str("Contact"))</a></li>
                    </ul>
                    <ul className="side-nav" id="mobile-demo">
                        <li><a href="badges.html">(str("FAQ"))</a></li>
                        <li><a href="collapsible.html">(str("A propos"))</a></li>
                        <li><a href="mobile.html">(str("Contact"))</a></li>
                    </ul>
                </div>
            </nav>
        </header>
        <div className="row content">
            <div className="">
                <ul id="slide-out" className="col m2 side-nav fixed">
                    <div className="brand-sidebar">
                        <h1 className="logo-wrapper">
                        <a className="brand-logo">
                            <img src="../public/images/logo.png" className="responsive-img" />
                            <span className="logo-text"></span>
                        </a>
                        </h1>
                    </div>
                    <li>
                        <div className="divider"></div>
                    </li>
                    <li className="no-padding">
                        <a href="#trainings" className="waves-effect waves-teal">(str("Formations"))</a>
                    </li>
                    <li>
                        <a className="waves-effect waves-teal" href="#newtrainings">(str("Créer une formation"))</a>
                    </li>

                    <li>
                        <a className="waves-effect waves-teal" href="#roles">(str("Liste des contacts"))</a>
                    </li>
                </ul>
                (
                    ReasonReact.cloneElement(
                        <a href="#" className="button-collapse"><i className="material-icons">(str("menu"))</i></a>,
                        ~props={"data-activates": "slide-out"},
                        [||]
                    )
                )
            </div>

            /**
             * Here add the component to show depending on the state of the current layout
             */
            (
                switch self.state.nowShowing {
                    | Index => <a href="#trainings"> (str("Voir les formation")) </a>
                    | Training => <Training />
                    | Trainings => <Trainings />
                }
            )
        </div>

        <div className="col m2">
            <div className="col m12 pub">
                <img src="../public/images/pub1.jpg" className="responsive-img" />
            </div>
            <div className="col m12 pub">
                <img src="../public/images/pub2.jpg" className="responsive-img" />
            </div>
        </div>
    </div>
  }
};