<?php
	session_start();	
	if (empty($_POST['nom_inscr']) OR empty($_POST['prenom_inscr']) OR empty($_POST['mail_inscr']) OR empty($_POST['passwd_inscr'])){
		header("Location: ../member/inscription.php");
	}
	else{
		try
		{
		    $bdd = new PDO('mysql:host=localhost;dbname=socialnet', 'root', 'root');
		}
		catch (Exception $e)
		{
		        die('Erreur : ' . $e->getMessage());
		}
		
		$req = $bdd->query('SELECT mail_u FROM user') or die(print_r($bdd->errorInfo()));
	
		$bdd->exec("INSERT INTO user(nom_u, prenom_u, mail_u, mdp_u, date_u) VALUES('".$_POST['nom_inscr']."','".$_POST['prenom_inscr']."', '".$_POST['mail_inscr']."','".$_POST['passwd_inscr']."',NOW())");
		//cree une entree dans la table profil, correspondant a l'utilisateur cree precedemment
		$bdd->exec("INSERT INTO profil(photo_path, date_naissance) VALUES('medias/upload_img/default.jpg',NOW())");
		
		//principe de login
		$req1=$bdd->query('SELECT id_u FROM user WHERE mail_u=\''.$_POST['mail_inscr'].'\'') or die(print_r($bdd->errorInfo()));
		while($datas1=$req1->fetch()){
			$id_inscr=$datas1['id_u'];
		}
		
		$_SESSION['nom']=$_POST['nom_inscr'];
		$_SESSION['prenom']=$_POST['prenom_inscr'];
		$_SESSION['id']=$id_inscr;
		$_SESSION['mail']=$_POST['mail_inscr'];
	}
?>