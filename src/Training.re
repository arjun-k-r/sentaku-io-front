/**
 * This component is the page which show a training details
 *
 * US_07
 */
open Model;
open TrainingDecode;

/**
* This module shows the training infos
*/
module TrainingHeader = {
  let component = ReasonReact.statelessComponent("TrainingHeader");
  let make = (children) => {
      ...component,
      render: self =>
          <div className="col m12 card">
              <div className="col m3">
              <img src="images/miage.png" className="responsive-img" />
              </div>
              <div className="col m9">
              <div className="col m12 center">
                  <h1 className="formation-title"> (str("Miage lille")) </h1>
              </div>
              <div className="col m12 center">
                  <div className="col m4"> (str("Note la plus basse : 12")) </div>
                  <div className="col m4"> (str("Moyenne des notes : 17")) </div>
                  <div className="col m4"> (str("Note la plus haute : 20")) </div>
              </div>
              <div className="col m12 list-tags">
                  <ul>
                  <li> <span className="tag orange"> (str("Lille")) </span> </li>
                  <li>
                      <span className="tag green"> (str("Informatique")) </span>
                  </li>
                  <li> <span className="tag blue"> (str("Master")) </span> </li>
                  <li> <span className="tag red"> (str("Miage")) </span> </li>
                  </ul>
              </div>
              </div>
          </div>
  };
};

/**
* This module is the tab panel at the bottom of a training where the ratings are displayed
*/
module TrainingFooter = {
  let component = ReasonReact.statelessComponent("TrainingFooter");
  let make = (children) => {
    ...component,
    render: self =>
        <div className="col m12 card">
            <ul id="tabs-swipe-demo" className="tabs">
            <li className="tab col s4">
                <a className="active" href="#test-swipe-1">
                (str("Description"))
                </a>
            </li>
            <li className="tab col s4">
                <a href="#test-swipe-2"> (str("Commentaire")) </a>
            </li>
            <li className="tab col s4">
                <a href="#test-swipe-3"> (str("Laisser un commentaire")) </a>
            </li>
            <li className="indicator" />
            </ul>
            <Description />
            <Ratings />
            /* <Rating /> */
        </div>
  };
};

/* let theTraining :string = "c2337f32-0b69-4434-846c-6107bc4b1904"; */

type state =
  | Loading
  | Error
  | Loaded(training);

type action =
  | TrainingFetch
  | TrainingFetched(training)
  | TrainingFailedToFetch;
let component = ReasonReact.reducerComponent("Training");
let make = _children => {
  ...component,
  initialState: _state => Loading,
  reducer: (action, _state) => 
    switch action {
      | TrainingFetch =>
        ReasonReact.UpdateWithSideEffects(
          Loading,
          (
            self =>
              Js.Promise.(
                Fetch.fetch("https://sentaku-api-prod.herokuapp.com/api/v1/trainings/3d74f052-082b-4f56-867c-511406e90681")
                |> then_(Fetch.Response.json)
                |> then_(json =>
                    json
                    |> TrainingDecode.training
                    |> (training => self.send(TrainingFetched(training)))
                    |> resolve
                  )
                |> catch(_err =>
                    Js.Promise.resolve(self.send(TrainingFailedToFetch))
                  )
                |> ignore
              )
          )
        )
      | TrainingFetched(training) => ReasonReact.Update(Loaded(training))
      | TrainingFailedToFetch => ReasonReact.Update(Error)
    },
  didMount: self => {
    self.send(TrainingFetch);
    ReasonReact.NoUpdate;
  },
  render: (self) =>
    switch self.state {
    | Error => <div> (str("An error occurred!")) </div>
    | Loading => <div> (str("Loading...")) </div>
    | Loaded(training) =>
      <div className="row content">
        <div className="col m8 offset-m2">
        (str(training.title))
          <TrainingHeader />
          <TrainingFooter />
        </div>
      </div>
    }
};