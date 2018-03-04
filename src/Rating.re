open ServicesMocks;

open Model;

let component = ReasonReact.statelessComponent("Rating");

let note = 3;

let starsArray = [0, 0, 0, 0, 0]; /*put this in a state*/

module Star = {
    let component = ReasonReact.statelessComponent("Star");
    let make = (~checked, _) => {
        ...component, 
        render: self => 
        <div>
            (str(checked ? "1" : "0"))
        </div>
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
                            <Star key=(string_of_int(i)) checked=(i < note) />, 
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