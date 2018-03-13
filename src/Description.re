open Model;

let component = ReasonReact.statelessComponent("Description");

let make = (~training, _children) => {
    ...component,
    render: (_self) => 
        <div id="test-swipe-1" className="col s12 active">
            <h5>(str("Les objectifs de la formation MIAGE"))</h5>
            <p>
                (str(training.description))
            </p>
        </div>
};