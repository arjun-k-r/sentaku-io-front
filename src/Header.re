open Model;
open RoleDecode;

let component = ReasonReact.statelessComponent("Header");

let make = (~userInfos: option(user), ~connection: connectionState, _children) => {
  ...component,
  render: _self =>{
    <header>
      <nav>
        <div className="nav-wrapper">
          <a href="#" className="brand-logo"> (str("Sentaku.io")) </a>
          (
            ReasonReact.cloneElement(
              <a href="#" className="button-collapse">
                <i className="material-icons"> (str("menu")) </i>
              </a>,
              ~props={"data-activates": "mobile-demo"},
              [||]
            )
          )
          <ul className="right hide-on-med-and-down">
            <li> <a href="#badges"> (str("FAQ")) </a> </li>
            <li> <a href="#collapsible"> (str("A propos")) </a> </li>
            <li> <a href="#mobile"> (str("Contact")) </a> </li>
            (
              switch connection {
              | Logged => <li> (str(switch (userInfos) {
                  | Some(user) => {
                    user.email ++ "(" ++ roleToString(user.role) ++ ")";
                  }
                  | None => "Erreur de login"
                })) </li>
              | NotLogged => {
                <span> </span>
              }
              }
            )
            (
              switch connection {
              | Logged => <li> <a href="/disconnect"> (str("Se deconnecter")) </a> </li>
              | NotLogged => <li> <a href="/login"> (str("Se connecter")) </a> </li>
              }
            )
            
          </ul>
          <ul className="side-nav" id="mobile-demo">
            <li> <a href="#badges"> (str("FAQ")) </a> </li>
            <li> <a href="#collapsible"> (str("A propos")) </a> </li>
            <li> <a href="#mobile"> (str("Contact")) </a> </li>
          </ul>
        </div>
      </nav>
    </header>
            }
};