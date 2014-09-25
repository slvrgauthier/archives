//définition des broches du décodeur 7 segments (vous pouvez changer les numéros si bon vous semble)
const int bit_C = 2;
const int bit_B = 3;
const int bit_D = 4;
const int bit_A = 5;

//définitions des broches des transistors pour chaque afficheur (dizaines et unités)
const int alim_dizaine = 6;
const int alim_unite = 7;

void setup()
{
	//Les broches sont toutes des sorties
	pinMode(bit_A, OUTPUT);
	pinMode(bit_B, OUTPUT);
	pinMode(bit_C, OUTPUT);
	pinMode(bit_D, OUTPUT);
	pinMode(alim_dizaine, OUTPUT);
	pinMode(alim_unite, OUTPUT);
	
	//Les broches sont toutes mises à l'état bas
	digitalWrite(bit_A, LOW);
	digitalWrite(bit_B, LOW);
	digitalWrite(bit_C, LOW);
	digitalWrite(bit_D, LOW);
	digitalWrite(alim_dizaine, LOW);
	digitalWrite(alim_unite, LOW);
}


//fonction écrivant sur un seul afficheur
//on utilise le même principe que vu plus haut
void afficher(char chiffre)
{
	digitalWrite(bit_A, LOW);
	digitalWrite(bit_B, LOW);
	digitalWrite(bit_C, LOW);
	digitalWrite(bit_D, LOW);
	if(chiffre >= 8)
	{
		digitalWrite(bit_D, HIGH);
		chiffre = chiffre - 8;
	}
	if(chiffre >= 4)
	{
		digitalWrite(bit_C, HIGH);
		chiffre = chiffre - 4;
	}
	if(chiffre >= 2)
	{
		digitalWrite(bit_B, HIGH);
		chiffre = chiffre - 2;
	}
	if(chiffre >= 1)
	{
		digitalWrite(bit_A, HIGH);
		chiffre = chiffre - 1;
	}
}

//le code est terminé
