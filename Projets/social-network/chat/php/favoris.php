<?php 
/* Fichier permettant l'affichage de la liste des favoris.
 */
 
// Connexion à la base de données
require_once("connexion_db.php");

echo '<span id="liste_favoris" class="trigger"><img src="images/list_close.png" class="img_list" /><img src="images/list_open.png" class="img_list" hidden /> Favoris</span><input class="check_con" id="check_fav" type=checkbox /> <div id="select_fav">'; 

echo '</div><br/>';