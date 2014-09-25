package test;

import tp2.Etudiant;

public class tp2{
  public static void main(String[] args){
    DateFormat df=DateFormat.getDateInstance(DateFormat.LONG);
    Date d=df.parse("12 mars 2000");
    Etudiant e=new Etudiant("La Petite Poubelle","Pouby",d,"Now","USA",8,10,9);
    e.ligneResultats();
    System.out.println(e.toString());
  }
}
