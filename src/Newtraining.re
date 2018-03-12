/**
 * This component allows to create a new training
 *
 * US_01
 */
open ServicesMocks;

open Model;

open TrainingDecode;

/*state that can be modified */
type state = {
    id: option(string),
    title: string,
    description: string,
    degreeLevel: int,
    etcsNumber: option(int),
    diploma: option(string),
    admissionModalities: string,
    logo: string,
    location: string,
    link: string,
    tags: option(array(string)),
    ratingOverview: ratingOverview
  };

  /* Actions : Post or Failed Posting*/
type action = 
  | PostTraining
  | FailedPostTraining;

  /* function to split tags */
let parseTags = (tags) => Js.String.split(",",tags);

/** Rest call header: application/json. prepare the token for authorization */
let make_headers = (token: option(string)) => {
    let content_type = ("content-type", "application/json");
    switch token {
    | None => [|content_type|]
    | Some(t) => [|content_type, ("authorization", "Token " ++ t)|]
    }
  };

/* REST call initialization  with Method, header, and data */
let makeInit = (method, token, data: option(Js.Json.t)) => {
    let defaultInit =
      Bs_fetch.RequestInit.make(
        ~method_=method,
        ~headers=Bs_fetch.HeadersInit.makeWithArray @@ make_headers(token)
      );
    switch data {
    | None => defaultInit()
    | Some(d) => defaultInit(~body=Bs_fetch.BodyInit.make @@ Js.Json.stringify(d), ())
    }
  };

  /** Json the responseText */
let parseNewTraining = (responseText) => {
    let json = Js.Json.parseExn(responseText);
};

/** Method create New Training that will send the request to the API and catch the response */
let createNewTraining = (createFunc, jsonData) => {
    open Js.Promise;
    let request = makeInit(Post, None, Some(jsonData));
    Bs_fetch.(
      fetchWithInit("https://sentaku-api-prod.herokuapp.com/api/v1/trainings"), request)
      |> then_(
           (response) => createFunc(Response.status(response), Response.text(response)) |> resolve
         )
    )
  };

  /** module EncodeTr to encode the training into a JSON */
module EncodeTr = {
    let encodeTraining = (training) => {
        open! Json.Encode;
        object_([
            ("title",str(training.title)),
            ("description",str(training.description)),
            ("degreeLevel",str(training.degreeLevel)),
            ("etcsNumber",str(training.etcsNumber)),
            ("diploma",str(training.diploma)),
            ("admissionModalities",str(training.admissionModalities)),
            ("logo",str(training.logo)),
            ("localisation",str(training.localisation)),
            ("link",str(training.link)),
            ("tags",parseTags(training.tags) |> Json.Encode.stringArray),
            ("ratingOverview",str(training.ratingOverview))
        ])) 
    };
    let training = (tr) => Json.Encode.(object_([("training",encodeTraining(tr))]));
};

/** method to create a training : take the state when event. Encode Json, and create a new Training with request */
let createTraining = ({ReasonReact.state, reduce}, event) => {
    ReactEventRe.Mouse.preventDefault(event);
    let jsonRequest = Encode.training(state);
      |> Js.Promise.then_(
           (json) => {
             let newTraining = parseNewTraining(json);
             createNewTraining(updateState, jsonRequest) |> ignore;
  };

/** component */
let component = ReasonReact.reducerComponent("NewTraining");

/** reducer that catch the action. render to print classes */
let make = children => {
    ...component,
    reducer: (action,_state) =>
        switch action{
        | PostTraining => ReasonReact.Update(...state)
        },
        render: (self) => {
            let {ReasonReact.state, reduce} = self;
            <div className="createTraining">
            <div className="container page">
              <div className="row">
                <div className="col-md-6 offset-md-3 col-xs-12">
                  <h1 className="text-xs-center"> (str("Creer une formation")) </h1>
                  <form>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="Titre"
                        value=state.title
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="Description"
                        value=state.description
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="degreeLevel"
                        value=state.degreeLevel
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="etcsNumber"
                        value=state.etcsNumber
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="diploma"
                        value=state.diploma
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="admissionModalities"
                        value=state.admissionModalities
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="logo"
                        value=state.logo
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="localisation"
                        value=state.localisation
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="link"
                        value=state.link
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="tags,tags,tags"
                        value=state.tags
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="ratingOverviewTitre"
                        value=state.ratingOverview
                      />
                    </fieldset>
                    <button
                      onClick=(reduce(createTraining(self)))
                      className="btn btn-lg btn-primary pull-xs-right">
                      (str("Creer"))
                    </button>
                  </form>
                </div>
              </div>
            </div>
          </div>
        }
};