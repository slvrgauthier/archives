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
	
	$req = $bdd->query('SELECT mail_u, mdp_u, nom_u, prenom_u, id_u FROM user') or die(print_r($bdd->errorInfo()));
	$existe_mail=false;
	$existe_mdp=false;
	while ($datas = $req->fetch()){
		if (!(empty($_POST['mail_connect'])) AND !(empty($_POST['passwd_connect']))){
			if($_POST['mail_connect']==$datas['mail_u'] AND $_POST['passwd_connect']==$datas['mdp_u']){
				$_SESSION['nom']=$datas['nom_u'];
				$_SESSION['prenom']=$datas['prenom_u'];
				$_SESSION['id']=$datas['id_u'];
				$_SESSION['mail']=$datas['mail_u'];
				$existe_mail=true;
				$existe_mdp=true;
			}
		}
	}
	
	if(!$existe_mdp){
		echo "Mot de passe incorrect pour ".$_POST['mail_connect'].".";
		?><br/><br/><a href="../index/index.php"> Retour à l'accueil </a>
		<?php			
	}
?>