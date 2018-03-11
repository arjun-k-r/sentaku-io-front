open ServicesMocks;

open Model;

type starAction = 
  | OnStar(int)
  | OutStar(int)
  | StarClicked(int);


let component = ReasonReact.statelessComponent("NewRating");

let rating = 3;

let starsArray = [0, 0, 0, 0, 0] /*put this in a state*/;

module Star = {
  type state = {shownRating: int};
  let component = ReasonReact.reducerComponent("Star");
  let make = (~id, _) => {
    ...component,
    initialState: () => {
      shownRating : 0
    },
    reducer: (starAction, _) =>
      switch starAction {
      | OnStar(id) => Js.log(id);ReasonReact.Update({shownRating : id})
      | OutStar(id) => ReasonReact.Update({shownRating : rating})
      | StarClicked(id) => ReasonReact.Update({shownRating : rating})
      },
    render: (self) => {
      <div> <img
      onMouseEnter=(self.reduce((_evt) => OnStar(id))) 
       src=(id <= self.state.shownRating ? "images/star-filled.png" : "images/star-stroke.png") /> </div>
    }
  };
};

let make = children => {
  ...component,
  render: self =>
    <div id="test-swipe-3" className="col s12">
      <form className="col s12">
        <div className="row">
          <div className="input-field col s20">
            (
              ReasonReact.arrayToElement(
                Array.of_list(
                  List.mapi(
                    (i, item) =>
                      <Star key=(string_of_int(i)) id=i/>,
                    starsArray
                  )
                )
              )
            )
          </div>
        </div>
        <div className="row">
          <div className="input-field col s12">
            <h5> (str("Votre commentaire : ")) </h5>
            <textarea id="icon_prefix2" className="materialize-textarea" />
          </div>
        </div>
      </form>
    </div>
};