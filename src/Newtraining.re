/**
 * This component allows to create a new training
 *
 * US_01
 */
open ServicesMocks;

open Model;

type state = {training : training};

type action =
  | CreateTraining(training);


let component = ReasonReact.reducerComponent("NewTraining");

let valueFromEvent = (evt) : string => (
  evt
  |> ReactEventRe.Form.target
  |> ReactDOMRe.domElementToObj
)##value;


let make = children => {...component,
    initialState: () => {
        training: { 
            id:1,
            title: "YOLO",
            description: "swag",
            degreeLevel: 1,
            etcsNumber: 1,
            diploma: "string",
            admissionModalities: "string",
            logo: "string",
            link: "string"}
      },
      reducer: (action, {training}) =>
      switch action{
      | CreateTraining(training) => ReasonReact.Update() 
      },
       render: ({state : {training}, reduce}) => {
           <div className="trainings">
           (str("test"))
        </div>
       }
  };