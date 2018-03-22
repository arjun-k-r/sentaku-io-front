
open Aliases;

let component = ReasonReact.statelessComponent("Login");

let make = (children) => {
  ...component,
  render: self =>
  <div className="col-md-6 col-md-offset-3 little-content">
  <h2>(str("Login"))</h2>
  <form name="form" > 
      <div className="user-name">
          <label htmlFor="username">(str("Username"))</label>
          <input _type="text" className="form-control" name="username"/>
      </div>
      <div className="passwd">
          <label htmlFor="password">(str("Password"))</label>
          <input _type="password" className="form-control" name="password" />
      </div>
      <div className="form-group">
          <button className="btn btn-primary">(str("Login"))</button>
          <a className="margin-left" href="/register"> (str("S'enregistrer")) </a>
      </div>
  </form>
</div>
};

/*

<!--onSubmit={this.handleSubmit}-->

*/