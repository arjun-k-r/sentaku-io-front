/**
 * This component is a tab panel which allows to view and rate a training.Arg
 * It allows also to modify a rating.
 *
 * US_02
 */

open Model;

let component = ReasonReact.statelessComponent("Rating");

let make = (~rating, _children) => {...component, render: _self => 
    <div className="col m12">
        <div className="col m1">
          <img src="images/myAvatar.png" className="circle responsive-img" />
        </div>
        <div className="col m10 commentaire">
          <h6> (str("Deleplanque Dylan")) </h6>
          <span> (str("Note: " ++ string_of_int(rating.rate))) </span>
          <p>
            (str(rating.comment))
          </p>
        </div>
      </div>
};