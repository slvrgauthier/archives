<?php
/* Fichier permettant l'affichage des favoris.
 */

$invites = $_GET["invites"];
if (!empty($invites)) {
  $user = $_GET["user"];
  $invites = explode(",", $invites);
  require_once("connexion_db.php");
  foreach ($invites as $Id) {
    //Ajouter seulement s'il n'existe pas
    $count = $bdd->prepare('SELECT COUNT(*) FROM chat_favoris WHERE id_utilisateur=? AND id_contact=?');
    $count->execute(array($user, $Id));
    $nbmembre = $count->fetchColumn();
    $count->closeCursor();
    if($nbmembre == 0) {
      $req = $bdd->prepare('INSERT INTO chat_favoris(id_utilisateur, id_contact) VALUES(?,?)');
      $req->execute(array($user, $Id));
      $req->closeCursor();
    }
  }
}
?>