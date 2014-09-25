<?php
	header("Content-Type: text/plain");
 
	$passwd = (isset($_GET["passwd"])) ? $_GET["passwd"] : NULL;
	$passwdr = (isset($_GET["passwdr"])) ? $_GET["passwdr"] : NULL;
	$nom = (isset($_GET["nom"])) ? $_GET["nom"] : NULL;
	$prenom = (isset($_GET["prenom"])) ? $_GET["prenom"] : NULL;
	$mail = (isset($_GET["mail"])) ? $_GET["mail"] : NULL;
	
	try
	{
	    $bdd = new PDO('mysql:host=localhost;dbname=socialnet', 'root', 'root');
	}
	catch (Exception $e)
	{
		die('Erreur : ' . $e->getMessage());
	}
	
	$req = $bdd->query('SELECT mail_u FROM user') or die(print_r($bdd->errorInfo()));
	$existe=false;
	while ($datas = $req->fetch()){
		if ($_GET['mail']==$datas['mail_u']){
			$existe=true;
		}
	}
	
	if(!$nom){
		echo "fail_nom_";
	}
	else if(!$prenom){
		echo "fail_prenom_";
	}
	else if(!$mail){
		echo "fail_mail_";
	}
	else if($existe){
		echo "mail_exists_";
	}
	else if ($passwd && $passwdr) {
		if($passwd!=$passwdr){
			echo "diff_";
		}
	} 
	else {
		echo "fail_passwd_";
	}
	
?>