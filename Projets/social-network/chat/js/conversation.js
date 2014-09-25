/*
		Fonction g�n�rant une requ�te javascript Asynchrone pour rajouter une nouvelle conversation dans le base de donn�es
*/
function creer_conversation(user)
{
var invites=[];
$("input:checked[name=invites]").each(function(){
	invites.push($(this).val());
});

// alert(JSON.stringify(invites));

var xhr_object = null; 
	     
	// Cas des navigateurs de type Netscape (Firefore, Conqueror, etc.)
	if(window.XMLHttpRequest) 
	   	xhr_object = new XMLHttpRequest(); 
	// Cas du navigateur Internet Explorer
	else if(window.ActiveXObject)
	  	 xhr_object = new ActiveXObject("Microsoft.XMLHTTP");
	// Cas des navigateurs ne comprenant pas cette technologie (anciens navigateurs)
	else { 
			// XMLHttpRequest non support� par le navigateur 
	 		alert("Votre navigateur ne supporte pas les objets XMLHTTPRequest..."); 
    	return; 
	} 
	 
	xhr_object.open("GET", "php/creer_conversation.php?user="+user+"&invites="+invites, true);

	xhr_object.onreadystatechange = function() { 
			// Etat : requ�te termin�e, r�ponse r�cup�r�e
	  	if(xhr_object.readyState == 4) {
				refresh(xhr_object.responseText);
		 	}
			return xhr_object.readyState;
	} 
	xhr_object.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
	
	//  Envoi de la requ�te
	xhr_object.send(null);
}

/* Fonction permettant la création de favoris dans la base de données
 */
function ajouter_favoris(user) {
  var invites=[];
  $("input:checked[name=invites]").each(function(){
    invites.push($(this).val());
  });

  var xhr_object = null; 
     
  if(window.XMLHttpRequest) 
    xhr_object = new XMLHttpRequest();
  else if(window.ActiveXObject)
    xhr_object = new ActiveXObject("Microsoft.XMLHTTP");
  else { 
  alert("Votre navigateur ne supporte pas les objets XMLHTTPRequest..."); 
  return; 
  } 

  xhr_object.open("GET", "php/ajouter_favoris.php?user="+user+"&invites="+invites, true);

  xhr_object.onreadystatechange = function() { 
    if(xhr_object.readyState == 4) {
      refresh_fav();
    }
    return xhr_object.readyState;
  } 
  xhr_object.setRequestHeader("Content-type", "application/x-www-form-urlencoded");

  xhr_object.send(null);
}

/* Fonction permettant la suppression de favoris de la base de données
 */
function supprimer_fav(id) {
  var user = document.getElementById('form_source').value;
  var xhr_object = null; 
     
  if(window.XMLHttpRequest) 
    xhr_object = new XMLHttpRequest(); 
  else if(window.ActiveXObject)
    xhr_object = new ActiveXObject("Microsoft.XMLHTTP");
  else { 
  alert("Votre navigateur ne supporte pas les objets XMLHTTPRequest..."); 
  return; 
  } 

  xhr_object.open("GET", "php/delete.php?type=favoris&id="+id+"&user="+user, true);

  xhr_object.onreadystatechange = function() { 
    if(xhr_object.readyState == 4) {
      refresh_fav();
    }
    return xhr_object.readyState;
  } 
  xhr_object.setRequestHeader("Content-type", "application/x-www-form-urlencoded");

  xhr_object.send(null);
}

/* Fonction permettant la suppression de conversation de la base de données
 */
function supprimer_conv(id) {
  var user = document.getElementById('form_source').value;
  var xhr_object = null; 
     
  if(window.XMLHttpRequest) 
    xhr_object = new XMLHttpRequest(); 
  else if(window.ActiveXObject)
    xhr_object = new ActiveXObject("Microsoft.XMLHTTP");
  else { 
  alert("Votre navigateur ne supporte pas les objets XMLHTTPRequest..."); 
  return; 
  } 

  xhr_object.open("GET", "php/delete.php?type=conversation&id="+id+"&user="+user, true);

  xhr_object.onreadystatechange = function() { 
    if(xhr_object.readyState == 4) {
      refresh(-1);
    }
    return xhr_object.readyState;
  } 
  xhr_object.setRequestHeader("Content-type", "application/x-www-form-urlencoded");

  xhr_object.send(null);
}