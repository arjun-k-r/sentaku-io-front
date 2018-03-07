open Model;
/**
 * This module shows the training infos
 */
let component = ReasonReact.statelessComponent("TrainingHeader");
let make = (children) => {
    ...component,
    render: self =>
        <div className="col m12 card">
            <div className="col m3">
            <img src="images/miage.png" className="responsive-img" />
            </div>
            <div className="col m9">
            <div className="col m12 center">
                <h1 className="formation-title"> (str("Miage lille")) </h1>
            </div>
            <div className="col m12 center">
                <div className="col m4"> (str("BONJOURNote la plus basse : 12")) </div>
                <div className="col m4"> (str("Moyenne des notes : 17")) </div>
                <div className="col m4"> (str("Note la plus haute : 20")) </div>
            </div>
            <div className="col m12 list-tags">
                <ul>
                <li> <span className="tag orange"> (str("Lille")) </span> </li>
                <li>
                    <span className="tag green"> (str("Informatique")) </span>
                </li>
                <li> <span className="tag blue"> (str("Master")) </span> </li>
                <li> <span className="tag red"> (str("Miage")) </span> </li>
                </ul>
            </div>
            </div>
        </div>
};