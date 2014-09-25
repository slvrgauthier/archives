<?php
/* Fichier permettant l'affichage des membres de la conversation.
 */

// Connexion à la base de données
require_once("connexion_db.php");
 
if(isset($_POST['id_conversation']))
  $id_conversation=$_POST['id_conversation'];
if($id_conversation!=-1) {
  // Récupération des membres
  $reponse = $bdd->prepare('SELECT * FROM chat_conversation,user WHERE id_membre=id_u AND id_conversation=? ORDER BY nom_u,prenom_u');
  $reponse->execute(array($id_conversation));
 
  // Affichage de chaque membre (toutes les données sont protégées par htmlspecialchars)
  echo '<small>';
  $donnees = $reponse->fetch();
  echo '<strong>'.htmlspecialchars($donnees['nom_u'], ENT_QUOTES|ENT_SUBSTITUTE).'</strong> '.htmlspecialchars($donnees['prenom_u'], ENT_QUOTES|ENT_SUBSTITUTE);

  while ($donnees = $reponse->fetch()) {
    echo ' - <strong>'.htmlspecialchars($donnees['nom_u'], ENT_QUOTES|ENT_SUBSTITUTE).'</strong> '.htmlspecialchars($donnees['prenom_u'], ENT_QUOTES|ENT_SUBSTITUTE);
  }
  echo ' </small>';

  $reponse->closeCursor();
}
?>