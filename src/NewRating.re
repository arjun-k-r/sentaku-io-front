
open Model;
open Utils;

type globalState = 
  | Empty /* No rating added yet */
  | Loading
  | Error
  | Posted(rating)
  | Modified(rating);

type state = {
  globalState: globalState,
  rating: rating
};

type action=
  | EditedRate(int)
  | EditedComment(string)
  | PostRating
  | ModifyRating
  | PostedRating(rating)
  | ModifiedRating(rating)
  | FailedPostingRating;

/**
 * TODO 
 * A déplacer dans un module RatingEncode
 */
let encodeRating = (rating) =>
  Json.Encode.(
    object_([
      ("ownerId", string(rating.ownerId)),
      ("note", int(rating.rate)),
      ("comment", string(rating.comment))
  ])
);

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
        placeholder=(placeHolder)
        onChange=(reduce((evt) => valueFromEvent(evt)))
      />
  };
};

let getRating : training => rating = training => {
  switch(List.filter(
    (rating) => rating.trainingId === training.id,
    Array.to_list(optArr(training.ratingOverview.ratings)))) {
      | [rating] => rating
      | _ => {
        id: "",
        ownerId: "f1b3f890-2616-11e8-b467-0ed5f89f718b",
        rate: 1,
        comment: "",
        trainingId: training.id
    }
  };
};

let component = ReasonReact.reducerComponent("NewRating");

let make = (~training, ~user, ~connection, _children) => {
  ...component,
  initialState: () => {
    globalState: Empty, 
    rating: {
      id: "",
      ownerId: user.id,
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
            Fetch.fetchWithInit(apiUrl ++ "trainings/" ++ training.id ++ "/notes", 
              Fetch.RequestInit.make(~method_=Post, ~headers= Fetch.HeadersInit.makeWithArray([|("content-type", "application/json")|]),~body=Fetch.BodyInit.make @@ Js.Json.stringify(encodeRating(rating)), ()))
              |> then_(Fetch.Response.json)
              |> then_(json =>
                  json
                  |> RatingDecode.note
                  |> (rating => self.send(PostedRating(rating.rating)))
                  |> resolve
                )
              |> catch(_err =>
                  Js.Promise.resolve(self.send(FailedPostingRating))
                )
              |> ignore
          )
        ));
      | ModifyRating => 
      ReasonReact.UpdateWithSideEffects({globalState: Loading, rating}, 
      (
        self => Js.Promise.(
          Fetch.fetchWithInit(apiUrl ++ "trainings/" ++ training.id ++ "/notes/" ++ self.state.rating.id, 
            Fetch.RequestInit.make(~method_=Put, ~headers= Fetch.HeadersInit.makeWithArray([|("content-type", "application/json")|]),~body=Fetch.BodyInit.make @@ Js.Json.stringify(encodeRating(rating)), ()))
            |> then_(Fetch.Response.json)
            |> then_(json =>
                json
                |> RatingDecode.note
                |> (rating => self.send(ModifiedRating(rating.rating)))
                |> resolve
              )
            |> catch(_err =>
                Js.Promise.resolve(self.send(FailedPostingRating))
              )
            |> ignore
        )
      ));
      | PostedRating(rating) => ReasonReact.Update({globalState: Posted(rating), rating})
      | ModifiedRating(rating) => ReasonReact.Update({globalState: Posted(rating), rating})
      | FailedPostingRating => ReasonReact.Update({globalState: Error, rating})
          
  },
  didMount: _self => {
    ReasonReact.Update({globalState: Empty, rating: getRating(training)});
  },
  render: self =>
    switch self.state.globalState {
    | Empty => 
      <div id="test-swipe-3" className="col s12">
          <form className="col s12">
            <div className="row">
              <div className="input-field col s12">
              <h5> (str("Votre note : ")) </h5>
                <select value=(string_of_int(self.state.rating.rate)) onChange=(evt => self.send(EditedRate(int_of_string(valueFromEvent(evt)))))>
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
                  value=(self.state.rating.comment)
                />
              </div>
            </div>
            <div className="row center">
              (
                switch self.state.rating.id {
                | "" => <button onClick=(_evt => self.send(PostRating)) className="btn">(str("Envoyer"))</button>
                | _ => <button onClick=(_evt => self.send(ModifyRating)) className="btn">(str("Modifier"))</button>
                }
              )
            </div>
          </form>
        </div>
      | Error => <div> (str("Impossible de poster le commentaire :( !")) </div>
      | Loading => <div> (str("Chargement de la page ...")) </div>
      | Posted(_rating) => <div> (str("Message posté :) !")) </div> 
      | Modified(_rating) => <div> (str("Message modifié :) !")) </div>
    }
};