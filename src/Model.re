/**
 * Here you will find all the model objects
 */
/*
 * This following type defines a training
 */
type training = {
  id: int,
  title: string,
  description: string,
  degreeLevel: int,
  etcsNumber: int,
  diploma: string,
  admissionModalities: string,
  logo: string,
  link: string
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