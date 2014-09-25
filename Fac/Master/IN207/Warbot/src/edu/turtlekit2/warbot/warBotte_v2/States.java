package edu.turtlekit2.warbot.warBotte_v2;

/** War Botte v2 : States
 *  
 *  Cette énumération recense tous les états de tous les agents.
 *  
 * @author GAUTHIER silvère
 *
 */
public enum States {
	/*
	 * Etat d'initialisation des agents
	 */
	FIRST_LAP,
	
	/*
	 * Etats de WarBase
	 */
	HIGH_ENERGY, //création d'agent si assez d'énergie
	AVERAGE_ENERGY, //état par défaut
	ASK_DEFENSE, //demande d'un WarRocketLauncher en défense
	
	/*
	 * Etats de WarExplorer
	 */
	RETURN_BASE, //retour à la base pour la nourrir
	SEARCH_FOOD, //exploration de la carte en quête de nourriture
	SPY, //espionnage en quête de base ennemie
	
	/*
	 * Etats de WarRocketLauncher
	 */
	ATTACK, //exploration en quête de base ennemie
	DEFEND, //défense de la base
	DEPLOYMENT, //attaque coordonnée de la base adverse
	GO_DEPLOY //rejoindre le champs de bataille avant déploiement
}
