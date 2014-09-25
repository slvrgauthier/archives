<?php
/* Fichier permettant le rafraîchissement des messages de la base de données.
 */

// Connexion à la base de données
require_once("connexion_db.php");

if(isset($_POST['id_conversation']))
	$id_conversation=$_POST['id_conversation'];

// Récupération des messages
$req = $bdd->prepare('SELECT nom_u,prenom_u,DATE_FORMAT(date_envoi, "%d/%m/%Y à %Hh%i") AS date_envoi,message FROM chat_message,user WHERE id_source=id_u AND id_conversation=? ORDER BY id_message');
$req->execute(array($id_conversation));
 
// Affichage de chaque message (toutes les données sont protégées par htmlspecialchars)
while ($data = $req->fetch())
{
    echo '<p><i><strong class="msg_left" >'.htmlspecialchars($data['nom_u'], ENT_QUOTES|ENT_SUBSTITUTE).' '.htmlspecialchars($data['prenom_u'], ENT_QUOTES|ENT_SUBSTITUTE).'</strong> a dit :<small class="msg_right" >Le '.htmlspecialchars($data['date_envoi'], ENT_QUOTES|ENT_SUBSTITUTE).'</i></small><br/><dd>'.htmlspecialchars($data['message'], ENT_QUOTES|ENT_SUBSTITUTE).'</dd></p>';
}

$req->closeCursor();
?>