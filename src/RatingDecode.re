open Model;

type response = {
    rating: rating
};

let parseRating = json =>
    Json.Decode.{
        id: json |> field("id", int),
        ownerId: json |> field("ownerId", string),
        rate: json |> field("rate", int),
        comment: json |> field("comment", string),
        trainingId: json |> field("trainingId", string)
    };

let rating = json =>
    Json.Decode.{
        rating: json |> field("rating", parseRating)
    }