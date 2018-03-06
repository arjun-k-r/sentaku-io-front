open Model;
/**
 * This module is the tab panel at the bottom of a training where the ratings are displayed
 */
let component = ReasonReact.reducerComponent("TrainingFooter");
let make = (children) => {
    ...component,
    reducer: ((), _) => ReasonReact.NoUpdate,
    render: self =>
        <div className="col m12 card">
            <ul id="tabs-swipe-demo" className="tabs">
            <li className="tab col s4">
                <a className="active" href="#test-swipe-1">
                (str("Description"))
                </a>
            </li>
            <li className="tab col s4">
                <a href="#test-swipe-2"> (str("Commentaire")) </a>
            </li>
            <li className="tab col s4">
                <a href="#test-swipe-3"> (str("Laisser un commentaire")) </a>
            </li>
            <li className="indicator" />
            </ul>
            <Description />
            <Ratings />
            /* <Rating /> */
        </div>
};