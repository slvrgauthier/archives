// Déclaration et remplissage du tableau...
// ...représentant les broches des LEDs
const int leds[10] = {2,3,4,5,6,7,8,9,10,11};
const int potar = 0; //le potentiomètre sera branché sur la broche analogique 0
int tension; //variable stockant la tension mesurée

void setup()
{
	int i = 0;
	for(i=0; i<10; i++)
	{
		pinMode(leds[i], OUTPUT); //déclaration de la broche en sortie
		digitalWrite(leds[i], HIGH); //mise à l'état haut
	}
}

void loop()
{
    afficher(analogRead(potar)); //la même chose qu'avant même en une seule ligne !
}

void afficher(int valeur)
{
	int i;
	for(i=0; i<10; i++)
	{
		if(valeur >= (i*100))
			digitalWrite(leds[i], LOW); //on allume la LED
		else
			digitalWrite(leds[i], HIGH); //ou on éteint la LED
	}
}
