open Model;

let parseRole: Js.Json.t => roleInfo =
  json =>
    Json.Decode.{
      email: json |> field("email", string),
      role: json |> field("role", string),
    };

    let parseRoles = json => {
      Js.log(json);
        json |> Json.Decode.array(parseRole) |> Array.map(role => role);
    };

let getRole: roleInfo => role =
  json =>
    switch (json.role) {
    | "admin" => Admin
    | "evaluator" => Evaluator
    | "staff" => Staff
    | _ => Prospect
    };

let roleToString = role =>
  switch (role) {
  | Admin => "Administrateur"
  | Evaluator => "Evaluateur"
  | Staff => "Personnel"
  | _ => "Prospect"
  };