<?php
$invites = $_GET["invites"];
if (!empty($invites))
{
$user = $_GET["user"];
$invites = explode(",", $invites);
require_once("connexion_db.php");
$req = $bdd->query('select id_conversation from chat_conversation order by id_conversation desc limit 1');
	$idConversation=0;
	while ($data = $req->fetch())
	{
		$idConversation = $data['id_conversation']+1;
	}
$req = $bdd->prepare('INSERT INTO chat_conversation(id_conversation, id_membre) VALUES(?,?)');
$req->execute(array($idConversation, $user));
foreach ($invites as $Id)
{
	$req = $bdd->prepare('INSERT INTO chat_conversation(id_conversation, id_membre) VALUES(?,?)');
	$req->execute(array($idConversation, $Id));
}
echo $idConversation;
}
?>