/**
 * This component is the main page which displays a list of trainings
 *
 * US_06
 */
open Model;
open TrainingDecode;

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
                Fetch.fetch(apiUrl ++ "trainings")
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
    }
};