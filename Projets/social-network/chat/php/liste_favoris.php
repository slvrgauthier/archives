<?php 
/* Fichier permettant l'affichage de la liste des favoris.
 */

// Connexion à la base de données
require_once("connexion_db.php"); 

$reponse = $bdd->prepare("SELECT * FROM chat_favoris,user WHERE id_contact=id_u AND id_utilisateur=? ORDER BY nom_u,prenom_u");
$reponse->execute(array($_POST['id_user']));

while ($donnees=$reponse->fetch()){
  echo '<div class="item" style="margin-left:10px" id="'.$donnees["id_favoris"].'"><input class="check_item_fav" type=checkbox name="invites" value="'.$donnees["id_contact"].'"/><small>'.$donnees["nom_u"].' '.$donnees["prenom_u"].' </small><img src="images/delete.gif" onclick="supprimer_fav('.$donnees['id_favoris'].')" /></div>';
}
echo '</div><br/>';