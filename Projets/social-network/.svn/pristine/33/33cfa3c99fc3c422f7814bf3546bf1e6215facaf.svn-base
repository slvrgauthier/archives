<?php
/* Fichier permettant la connexion à la base de données.
 */

try {
    $bdd = new PDO('mysql:host=localhost;dbname=socialnet', 'root', 'root', array(PDO::MYSQL_ATTR_INIT_COMMAND => 'SET NAMES utf8')); //les paramètres sont certainement à modifier pour le serveur
}
catch(Exception $e) {
        die('Erreur : '.$e->getMessage());
}
?>