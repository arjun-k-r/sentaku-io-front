/**
 * This component reprensents the main layout of the website. It contains the menu and its content changes depending on the url
 */
open Model;

type page =
  | Index
  | Trainings
  | Training(string);

/* | NewTraining; */
type state = {nowShowing: page};

type action =
  | ShowIndex
  | ShowTraining(string)
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
    | ShowTraining(id) => ReasonReact.Update({nowShowing: Training(id)})
    },
  render: _self =>
    <div>
      <Header />
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
              <a href="trainings" className="waves-effect waves-teal">
                (str("Formations"))
              </a>
            </li>
            <li>
              <a className="waves-effect waves-teal" href="#newtrainings">
                (str("Cr\195\169er une formation"))
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
        <Router>
          ...(
               (url: ReasonReact.Router.url) =>
                 <div>
                   (
                     switch url.path {
                     | ["trainings"] => <Trainings />
                     | ["training", id] => <Training id />
                     | _ =>
                       <a href="/trainings"> (str("Voir les formation")) </a>
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
};