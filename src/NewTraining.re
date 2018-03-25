/**
 * This component allows to create a new training
 *
 * US_01
 */
open ServicesMocks;
open Utils;
open Model;
open FirebaseConfig;
open BsFirebase.ReasonFirebase.Storage;
open BsFirebase.ReasonFirebase.Auth;
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
  | EditedTitle(string)
  | EditedDescription(string)
  | EditedDegreeLevel(int)
  | EditedEtcsNumber(option(int))
  | EditedDiploma(option(string))
  | EditedAdmissionModalities(string)
  | EditedLogo(string)
  | EditedLocation(string)
  | EditedLink(string)
  | EditedTags(option(array(string)))
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
    ("ETCSNumber",int(optInt(training.etcsNumber))),
    ("diploma",string(opt(training.diploma))),
    ("admissionModalities",string(training.admissionModalities)),
    ("logo",string(training.logo)),
    ("location",string(training.location)),
    ("link",string(training.link)),
    ("tags",string(optArray(training.tags))) /**,
    ("ratingOverview",string(""))*/
  ])
);

/** take the value from an event */
let valueFromEvent = (evt) : string =>(
  evt 
  |> ReactEventRe.Form.target
  |> ReactDOMRe.domElementToObj
)##value;

/** component */
let component = ReasonReact.reducerComponent("Newtraining");


