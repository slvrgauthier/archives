var collection;
var liste;

function chargement(){
  if(connexion.readyState == 4) {
    collection = eval(connexion.responseText);
    liste = document.createElement("select"); //création de la liste
    liste.setAttribute("onChange", "chargementJSON(collection[liste.selectedIndex-1].lien)");
    
    document.body.appendChild(liste);
    var item;
    item = document.createElement("option");
    item.appendChild(document.createTextNode("Choisissez..."));
    liste.appendChild(item);
    for(var i=0;i<collection.length;i++) {
      item = document.createElement("option");
      item.appendChild(document.createTextNode(collection[i].nom));
      liste.appendChild(item);
    }
  }
}

function chargementJSON(url) {
  if(window.XMLHttpRequest) {
    connexion = new XMLHttpRequest();
    
    if(connexion != 0) {
      connexion.onload = null;
      connexion.open("GET", url, true);
      
      connexion.onreadystatechange = chargement;
      
      connexion.send(null); //envoi de la requete
    }
  }
  else {
    alert("La connexion n'a pas pu etre initiee !");
  }
}

chargementJSON("chanteurs.json"); //point d'entrée