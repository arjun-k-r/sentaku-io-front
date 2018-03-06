/**
 * This component is the page which show a training details
 *
 * US_07
 */
open TrainingHeader;
open TrainingFooter;

open Model;

/* let theTraining :string = "c2337f32-0b69-4434-846c-6107bc4b1904"; */

type state =
  | Loading
  | Error
  | Loaded(training);
/*
type action =
  | TrainingFetch
  | TrainingFetched(training)
  | TrainingFailedToFetch; */


let component = ReasonReact.reducerComponent("Training");

let make = (children) => {
  ...component,
  initialState: _state => Loading,
  reducer: ((), _) => ReasonReact.NoUpdate,
  render: (self) =>
    <div className="row content">
      <div className="col m8 offset-m2">
        <TrainingHeader />
        <TrainingFooter />
      </div>
    </div>
};