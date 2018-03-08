/**
 * Here you will find all the model objects
 */
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
  tags: option(array(string))
};

/**
 * This type defines a training rating (note)
 */
type rating = {
  id: int,
  ownerId: string,
  rate: int, /* la note */
  comment: string,
  trainingId: int
};

let str = ReasonReact.stringToElement;