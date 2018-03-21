
open Model;

let component = ReasonReact.statelessComponent("Ratings");

let make = (~training, _children) => {
    ...component,
  render: _self =>
    <div id="test-swipe-2" className="row">
      (
        switch(training.ratingOverview.ratings) {
          | Some(ratings) => 
            [%bs.debugger];
            if(Array.length(ratings) === 0) {
              str("Aucune note")
            } else {
              ReasonReact.arrayToElement(Array.map(
                (rating : rating) =>
                  <Rating
                    key=(rating.id)
                    rating
                  />,
                ratings
              ))

            }
          | None => {
            [%bs.debugger];
            str("Aucune note");
          }
        }
      )
    </div>
};