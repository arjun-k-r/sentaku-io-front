open ServicesMocks;

open Model;
open Rating;

let component = ReasonReact.statelessComponent("Ratings");

let make = (~training, children) => {
    ...component,
  render: self =>
    <div id="test-swipe-2" className="col s12">
      (
        switch(training.ratingOverview.ratings) {
          | Some(ratings) => 
          if(Array.length(ratings) === 0) {
            str("Aucune note")
          } else {
            ReasonReact.arrayToElement(Array.map(
              (rating : rating) =>
                <Rating
                  key=(string_of_int(rating.id))
                  rating
                />,
              ratings
            ))

          }
          | None => str("Aucune note")
        }
      )
    </div>
};