<?php
	try
	{
	    $bdd = new PDO('mysql:host=localhost;dbname=socialnet', 'root', 'root');
	}
	catch (Exception $e)
	{
		die('Erreur : ' . $e->getMessage());
	}
	
	if(isset($_GET['id_mess_qu_on_a_like'])){
		$bdd->exec("UPDATE message SET aime=(aime+1) WHERE id_m=".$_GET['id_mess_qu_on_a_like']);
	}
	
	header("Location: ../index/index.php");	
?>