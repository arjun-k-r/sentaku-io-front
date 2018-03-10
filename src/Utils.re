open Model;
/**
 * Shows the value of an optional
 */
let optStr = opt =>
    switch opt {
    | Some(value) => str(value)
    | None => str("Non renseigné")
    };

let optIntStr= opt=>
switch opt {
    | Some(value) => string_of_int(value)
    | None => "Non renseigné"
};
let opt = opt =>
    switch opt {
    | Some(value) => value
    | None => "Non renseigné"
};
