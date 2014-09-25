/*
Activation ou desactivation d'un DEL par la lumiere detecte par une autre DEL selon on seuil.
Ce code n'est fonctionnel que si la DEL emetrice n'influence pas la DEL qui capte l'intensite lumineuse.
Creer et imagine par Pascal Lafreniere (ATKProduductions Inc.) Vous êtes libres d'en faire ce que vous voulez.
*/

// Initialisation des variables

int recepteur = A0; // Pin de la DEL receptrice
int lumiere = 13; // Pin de la DEL emetrice

int maximum; // Reglage du maximum de sensibilite automatique
int minimum; // et du minimum.

int light; // Variable du niveaux de lumiere
int lightpourcent; // Variable de detection du niveau lumineux en pourcentage
int seuil = 20; // Seuil d'Activation en pourcentage

// Boucle d'initialisation

void setup() {

pinMode(recepteur, INPUT);
pinMode(lumiere, OUTPUT);

digitalWrite(lumiere, HIGH);

light = analogRead(recepteur); // Lecture du niveau lumineux
maximum = light + 1; // Minimum de la plage de lecture ( + 1 pour la stabilite )
minimum = light - 1; // Maximum de la plage de lecture ( - 1 pour la stabilite )

}

// Boucle principale

void loop() {

light = analogRead(recepteur); // Prise de mesure de l'intensite lumineuse

if (light > maximum) // Calibration automatique et en temp reel
maximum = light;
if (light < minimum)
minimum = light;

lightpourcent = map(light, minimum, maximum, 0, 100); // Mise a l'echelle du seuil minimum selon l'ajustement

if (lightpourcent > seuil) // Si la lumiere est plus grande que le seuil, eteindre la lumiere
digitalWrite(lumiere, HIGH);

if (lightpourcent < seuil) // Si la lumiere est plus faible que le seuil, allumer la lumiere
digitalWrite(lumiere, LOW);

}
