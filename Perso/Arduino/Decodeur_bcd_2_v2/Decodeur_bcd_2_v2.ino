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

bool afficheur = false; //variable pour le choix de l'afficheur
long temps = 0;
long tps = 0;
int valeur = 0;

void loop()
{
	//gestion du rafraichissement
	//si ça fait plus de 10 ms qu'on affiche, on change de 7 segments (alternance unité <-> dizaine)
	if((millis() - temps) > 10)
	{
		//on inverse la valeur de "afficheur" pour changer d'afficheur (unité ou dizaine)
		afficheur = !afficheur;
		//on affiche la valeur sur l'afficheur
		//afficheur : true->dizaines, false->unités
		afficher_nombre(valeur, afficheur);
		temps = millis(); //on met à jour le temps
                if((millis()-tps) > 500) {
                  valeur = valeur + 1;
                  tps = millis();
                  if(valeur > 99) {
                    valeur = 0;
                  }
                }
	}
	
	//ici, on peut traiter les évènements (bouton...)
}

//fonction permettant d'afficher un nombre
//elle affiche soit les dizaines soit les unités
void afficher_nombre(char nombre, bool afficheur)
{
	char unite = 0, dizaine = 0;
	if(nombre > 9)
		dizaine = nombre / 10; //on recupere les dizaines
	unite = nombre - (dizaine*10); //on recupere les unités
	
	//si "
	if(afficheur)
	{
		//on affiche les dizaines
		digitalWrite(alim_unite, LOW);
		afficher(dizaine);
		digitalWrite(alim_dizaine, HIGH);
	}
	else // égal à : else if(!afficheur)
	{
		//on affiche les unités
		digitalWrite(alim_dizaine, LOW);
		afficher(unite);
		digitalWrite(alim_unite, HIGH);
	}
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
