open ServicesMocks;

open Model;

open TrainingDecode;

type state = 
  | Empty /* No rating added yet */
  | Loading
  | Posted(rating);

type action=
  | PostRating
  | PostedRating(rating)
  | FailedPostingRating;

let component = ReasonReact.reducerComponent("NewRating");


let testData = 
  Json.Encode.(
    object_([
      ("id", string("a7383-3782-3783-3283")),
      ("trainingId", string("382461c8-9cf9-4f3d-9132-6126999c968e")),
      ("note", int(4)),
      ("comment", string("Une bonne formation dans l'ensemble"))
  ])
  );

let _ = 
  Json.Encode.(
    object_([
      ("x", int(42)),
      ("foo", string("bar"))
    ])
    |> Js.log
  );

let initRatingRequest = (data) => {
  Fetch.RequestInit.make(~method_ = Post, 
                        ~body=Fetch.BodyInit.make @@ Js.Json.stringify(data), ());
};

let make = children => {
  ...component,
  initialState: _state => Empty,
  reducer: (action, _state) => 
  switch action {
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
    | FailedPostingRating => ReasonReact.NoUpdate();
 /* ReasonReact.UpdateWithSideEffects(Loading, 
    (
      self => Js.Promise.(
        Fetch.fetchWithInit(
          "https://sentaku-api-prod.herokuapp.com/api/v1/notes/trainingId/ca7c1b46-a66e-44f8-b418-a823ccdd57a2", 
          Fetch.RequestInit.make(~method_=Post, Fetch.BodyInit.make(
            "\"id\":\"a7383-3782-3783-3283\", \"trainingId\":\"\", \"note\":3, \"comment\":\"Une bonne formation dans l'esnemble\"")
      )
    ))); */

  },
  render: self =>
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
            <textarea id="icon_prefix2" className="materialize-textarea" />
          </div>
        </div>
        <div className="row center">
          <button className="btn">(str("Envoyer"))</button>
        </div>
      </form>
    </div>
};