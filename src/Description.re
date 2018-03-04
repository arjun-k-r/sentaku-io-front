open ServicesMocks;

open Model;

let component = ReasonReact.statelessComponent("Description");

let make = children => {
    ...component,
    render: (self) => 
        <div id="test-swipe-1" className="col s12 active">
            <h5>(str("Les objectifs de la formation MIAGE"))</h5>
            <p>
                (str("MIAGE signifie Méthodes Informatiques Appliquées à la Gestion des Entreprises. Centrée sur l’ingénierie des systèmes d’information,
                la MIAGE a pour objectif de former des informaticiens ayant des compétences en gestion des organisations, gestion
                de projets, systèmes d'information et communication d'entreprise. La formation MIAGE apporte des bases théoriques
                et des compétences technologiques tout en assurant un contact permanent avec le monde de l’entreprise. Cela est possible
                grâce à l’intervention de professionnels qui assurent certains enseignements, aux stages ou encore aux activités
                proposées, telles que la journée de simulation d’entretiens ou encore les visites d’entreprises et conférences données
                par des professionnels."))
            </p>
            <h5>
                (str("Accéder au Master MIAGE"))
            </h5>
            <p>
                (str("Le Master mention MIAGE est accessible par les étudiants issus aussi bien de la licence MIAGE que de la licence Informatique
                ou de toute autre formation équivalente. Le parcours MIAGE de la licence est bien entendu le plus adapté pour l’accès
                au Master (la MIAGE étant une formation construite sur 3 ans) mais n’est en aucun cas un prérequis. L’entrée en deuxième
                année de master n’est possible que pour des étudiants issus d’une première année de Master MIAGE ou d’une formation
                équivalente basée sur l’informatique, les systèmes d’information et la gestion des organisations."))
            </p>
            <h5>
                (str("Organisation du Master MIAGE"))
            </h5>
            <p>
                (str("Le master mention MIAGE offre deux modalités d'enseignement :"))
                <br />(str(" - Réaliser une formation à temps plein à l’université (en formation initiale), dans ce cas les deux ans s’organisent
                sur 4 semestres."))
                <br />(str("- Etre présent deux jours par semaine à l’université et trois jours en entreprise (en formation en alternance),
                dans ce cas les deux ans s’organisent sur 6 trimestres."))

            </p>
        </div>
};