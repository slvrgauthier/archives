<?php
	header("Content-Type: text/plain");
 
	$mail = (isset($_POST["mail_connect"])) ? $_POST["mail_connect"] : NULL;
	$mdp = (isset($_POST["passwd_connect"])) ? $_POST["passwd_connect"] : NULL;

	try
	{
	    $bdd = new PDO('mysql:host=localhost;dbname=socialnet', 'root', 'root');
	}
	catch (Exception $e)
	{
		die('Erreur : ' . $e->getMessage());
	}
	
	if (empty($_POST['mail_connect'])){
		echo "miss_mail";
	}
	else if (empty($_POST['passwd_connect'])){
		echo "miss_mdp";
	}
	else{
		$req = $bdd->query('SELECT mail_u FROM user') or die(print_r($bdd->errorInfo()));
	
		$existe_mail=false;
		while ($datas = $req->fetch()){
			if ($_POST['mail_connect']==$datas['mail_u']){
				$existe_mail=true;
			}
		}
		
		if(!$existe_mail){
			echo 'fail_mail';
		}
		else{
			$existe_mdp=false;
			
			$req1=$bdd->query("SELECT mdp_u FROM user WHERE mail_u='".$mail."'") or die(print_r($bdd->errorInfo()));
			
			while ($datas1=$req1->fetch()){
				if($mdp!=$datas1['mdp_u']){
					$existe_mdp=true;
				}
			}
			if ($existe_mdp){
				echo 'fail_mdp';
			}
		} 
	}	
?>