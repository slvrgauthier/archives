function request() {
    var xhr = XMLHttpRequest();
    var xhr1= XMLHttpRequest();
     
    var nom = encodeURIComponent(document.getElementById("nom_inscr").value);
    var prenom = encodeURIComponent(document.getElementById("prenom_inscr").value);
    var mail = encodeURIComponent(document.getElementById("mail_inscr").value);
    var passwd = encodeURIComponent(document.getElementById("passwd_inscr").value);
    var passwdr = encodeURIComponent(document.getElementById("passwdr_inscr").value);
    
    xhr.onreadystatechange = function() {
    	$('#message_erreur').empty();
    	$('.form_insc').removeAttr('style');
        if (xhr.readyState == 4 && (xhr.status == 200 || xhr.status == 0)) {
        	if(xhr.responseText=="diff_"){
            	$('#message_erreur').append("Les mots de passe sont différents.");
            	$('#passwd_inscr').css("border","#df0c0c 2px solid");
            	$('#passwdr_inscr').css("border","#df0c0c 2px solid");
            }
            else if(xhr.responseText=="fail_passwd_"){
            	$('#message_erreur').append("Veuillez renseigner un mot de passe (et le répéter).");
            	//	border:#df0c0c 1px solid;
            	$('#passwd_inscr').css("border","#df0c0c 2px solid");
            	$('#passwdr_inscr').css("border","#df0c0c 2px solid");
            }
            else if(xhr.responseText=="fail_nom_"){
            	$('#message_erreur').append("Veuillez renseigner un nom.");
            	$('#nom_inscr').css("border","#df0c0c 2px solid");
            }
            else if(xhr.responseText=="fail_prenom_"){
            	$('#message_erreur').append("Veuillez renseigner un prenom.");
            	$('#prenom_inscr').css("border","#df0c0c 2px solid");
            }
            else if(xhr.responseText=="fail_mail_"){
            	$('#message_erreur').append("Veuillez renseigner une adresse mail.");
            	$('#mail_inscr').css("border","#df0c0c 2px solid");
            }
            else if(xhr.responseText=="mail_exists_"){
            	$('#message_erreur').append("Cette adresse mail existe déjà.");
            	$('#mail_inscr').css("border","#df0c0c 2px solid");
            }
            else{
            	xhr1.open("POST", "inscription_post.php", true);
            	xhr1.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
            	xhr1.send("nom_inscr="+nom+"&prenom_inscr="+prenom+"&mail_inscr="+mail+"&passwd_inscr="+passwd);
            	$('#message_succes').append("Vous êtes maintenant inscrit au site.");	
            }
        }
    };
     xhr1.onreadystatechange = function() {
      if (xhr1.readyState == 4 && (xhr1.status == 200 || xhr1.status == 0)) {
      		window.location='../index/index.php';
        }
     }
    	     
    xhr.open("GET", "inscr_tmp.php?nom="+nom+"&prenom="+prenom+"&mail="+mail+"&passwd="+passwd+"&passwdr="+passwdr , true);
    xhr.send(null);
}