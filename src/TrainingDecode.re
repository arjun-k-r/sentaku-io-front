open Model;

type response = {
    training: training
};

let parseRating = json =>
    Json.Decode.{
        id: json |> field("id", int),
        ownerId: json |> field("ownerId", string),
        rate: json |> field("rate", int),
        comment: json |> field("comment", string),
        trainingId: json |> field("trainingId", int)
    };

let parseRatings = json => {
    json |> Json.Decode.array(parseRating)
         |> Array.map(rating =>  rating)
};

let parseNotesOverview = json => 
    Json.Decode.{
        average: json |> optional(field("average", float)),
        ratings: json |> optional(field("notes", parseRatings))
    };

let parseTr = json =>
    Json.Decode.{
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
        tags: json |> optional(field("tags", array(string))),
        ratingOverview: json |> field("noteOverview", parseNotesOverview)
    };

let training = json =>
    Json.Decode.{
        training: json |> field("training", parseTr)
    };