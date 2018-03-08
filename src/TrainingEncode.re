open Model;

type tr = {
    training: training
};

let parseTr = json =>
    Json.Encode.{
        id: json |> field("id", string),
        title: json |> field("title", string),
        description: json |> field("description", string),
        degreeLevel: json |> field("degreeLevel", int),
        etcsNumber: json |> optional(field("ETCSNumber", int)),
        diploma: json |> optional(field("diploma", string)),
        admissionModalities: json |> field("admissionModalities", string),
        logo: json |> field("logo", string),
        location: json |> field("location", string),
        link: json |> field("link", string),
        tags: json |> optional(field("tags", array(string)))
    };

let training = json =>
    Json.Encode.{
        training: json |> field("training", parseTr)
    };

