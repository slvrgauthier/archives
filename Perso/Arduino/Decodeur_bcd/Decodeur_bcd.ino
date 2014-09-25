const int bit_C = 2;
const int bit_B = 3;
const int bit_D = 4;
const int bit_A = 5;

void setup()
{
   //on met les broches en sorties
   pinMode(bit_A, OUTPUT);
   pinMode(bit_B, OUTPUT);
   pinMode(bit_C, OUTPUT);
   pinMode(bit_D, OUTPUT);

   //on commence par écrire le chiffre 0, donc toutes les sorites à l'état bas
   digitalWrite(bit_A, LOW);
   digitalWrite(bit_B, LOW);
   digitalWrite(bit_C, LOW);
   digitalWrite(bit_D, LOW);
}
//fonction écrivant sur un seul afficheur
void afficher(char chiffre)
{
   //on met à zéro tout les segments
   digitalWrite(bit_A, LOW);
   digitalWrite(bit_B, LOW);
   digitalWrite(bit_C, LOW);
   digitalWrite(bit_D, LOW);

   //On allume les bits nécessaires
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
void loop()
{
    char i=0; //variable "compteur"
    for(i=0; i<10; i++)
    {
        afficher(i); //on appel la fonction d'affichage
        delay(1000); //on attend 1 seconde
    }
}
