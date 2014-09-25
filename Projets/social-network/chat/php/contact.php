<?php 
/* 
	* contact.php 
	*
	* Fichier servant a afficher la liste des utilisateurs dans la bdd
	* Inclus dans chat.php
*/

	//CONNEXION A LA BDD
	require_once("connexion_db.php");
	
	/*
		***************************************************************************************************
		**************************	  AFFICHAGE LISTE CONTACTS ENSEIGNANTS      ***************************	
		***************************************************************************************************
	*/	echo '<span id="liste_amis" class="trigger"><img src="images/list_close.png" class="img_list" /><img src="images/list_open.png" class="img_list" hidden /> Amis</span><input class="check_con" id="check_ami" type=checkbox /> <div id="select_ami">'; 
	
	$req_ami = $bdd->prepare("SELECT * FROM ami a,user u WHERE a.id_ami=u.id_u AND a.id_u=? ORDER BY nom_u,prenom_u");
	$req_ami->execute(array($user));
	
	while ($datas_ami=$req_ami->fetch()){
		echo '<div class="item" style="margin-left:10px" name="invites" id="'.$datas_ami["id_ami"].'"><small>'.$datas_ami["nom_u"].' '.$datas_ami["prenom_u"].'</small><input class="check_item_ami" type=checkbox name="invites" value="'.$datas_ami["id_u"].'"/></div>';
	}
	echo '</div><br/>';
?>