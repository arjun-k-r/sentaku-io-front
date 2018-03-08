/**
 * This component is a tab panel which allows to view and rate a training.Arg
 * It allows also to modify a rating.
 *
 * US_02
 */
open ServicesMocks;

open Model;

let component = ReasonReact.statelessComponent("Rating");

let make = children => {...component, render: self => <div />};