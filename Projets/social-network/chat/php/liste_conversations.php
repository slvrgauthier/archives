<?php
require_once("connexion_db.php");
if(isset($_POST['id_user']))
	$user=$_POST['id_user'];
$req = $bdd->prepare('select distinct id_conversation from chat_conversation where id_membre=?');
$req->execute(array($user));
while ($data = $req->fetch())
	{
		echo "<li class='conv' value='".$data['id_conversation']."'><small>Conversation ".$data['id_conversation']."</small> ".'<img src="images/delete.gif" onclick="supprimer_conv('.$data['id_conversation'].')" />'."</li>";
	}
