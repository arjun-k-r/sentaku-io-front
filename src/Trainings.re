/**
 * This component is the main page which displays a list of trainings
 *
 * US_06
 */
open FirebaseConfig;
open Model;
open BsFirebase.ReasonFirebase.Auth;
open UserDecode;
open TrainingDecode;

type mState =
  | Loading
  | Error
  | Loaded(array(training));

type state = {
  mState: mState,
};
  
type action =
  | TrainingsFetch
  | TrainingsFetched(array(training))
  | TrainingFailedToFetch;

let component = ReasonReact.reducerComponent("Trainings");
let make = (~userInfos, ~connection, _children) => {
  ...component,
  initialState: _state => {mState: Loading},
  reducer: (action, state) => 
    switch action {
      | TrainingsFetch => {
      switch userInfos {
        | Some(user) => 
          ReasonReact.UpdateWithSideEffects(
            {mState: Loading},
            (
              self =>{
                [%bs.debugger];
                Js.Promise.(
                  Fetch.fetchWithInit(apiUrl ++ "trainings", 
                  Fetch.RequestInit.make(~method_=Get, ~headers= Fetch.HeadersInit.makeWithArray([|("authorization", user.token)|]), ()))
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
                    }
            )
          )
        | None => ReasonReact.Update({mState: Error})
        }
        }
      | TrainingsFetched(training) => {
        ReasonReact.Update({mState: Loaded(training)})
      }
      | TrainingFailedToFetch => ReasonReact.Update({mState: Error})
    },
  didMount: self => {
    /* onAuthStateChanged(auth, ~nextOrObserver = (_user) => {
      [%bs.debugger];
      self.send(TrainingsFetch);
    }, ~error= err => Js.log(err), ~completed= u => Js.log(u)); */
    self.send(TrainingsFetch);
    ReasonReact.NoUpdate;
  },
  render: (self) =>
    switch self.state {
    | {mState: Error} => <div> (str("Nous n'arrivons pas à récupérer la liste des formations :( !")) </div>
    | {mState: Loading} => <div> (str("Chargement de la page ...")) </div>
    | {mState: Loaded(trainings)} =>
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