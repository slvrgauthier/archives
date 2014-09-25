<?php
/* Fichier servant à l'envoi des messages puis à la redirection vers chat.php
 */
 
// Connexion à la base de données
require_once("connexion_db.php");

if ($_POST['id_conversation'] != -1) {

  // Insertion du message à l'aide d'une requête préparée
  $req = $bdd->prepare('INSERT INTO chat_message (id_conversation, id_source, message, date_envoi) VALUES(?, ?, ?, NOW())');
  $req->execute(array($_POST['id_conversation'], $_POST['id_source'], $_POST['message']));
} 
// Redirection du visiteur vers la page du chat
header("Location: ../chat.php?id_conversation=".$_POST['id_conversation']);
?>