/**
 * This component allows to create a new training
 *
 * US_01
 */
open ServicesMocks;

open Model;

let component = ReasonReact.statelessComponent("NewTraining");

let make = children => {...component, render: self => <div />};