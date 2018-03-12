/**
 * This component is the main page which displays a list of trainings
 *
 * US_06
 */
open Model;
open Utils;
open TrainingDecode;

/**
* This module shows the training infos
*/
module TrainingItem = {

  let component = ReasonReact.statelessComponent("TrainingItem");
  let make = (~training, children) => {
      ...component,
      render: self =>
      <div className="col m12 card">
        <div className="col m2">
          <img src=(training.logo) className="responsive-img" />
        </div>
        <div className="col m10">
          <div className="col m12">
            <span className="formation-title">(str(training.title))</span>
            <span><i className="material-icons rate-stars">(str("star_half"))</i></span>
            <span><i className="material-icons rate-stars">(str("star"))</i></span>
            <span><i className="material-icons rate-stars">(str("star"))</i></span>
            <span><i className="material-icons rate-stars">(str("star"))</i></span>
            <span><i className="material-icons rate-stars">(str("star"))</i></span>
          </div>
          <div className="col m12">
            <p className="formation-description">
              (str(training.description))
            </p>
          </div>
        </div>
      </div>
  };
};

type state =
  | Loading
  | Error
  | Loaded(array(training));

type action =
  | TrainingsFetch
  | TrainingsFetched(array(training))
  | TrainingFailedToFetch;
let component = ReasonReact.reducerComponent("Trainings");
let make = _children => {
  ...component,
  initialState: _state => Loading,
  reducer: (action, _state) => 
    switch action {
      | TrainingsFetch =>
        ReasonReact.UpdateWithSideEffects(
          Loading,
          (
            self =>
              Js.Promise.(
                Fetch.fetch("https://sentaku-api-prod.herokuapp.com/api/v1/trainings")
                |> then_(Fetch.Response.json)
                |> then_(json =>
                    json
                    |> TrainingDecode.trainings
                    /* |> (training => {
                      Js.log(training);
                      training
                    }) */
                    |> (trainings => self.send(TrainingsFetched(trainings.trainings)))
                    |> resolve
                  )
                |> catch(_err =>
                    Js.Promise.resolve(self.send(TrainingFailedToFetch))
                  )
                |> ignore
              )
          )
        )
      | TrainingsFetched(training) => ReasonReact.Update(Loaded(training))
      | TrainingFailedToFetch => ReasonReact.Update(Error)
    },
  didMount: self => {
    self.send(TrainingsFetch);
    ReasonReact.NoUpdate;
  },
  render: (self) =>
    switch self.state {
    | Error => <div> (str("Nous n'arrivons pas à récupérer la liste des formations :( !")) </div>
    | Loading => <div> (str("Chargement de la page ...")) </div>
    | Loaded(trainings) =>
      <div className="row content">
        <div className="col m8 offset-m2">
        (
          ReasonReact.arrayToElement(Array.map(
              (training : training) =>
                <TrainingItem
                  key=(training.id)
                  training
                />,
              trainings
            ))
        )
        </div>
      </div>
    }
};