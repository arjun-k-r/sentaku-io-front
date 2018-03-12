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
  | EditedRate(int)
  | EditedComment(string)
  | PostRating
  | PostedRating(rating)
  | FailedPostingRating;

let testData = (rating) =>
  Json.Encode.(
    object_([
      ("ownerId", string(rating.ownerId)),
      ("note", int(rating.rate)),
      ("comment", string(rating.comment))
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
      id: -1,
      ownerId: "f1b3f890-2616-11e8-b467-0ed5f89f718b",
      rate: 1,
      comment: "",
      trainingId: training.id
    }
  },
  reducer: (action, {globalState, rating}) => 
    switch action {
      | EditedComment(comment) => ReasonReact.Update({globalState, rating: {...rating, comment}})
      | EditedRate(rate) => ReasonReact.Update({globalState, rating: {...rating, rate}});
      | PostRating => 
      ReasonReact.UpdateWithSideEffects({globalState: Loading, rating}, 
        (
          self => Js.Promise.(
            Fetch.fetchWithInit("https://sentaku-api-prod.herokuapp.com/api/v1/trainings/" ++ training.id ++ "/notes", 
              Fetch.RequestInit.make(~method_=Post, ~headers= Fetch.HeadersInit.makeWithArray([|("content-type", "application/json")|]),~body=Fetch.BodyInit.make @@ Js.Json.stringify(testData(rating)), ()))
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
  didMount: self => {
    ReasonReact.Update({globalState: Empty, rating: self.state.rating});
  },
  render: self =>
    switch self.state.globalState {
    | Empty => 
      <div id="test-swipe-3" className="col s12">
          <form className="col s12">
            <div className="row">
              <div className="input-field col s20">
              <h5> (str("Votre note : ")) </h5>
                <select onChange=(evt => self.send(EditedRate(int_of_string(valueFromEvent(evt)))))>
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