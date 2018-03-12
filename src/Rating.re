/**
 * This component is a tab panel which allows to view and rate a training.Arg
 * It allows also to modify a rating.
 *
 * US_02
 */
open ServicesMocks;

open Model;

let component = ReasonReact.statelessComponent("Rating");

let make = (~rating, children) => {...component, render: self => 
    <div className="col m12">
        <div className="col m1">
          <img src="images/myAvatar.png" className="circle responsive-img" />
        </div>
        <div className="col m10 commentaire">
          <h6> (str("Deleplanque Dylan")) </h6>
          <span> (str("Note: 17")) </span>
          <p>
            (
              str(
                "Les intervenants ext\195\169rieurs sont passionnants : un professionnel de la d\195\169fense pour la s\195\169curit\195\169 SI, des op\195\169rationnels\r\n                        dans certaines mati\195\168res de finances. Certains enseignants chercheurs sont des r\195\169f\195\169rences dans leur domaine,\r\n                        d'autre sont plus \195\169loign\195\169s du monde de la professionnel."
              )
            )
          </p>
        </div>
      </div>
};