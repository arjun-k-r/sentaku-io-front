/**
 * This component allows to create a new training
 *
 * US_01
 */
open ServicesMocks;

open Model;

let component = ReasonReact.statelessComponent("NewTraining");

let make = _children => {...component, render: _self => <div />};