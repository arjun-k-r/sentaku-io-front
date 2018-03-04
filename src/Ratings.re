open ServicesMocks;

open Model;

let component = ReasonReact.statelessComponent("Ratings");

let make = children => {
    ...component,
  render: self =>
    <div id="test-swipe-2" className="col s12" >
      <br />
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
      <div className="col m12">
        <div className="col m1">
          <img src="images/myAvatar2.png" className="circle responsive-img" />
        </div>
        <div className="col m10 commentaire">
          <h6> (str("Bourre Lucas")) </h6>
          <span> (str("Note: 19")) </span>
          <p>
            (
              str(
                "Ma formation \195\160 la MIAGE date de presque 30 ans. A l'\195\169poque, il n'existait que tr\195\168s peu de formations \195\160 l'informatique\r\n                        et ce que je me souviens, c'est qu'\195\160 l'obtention du dipl\195\180me, je me suis dirig\195\169e vers de l'informatique technique\r\n                        (syst\195\168me et r\195\169seau) et j'ai d\195\169couvert que l'universit\195\169 \195\169tait assez en retard ..."
              )
            )
          </p>
        </div>
      </div>
    </div>
};