let make = (~userInfos, ~connection, _children) => {
  ...component,
  initialState:() =>{
    globalState:Empty,
    training:{
      id: "-1",
      etcsNumber:None,
      title: "", 
      description:"",
      admissionModalities:"",
      diploma:None,
      logo:"",
      degreeLevel:0,
      location:"",
      link:"",
      tags:None,
      ratingOverview:{average:None,ratings:None}
    }
  }, 
  reducer:(action,{globalState,training}) =>
    switch action{
    | EditedTitle(title) => ReasonReact.Update({globalState, training: {...training, title}})
    | EditedDescription(description) =>  ReasonReact.Update({globalState, training: {...training, description}})
    | EditedDegreeLevel(degreeLevel) =>  ReasonReact.Update({globalState, training: {...training, degreeLevel}})
    | EditedEtcsNumber(etcsNumber) =>  ReasonReact.Update({globalState, training: {...training, etcsNumber }})
    | EditedDiploma(diploma) =>  ReasonReact.Update({globalState, training: {...training, diploma}})
    | EditedAdmissionModalities(admissionModalities) =>  ReasonReact.Update({globalState, training: {...training, admissionModalities}})
    | EditedLogo(logo) =>  ReasonReact.Update({globalState, training: {...training, logo}})
    | EditedLocation(location) =>  ReasonReact.Update({globalState, training: {...training, location}})
    | EditedLink(link) =>  ReasonReact.Update({globalState, training: {...training, link}})
    | EditedTags(tags) =>  ReasonReact.Update({globalState, training: {...training, tags}})
    | PostTraining =>  ReasonReact.UpdateWithSideEffects({globalState: Loading, training},
    (
      self => Js.Promise.(
        Fetch.fetchWithInit(apiUrl ++ "training",
          Fetch.RequestInit.make(~method_=Post, ~headers = Fetch.HeadersInit.makeWithArray([|("content-type","application/json"),("authorization","eyJhbGciOiJSUzI1NiIsImtpZCI6ImY1YjE4Mjc2YTQ4NjYxZDBhODBiYzhjM2U5NDM0OTc0ZDFmMWRiNTEifQ.eyJpc3MiOiJodHRwczovL3NlY3VyZXRva2VuLmdvb2dsZS5jb20vc2VudGFrdS1pbyIsImF1ZCI6InNlbnRha3UtaW8iLCJhdXRoX3RpbWUiOjE1MjE5MjcyOTQsInVzZXJfaWQiOiJyclJheWJXTlF2UUtLT3MwWG5STmRrVHVTU3YxIiwic3ViIjoicnJSYXliV05RdlFLS09zMFhuUk5ka1R1U1N2MSIsImlhdCI6MTUyMTk4ODA0NCwiZXhwIjoxNTIxOTkxNjQ0LCJlbWFpbCI6Im1hd3NAdGVzdC5mciIsImVtYWlsX3ZlcmlmaWVkIjpmYWxzZSwiZmlyZWJhc2UiOnsiaWRlbnRpdGllcyI6eyJlbWFpbCI6WyJtYXdzQHRlc3QuZnIiXX0sInNpZ25faW5fcHJvdmlkZXIiOiJwYXNzd29yZCJ9fQ.BM96kMmzAj1yPr_YKDIqFOdybn5JFm3P7jxNobuTP9bgq3b_A0awG79KitZnniJWJ1eIJyinPIuLV0LF3XXuyq6J4DywHgflsSKtE_THNM95mliEwlNhbri6QxcevwhAoK82KGZ4A7J83vh0xVHQeX7fZ6LfJMf1WwHXOQFF4wxKQvL5294Nwul2dT7lTWJGuv_x9OmjbSJ3N-G2_f6ekIPENYqKPokmVWQwRtwZqVIGfJiGGqZZdGpIrB-K-k3LbSmY3KzfYeGxrMv4ZDQIrs_HXFsq9iKUveheeuBnWz6BzA52B-Ww-o2H6pSLHGXLx7nHuet-LK7MPVL6VHqKCg")|])
          ,~body=Fetch.BodyInit.make @@ Js.Json.stringify(data(training)), ()))
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
                <div className="col m8 offset-m2">
                  <h3> (str("Creer une formation")) </h3>
                  <form className="col s12">
                      <fieldset className="form-group">
                      (str("Logo : "))
                      <input
                        _type="file"
                        className="form-control form-control-lg"
                        placeholder="Lien du Logo" key="comment_input"
                        onChange=(evt => self.send(EditedLogo(valueFromEvent(evt))))
                      />
                    </fieldset>
                    <fieldset className="form-group"> 
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="Titre" key="comment_input"
                        onChange=(evt => self.send(EditedTitle(valueFromEvent(evt))))
                        />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="Description" key="comment_input"
                        onChange=(evt => self.send(EditedDescription(valueFromEvent(evt))))
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="DegreeLevel" key="comment_input" 
                        onChange=(evt => self.send(EditedDegreeLevel(int_of_string(valueFromEvent(evt)))))
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="Nombre d ETCS" key="comment_input"
                        onChange=(evt => {
                          let etcs = valueFromEvent(evt);
                          let etcsInt = switch etcs {
                          | "" => None
                          | _ => Some(int_of_string(etcs))
                          };

                          self.send(EditedEtcsNumber(etcsInt))
                        })
                        
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="Diplome" key="comment_input"
                        onChange=(evt => {
                          let diploma = valueFromEvent(evt);
                          let diplomaStr = switch diploma {
                          | "" => None
                          | _ => Some(diploma)
                          };
                          self.send(EditedDiploma(diplomaStr));
                        }) 
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="Modalites d inscription" key="comment_input"
                        onChange=(evt => self.send(EditedAdmissionModalities(valueFromEvent(evt))))
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="Localisation" key="comment_input"
                        onChange=(evt => self.send(EditedLocation(valueFromEvent(evt))))
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="Url vers la formation" key="comment_input"
                        onChange=(evt => self.send(EditedLink(valueFromEvent(evt))))
                      />
                    </fieldset>
                    <fieldset className="form-group">
                      <input
                        _type="text"
                        className="form-control form-control-lg"
                        placeholder="Liste de tags" key="comment_input"
                        onChange=(evt => {
                          let tags = valueFromEvent(evt);
                          let tagsArray =
                           switch tags{
                          | "" => None
                          | _ => None
                          };
                      
                          self.send(EditedTags(tagsArray));
                        })
                      />
                    </fieldset>
                    <div className="center">
                    <button
                      onClick=(_evt => self.send(PostTraining))
                      className="btn btn-lg btn-primary pull-xs-right">
                      (str("Creer"))
                    </button>
                    </div>
                  </form>
                </div>

          | Error => <div> (str("Erreur lors de la creation de la formation ! :( ")) </div>
          | Loading => <div> (str("Chargement...")) </div>
          | Posted(training) => <div> (str("Formation envoyée !")) </div>
          }
        };