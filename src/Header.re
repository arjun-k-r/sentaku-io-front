open Model;

let component = ReasonReact.statelessComponent("Header");

let make = _children => {
  ...component,
  render: _self =>
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
          </ul>
          <ul className="side-nav" id="mobile-demo">
            <li> <a href="#badges"> (str("FAQ")) </a> </li>
            <li> <a href="#collapsible"> (str("A propos")) </a> </li>
            <li> <a href="#mobile"> (str("Contact")) </a> </li>
          </ul>
        </div>
      </nav>
    </header>
};