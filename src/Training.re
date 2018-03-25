/**
 * This component is the page which show a training details
 *
 * US_07
 */
open Model;
open Utils;
open FirebaseConfig;
open BsFirebase.ReasonFirebase.Auth;
open TrainingDecode;


/**
* This module shows the training infos
*/
module TrainingHeader = {
  let randomColor = (n) =>
    switch n {
    | 0 => "orange"
    | 1 => "blue"
    | 2 => "red"
    | 3 => "green"
    | _ => "white"
    };

  let component = ReasonReact.statelessComponent("TrainingHeader");
  let make = (~training, _children) => {
      ...component,
      render: _self =>
          <div className="col m12 card">
              <div className="col m3">
              <img src=(training.logo) className="responsive-img" />
              </div>
              <div className="col m9">
              <div className="col m12 center">
                  <h1 className="formation-title">(str(training.title))</h1>
              </div>
              <div className="col m12 center">
              <a href=(training.link)>(str("Lien du site"))</a>
              </div>
              <div className="col m12 center">
                  (str("Localisation géographique : " ++ training.location))
              </div>
              <div className="col m12 center">
                  <div className="col m4"> (str("ETCS : " ++ 
                    optIntStr(training.etcsNumber)))
                  </div>
                  <div className="col m4"> (str("Modalités d'admission : " ++ training.admissionModalities)) </div>
                  <div className="col m4"> (str("Niveau d'étude : " ++ string_of_int(training.degreeLevel))) </div>
              </div>
              <div className="col m12 center">
                  <div className="col m6"> (str("Moyenne des notes : " ++ optFloatStr(training.ratingOverview.average))) </div>
                  <div className="col m6"> (str("Diplôme délivré : " ++ opt(training.diploma))) </div>
              </div>
              <div className="col m12 list-tags">
              <ul>
                  (
                    switch(training.tags) {
                      | Some(tags) => 
                      if(Array.length(tags) === 0) {
                        str("Aucun tag")
                      } else {
                        ReasonReact.arrayToElement(Array.map(
                          (tag : string) =>
                          <li key=(tag)> <span 
                            className=("tag " ++ randomColor(Random.int(3)))> (str(tag)) </span> </li>,
                          tags
                        ))
  
                      }
                      | None => str("Aucun tag")
                    }
                  )
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
  let make = (~training, ~userInfos, ~connection, _children) => {
    ...component,
    render: _self =>
      <div className="col m12 card">
        /* <div className="col m12">
          <ul id="tabs-swipe-demo" className="tabs">
            <li className="tab col s4">
                <a className="active" href="#test-swipe-1">
                  (str("Description"))
                </a>
            </li>
            <li className="tab col s4">
                <a href="#test-swipe-2"> 
                  (str("Commentaire"))
                </a>
            </li>
            <li className="tab col s4">
                <a href="#test-swipe-3">
                  (str("Laisser un commentaire"))
                </a>
            </li>
            <li className="indicator" />
          </ul>
        </div> */
        <Description training/>
        (
          switch userInfos {
            | Some(user) => <NewRating training user=user connection=connection/>
            | None => <div> <h3>(str("Connectez vous pour pouvoir poster un message"))</h3></div>
            }
        )
        
        <Ratings training userInfos=userInfos connection=connection/>
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
let make = (~id, ~userInfos, ~connection, _children) => {
  ...component,
  initialState: _state => Loading,
  reducer: (action, _state) => 
    switch action {
      | TrainingFetch =>
      switch userInfos {
      | Some(user) => 
      ReasonReact.UpdateWithSideEffects(
        Loading,
        (
          self =>
          {
            Js.Promise.(
              Fetch.fetchWithInit(apiUrl ++ "trainings/"++ id, 
                Fetch.RequestInit.make(~method_=Get, ~headers= Fetch.HeadersInit.makeWithArray([|("authorization", user.token)|]), ()))
              |> then_(Fetch.Response.json)
              |> then_(json =>
                  json
                  |> TrainingDecode.training
                  |> (training => self.send(TrainingFetched(training.training)))
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
      | None => ReasonReact.NoUpdate
      }
        
      | TrainingFetched(training) => ReasonReact.Update(Loaded(training))
      | TrainingFailedToFetch => ReasonReact.Update(Error)
    },
  didMount: self => {
    /* onAuthStateChanged(auth,  ~nextOrObserver = (_user) => {
      self.send(TrainingFetch);
    }, ~error= err => Js.log(err), ~completed= u => Js.log(u)); */
    self.send(TrainingFetch);
    ReasonReact.NoUpdate;
  },
  render: (self) =>
    switch self.state {
      | Error => <div> (str("Nous n'arrivons pas à récupérer la formation :( !")) </div>
      | Loading => <div> (str("Chargement de la page ...")) </div>
      | Loaded(training) =>
        <div className="row content">
          <div className="row">
            <TrainingHeader training />
            <TrainingFooter training userInfos=userInfos connection=connection/>
          </div>
        </div>
    }
};