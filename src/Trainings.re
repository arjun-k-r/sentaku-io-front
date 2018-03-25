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
open Tokens;

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
let make = (~userInfos: option(user), ~connection, _children) => {
  ...component,
  initialState: _state => {mState: Loading},
  reducer: (action, _state) => 
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
                   /* Fetch.RequestInit.make(~credentials=SameOrigin, ~headers=Fetch.HeadersInit.make({"Authorization": "Bearer " ++ user.token}), ())) */
                   Fetch.RequestInit.make(~method_=Get, ~headers=Fetch.HeadersInit.makeWithArray([|("authorization", "eyJhbGciOiJSUzI1NiIsImtpZCI6ImY1YjE4Mjc2YTQ4NjYxZDBhODBiYzhjM2U5NDM0OTc0ZDFmMWRiNTEifQ.eyJpc3MiOiJodHRwczovL3NlY3VyZXRva2VuLmdvb2dsZS5jb20vc2VudGFrdS1pbyIsImF1ZCI6InNlbnRha3UtaW8iLCJhdXRoX3RpbWUiOjE1MjE5MjcyOTQsInVzZXJfaWQiOiJyclJheWJXTlF2UUtLT3MwWG5STmRrVHVTU3YxIiwic3ViIjoicnJSYXliV05RdlFLS09zMFhuUk5ka1R1U1N2MSIsImlhdCI6MTUyMTk3NTY0NSwiZXhwIjoxNTIxOTc5MjQ1LCJlbWFpbCI6Im1hd3NAdGVzdC5mciIsImVtYWlsX3ZlcmlmaWVkIjpmYWxzZSwiZmlyZWJhc2UiOnsiaWRlbnRpdGllcyI6eyJlbWFpbCI6WyJtYXdzQHRlc3QuZnIiXX0sInNpZ25faW5fcHJvdmlkZXIiOiJwYXNzd29yZCJ9fQ.EkJOTKsjCYb_usmMEvh9eTZ8hAfdXvyg-x7DhpEvm6O1kSfXV4KmAWiJIMIboHvydq3gmuY2ytRsV1cLHAHIh63PM9XHKeVVMZ2OlqarMOLGJHlA9IH8m1PIfd3EB0BDDDz7xTHAUXAZtribYcu3N69UgteFokETokMrxakTbTLrZBFAl6vk9wMehnlABj9VTrLr0fmpQhKRBv6CXtkPrUYZlGJczZvhVU2McH7juj51esFWC-HjZF0yGZVZcc_xL-VmZaswEpKUR12uIQlzwZ6w9iChvVY9-dRcfLJB_RkwmbEyL-GM8UGdpQyl0GZ46MLwu9a9qOwXkoNYCqFdXQ")|]), ()))
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