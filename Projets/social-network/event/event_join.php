<?php 
	session_start();
	try
	{
	    $bdd = new PDO('mysql:host=localhost;dbname=socialnet', 'root', 'root');
	}
	catch (Exception $e)
	{
		die('Erreur : ' . $e->getMessage());
	}
	
	$bdd->exec("INSERT INTO evenement(id_e, id_hote, nom, lieu, date, description, id_participant) VALUES (".$_GET['id_e'].",".$_GET['id_hote'].",'".$_GET['nom_e']."','".$_GET['lieu_e']."','".$_GET['date_e']."','".$_GET['desc_e']."',".$_SESSION['id'].")");
		
	header("Location: ../index/index.php");
?>