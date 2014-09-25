<?php
	try
	{
	    $bdd = new PDO('mysql:host=localhost;dbname=socialnet', 'root', 'root');
	}
	catch (Exception $e)
	{
		die('Erreur : ' . $e->getMessage());
	}	
	
	//nos evenements
	$affiche_nous=false;
	
	$req = $bdd->query("SELECT * FROM evenement, profil WHERE evenement.id_hote=profil.id_user AND id_hote=".$_SESSION['id']." ORDER BY evenement.date") or die (print_r($bdd->errorInfo()));
		
	echo "Vos événements <br/>";
	while ($datas=$req->fetch()){
		if(!$affiche_nous){
			$affiche_nous=true;
			echo "<a href='../menu/profil.php'><img src='../".$datas['photo_path']."' alt='Erreur d'affichage' title='Votre profil' class='img_event' width='30px' height='38px' /></a> <a id='id_event_display' href='../event/event_id.php?id_event=".$datas['id_e']."'>".$datas['nom']."</a> ";
		}
	}
	
	//Evenements des amis
	$affiche=false;
	$req1=$bdd->query("SELECT evenement.nom as nomE, id_e,photo_path,friend.id_u as idA,friend.nom_u as nomA,friend.prenom_u as prenomA, friend.id_u as idA FROM user as friend, user as utilisateur, ami, profil, evenement WHERE friend.id_u=ami.id_ami AND utilisateur.id_u=ami.id_u AND evenement.id_hote=friend.id_u AND utilisateur.id_u=".$_SESSION['id']." AND profil.id_user=friend.id_u ORDER BY evenement.date") or die (print_r($bdd->errorInfo()));
	
	echo "<br/><br/> Evénements de vos amis <br/>";
	while($datas1=$req1->fetch()){
		if(!$affiche){
			$affiche=true;
			echo "<a href='../profil/friend_profil.php?id_profil=".$datas1['idA']."'><img src='../".$datas1['photo_path']."' alt='Erreur d'affichage' title='Profil de ".$datas1['nomA']." ".$datas1['prenomA']."' class='img_event' width='30px' height='38px' /></a> <a id='id_event_display' href='../event/event_id.php?id_event=".$datas1['id_e']."'>".$datas1['nomE']."</a> ";
		}
	}
?>
