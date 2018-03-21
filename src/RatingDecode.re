open Model;

type response = {
    rating: rating
};

let parseRating = json =>
    Json.Decode.{
        id: json |> field("id", string),
        ownerId: json |> field("ownerId", string),
        rate: json |> field("note", int),
        comment: json |> field("comment", string),
        trainingId: json |> field("trainingId", string)
    };

let rating = json =>
    Json.Decode.{
        rating: json |> field("rating", parseRating)
    }