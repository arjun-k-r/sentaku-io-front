open Model;

let training = json =>
    Json.Decode.{
        id: field("id", int, json),
        title: field("id", string, json),
        description: field("id", string, json),
        degreeLevel: field("id", int, json),
        etcsNumber: field("id", int, json),
        diploma: field("id", string, json),
        admissionModalities: field("id", string, json),
        logo: field("id", string, json),
        link: field("id", string, json)
    };