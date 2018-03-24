open Model;

type response = { user };

let parseUser = json =>
  Json.Decode.{
    id: json |> field("uid", string),
    email: json |> field("email", string),
    token: json |> field("refreshToken", string),
    role: json |> field("role", string)
  };