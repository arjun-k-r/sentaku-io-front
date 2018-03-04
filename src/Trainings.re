/**
 * This component is the main page which displays a list of trainings
 *
 * US_06
 */
open ServicesMocks;

open Model;

let component = ReasonReact.statelessComponent("Trainings");

let make = children => {
  ...component,
  render: self => <div> (ReasonReact.stringToElement("Hello")) </div>
};