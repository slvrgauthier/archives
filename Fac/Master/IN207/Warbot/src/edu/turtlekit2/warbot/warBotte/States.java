package edu.turtlekit2.warbot.warBotte;

public enum States {
	FIRST_LAP,
	
	//Base
	LOW_ENERGY, // -> deprecated
	HIGH_ENERGY,
	AVERAGE_ENERGY,
	ASK_DEFENSE,
	ASK_SPY, // -> deprecated
	
	//Explorer
	RETURN_BASE,
	SEARCH_FOOD,
	SPY,
	
	//RocketLauncher
	ATTACK,
	DEFEND,
	DEPLOYMENT,
	GO_DEPLOY
}
