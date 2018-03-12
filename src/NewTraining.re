/**
 * This component allows to create a new training
 *
 * US_01
 */
open ServicesMocks;

open Model;

open TrainingDecode;


/** globalState to say what is the current action */
type globalState =
  | Empty
  | Loading
  | Error
  | Posted(training);

/*state that can be modified */
type state = {
  globalState:globalState,
  training:training
  };

  /* Actions : Post, Posted or Failed Posting*/
type action = 
  | PostTraining
  | PostedTraining(training)
  | FailedPostTraining;

  /* function to split tags */
let parseTags = (tags) => Js.String.split(",",tags);

/** Data encoder. For the future, to put in TrainingEncode. */
let data = (training) => 
Json.Encode.(
  object_([
    ("title",string(training.title)),
    ("description",string(training.description)),
    ("degreeLevel",int(training.degreeLevel)),
    ("etcsNumber",int(training.etcsNumber)),
    ("diploma",string(training.diploma)),
    ("admissionModalities",string(training.admissionModalities)),
    ("logo",string(training.logo)),
    ("localisation",string(training.localisation)),
    ("link",string(training.link)),
    ("tags",parseTags(training.tags) |> Json.Encode.stringArray),
    ("ratingOverview",string(training.ratingOverview))
  ])
);

/** take the value from an event */
let valueFromEvent = (evt) : string =>(
  evt 
  |> ReactEventRe.Form.target
  |> ReactDOMRe.domElementToObj
)##value;

/** component */
let component = ReasonReact.reducerComponent("NewTraining");


let make = (~training, children) => {
  ...component,
  initialState:() =>{
    globalState:Empty,
    training:{
      id: "-1",
      etcsNumber: Some(-1),
      title: "", 
      description:"",
      admissionModalities:"",
      diploma:Some(""),
      logo:"",
      degreeLevel:-1,
      location:"",
      link:"",
      tags:Some([|""|]),
      ratingOverview:{average:Some(-1),ratings:Some([|rating|])}
    }
  }, 
  reducer:(action,{globalState,training}) =>
    switch action{
    | PostTraining =>
    ReasonReact.UpdateWithSideEffects({globalState: Loading, training},
    (
      self => Js.Promise.(
        Fetch.fetchWithInit("http://sentaku-api-prod.herokuapp.com/api/v1/training",
          Fetch.RequestInit.make(~method_=Post, ~headers = Fetch.HeadersInit.makeWithArray([|("content-type","application/json")|]),~body=Fetch.BodyInit.make @@ Js.Json.stringify(data(training)), ()))
          |> then_(Fetch.Response.json)
          |> then_(json =>
              json 
              |> TrainingDecode.training
              |> (training => self.send(PostedTraining(training.training)))
              |> resolve
            )
          |> catch(_err =>
              Js.Promise.resolve(self.send(FailedPostTraining))
           )
          |> ignore
        )
      ));
      | PostedTraining(training) => ReasonReact.Update({globalState:Posted(training),training})
      | FailedPostTraining => ReasonReact.Update({globalState:Error,training})
      }, 
      didMount: self =>{
        ReasonReact.Update({globalState:Empty, training:self.state.training})
      },
        render: (self) => 
          switch self.state.globalState{
          | Empty =>
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
                        placeholder="Title"
                        value="title"
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="Description"
                        value="description"
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="degreeLevel"
                        value="degreeLevel"
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="etcsNumber"
                        value="etcsNumber"
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="diploma"
                        value="diploma"
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="admissionModalities"
                        value="admissionModalities"
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="logo"
                        value="logo"
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="localisation"
                        value="localisation"
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="link"
                        value="link"
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="tags,tags,tags"
                        value="tags"
                      />
                    </fieldset>
                  /*  <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="ratingOverviewTitre"
                        value="ratingOverview"
                      />
                    </fieldset>*/
                    <button
                      onClick=(_evt => self.send(PostTraining))
                      className="btn btn-lg btn-primary pull-xs-right">
                      (str("Creer"))
                    </button>
                  </form>
                </div>
              </div>
            </div>
          </div>
          | Error => <div> (str("Erreur lors de la creation de la formation.")) </div>
          | Loading => <div> (str("Chargement...")) </div>
          | Posted(training) => <div> (str("Formation envoyée !")) </div>
          }
};