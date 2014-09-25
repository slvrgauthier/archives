<?php
	session_start();
	if (isset($_GET['id_con_a_ajouter_a_la_liste_d_amis_du_connecte'])){
		try
		{
		    $bdd = new PDO('mysql:host=localhost;dbname=socialnet', 'root', 'root');
		}
		catch (Exception $e)
		{
		        die('Erreur : ' . $e->getMessage());
		}
	
		
		$bdd->exec("INSERT INTO ami(id_u, id_ami) VALUE (".$_SESSION['id'].", ".$_GET['id_con_a_ajouter_a_la_liste_d_amis_du_connecte'].")");
		$bdd->exec("INSERT INTO ami(id_u, id_ami) VALUE (".$_GET['id_con_a_ajouter_a_la_liste_d_amis_du_connecte'].", ".$_SESSION['id'].")");
		
		
		//retour page d'ami
		header("Location: display_friend.php");
	}
?>