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

	$date = $_POST['an']."-".$_POST['mois']."-".$_POST['jour'];
	
	if(isset($_POST['nom_event_modif']) OR isset($_POST['lieu_event_modif']) OR isset($_POST['desc_event_modif'])){
	}
	else{
		$bdd->exec("INSERT INTO evenement(id_e, id_hote, nom, lieu, date, description, id_participant) SELECT max(id_e)+1,".$_SESSION['id'].",'".$_POST['nom_even']."','".$_POST['lieu_even']."','".$date."','".$_POST['desc_even']."',".$_SESSION['id']." FROM evenement");
	}
	header("Location: ../index/index.php");
?>