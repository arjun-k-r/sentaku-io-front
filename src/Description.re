open ServicesMocks;

open Model;

let component = ReasonReact.statelessComponent("Description");

let make = (~training, children) => {
    ...component,
    render: (self) => 
        <div id="test-swipe-1" className="col s12 active">
            <h5>(str("Les objectifs de la formation MIAGE"))</h5>
            <p>
                (str(training.description))
            </p>
        </div>
};