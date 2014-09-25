<?php
/* Fichier permettant la suppression des favoris ou conversations de la base de données.
 */

// Connexion à la base de données
require_once("connexion_db.php");

if($_GET['type']=="favoris") {
  $req = $bdd->prepare('DELETE FROM chat_favoris WHERE id_favoris=?');
  $req->execute(array($_GET['id']));
}
else if($_GET['type']=="conversation") {
  $req = $bdd->prepare('DELETE FROM chat_conversation WHERE id_conversation=? AND id_membre=?');
  $req->execute(array($_GET['id'], $_GET['user']));
  
  //Supression des messages si conversation sans membre
  $count = $bdd->prepare('SELECT COUNT(*) FROM chat_conversation WHERE id_conversation=?');
  $count->execute(array($_GET['id']));
  $nbmembre = $count->fetchColumn();
  if($nbmembre < 1) {
    $ssreq = $bdd->prepare('DELETE FROM chat_message WHERE id_conversation=?');
    $ssreq->execute(array($_GET['id']));
    $ssreq->closeCursor();
  }
  $count->closeCursor();
}

$req->closeCursor();
?>