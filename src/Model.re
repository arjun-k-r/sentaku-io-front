/**
 * Here you will find all the model objects
 */

/**
 * This type defines a training rating (note)
 */
type rating = {
  id: string,
  ownerId: string,
  rate: int, /* la note */
  comment: string,
  trainingId: string
};

type ratingOverview = {
  average: option(float),
  ratings: option(array(rating))
};
/*
 * This following type defines a training
 */
type training = {
  id: string,
  title: string,
  description: string,
  degreeLevel: int,
  etcsNumber: option(int),
  diploma: option(string),
  admissionModalities: string,
  logo: string,
  location: string,
  link: string,
  tags: option(array(string)),
  ratingOverview: ratingOverview
};

/**
 * When logged in
 */
type user = {
  id: string,
  email: string,
  token: string
};

/**
 * To login
 */
type credential = {
  email: string,
  password: string
};

let str = ReasonReact.stringToElement;

let apiUrl = "https://sentaku-api-prod.herokuapp.com/api/v1/";