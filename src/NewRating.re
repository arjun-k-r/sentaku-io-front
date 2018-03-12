open ServicesMocks;

open Model;

open TrainingDecode;

type globalState = 
  | Empty /* No rating added yet */
  | Loading
  | Error
  | Posted(rating);

type state = {
  globalState: globalState,
  rating: rating
};

type action=
  | EditedComment(string)
  | PostRating
  | PostedRating(rating)
  | FailedPostingRating;

let testData = 
  Json.Encode.(
    object_([
      ("ownerId", string("f1b3f890-2616-11e8-b467-0ed5f89f718b")),
      ("note", int(4)),
      ("comment", string("Une bonne formation dans l'ensemble"))
  ])
);

let initRatingRequest = (data) => {
Fetch.RequestInit.make(~method_ = Post, 
                      ~body=Fetch.BodyInit.make @@ Js.Json.stringify(data), ());
};

let valueFromEvent = (evt) : string => (
  evt
  |> ReactEventRe.Form.target
  |> ReactDOMRe.domElementToObj
)##value;

module Input = {
  type state = string;
  let component = ReasonReact.reducerComponent("Input");
  let make = (~placeHolder, _) => {
    ...component,
    initialState: () => "",
    reducer: (newText, _text) => ReasonReact.Update(newText),
    render: ({state: text, reduce}) =>
      <input
        value=text
        _type="text"
        placeholder=(placeHolder)
        onChange=(reduce((evt) => valueFromEvent(evt)))
      />
  };
};

let component = ReasonReact.reducerComponent("NewRating");

let make = (~training, children) => {
  ...component,
  initialState: () => {
    globalState: Empty, 
    rating:{
      id: 0,
      ownerId: "",
      rate: 0,
      comment: "",
      trainingId: 0
    }
  },
  reducer: (action, {globalState, rating}) => 
    switch action {
      | EditedComment(comment) => ReasonReact.Update({globalState, rating: {...rating, comment: comment}})
      | PostRating => 
      ReasonReact.UpdateWithSideEffects({globalState: Loading, rating}, (
        self => Js.Promise.(
          Fetch.fetchWithInit("https://sentaku-api-prod.herokuapp.com/api/v1/trainings/382461c8-9cf9-4f3d-9132-6126999c968e/notes", 
            Fetch.RequestInit.make(~method_=Post, ~headers= Fetch.HeadersInit.makeWithArray([|("content-type", "application/json")|]),~body=Fetch.BodyInit.make @@ Js.Json.stringify(testData), ()))
            |> then_(Fetch.Response.json)
            |> then_(json =>
                json
                |> RatingDecode.rating
                /* |> (training => {
                  Js.log(training);
                  training
                }) */
                |> (rating => self.send(PostedRating(rating.rating)))
                |> resolve
              )
            |> catch(_err =>
                Js.Promise.resolve(self.send(FailedPostingRating))
              )
            |> ignore
        )
        ));
      | PostedRating(training) => ReasonReact.Update({globalState: Posted(training), rating})
      | FailedPostingRating => ReasonReact.Update({globalState: Error, rating})
          
  },
  didMount: {{rating}} => {
    ReasonReact.Update({globalState: Empty, rating});
  },
  /* switch action {
    | PostRating => ReasonReact.UpdateWithSideEffects(Loading, (
      self => Js.Promise.(
        Fetch.fetchWithInit(
          "https://sentaku-api-prod.herokuapp.com/api/v1/notes/trainingId/382461c8-9cf9-4f3d-9132-6126999c968e",
          initRatingRequest(testData)
        )
        |> then_(Fetch.Response.json)
        |> then_(json => 
          json
          |> RatingDecode.rating
          |> resolve
        )
      )));
    | PostedRating(rating) => ReasonReact.NoUpdate();
    | FailedPostingRating => ReasonReact.NoUpdate(); */
 /* ReasonReact.UpdateWithSideEffects(Loading, 
    (
      self => Js.Promise.(
        Fetch.fetchWithInit(
          "https://sentaku-api-prod.herokuapp.com/api/v1/notes/trainingId/ca7c1b46-a66e-44f8-b418-a823ccdd57a2", 
          Fetch.RequestInit.make(~method_=Post, Fetch.BodyInit.make(
            "\"id\":\"a7383-3782-3783-3283\", \"trainingId\":\"\", \"note\":3, \"comment\":\"Une bonne formation dans l'esnemble\"")
      )
    ))); */

  /* }, */
  render: self =>
    switch self.state {
    | Empty => 
      <div id="test-swipe-3" className="col s12">
          <form className="col s12">
            <div className="row">
              <div className="input-field col s20">
              <h5> (str("Votre note : ")) </h5>
                <select>
                  <option value="1">(str("1"))</option>
                  <option value="2">(str("2"))</option>
                  <option value="3">(str("3"))</option>
                  <option value="4">(str("4"))</option>
                  <option value="5">(str("5"))</option>
                </select>
              </div>
            </div>
            <div className="row">
              <div className="input-field col s12">
                <h5> (str("Votre commentaire : ")) </h5>
                <textarea
                  placeholder="Commentaire"
                  key="comment_input" 
                  onChange=((evt) => self.send(EditedComment(valueFromEvent(evt))))
                />
              </div>
            </div>
            <div className="row center">
              <button onClick=(_evt => self.send(PostRating)) className="btn">(str("Envoyer"))</button>
            </div>
          </form>
        </div>
      | Error => <div> (str("Impossible de poster le commentaire :( !")) </div>
      | Loading => <div> (str("Chargement de la page ...")) </div>
      | Posted(rating) => <div>(str("Posté :) !"))</div> 
    }
    
};