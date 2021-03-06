
open Model;

let component = ReasonReact.statelessComponent("Ratings");

let make = (~training, ~userInfos, ~connection, _children) => {
    ...component,
  render: _self =>
    <div id="test-swipe-2" className="row">
      (
        switch(training.ratingOverview.ratings) {
          | Some(ratings) => 
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
            str("Aucune note");
          }
        }
      )
    </div>
};