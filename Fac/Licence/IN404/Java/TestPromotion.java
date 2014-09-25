package test;

import tp2.Promotion;
import tp2.Etudiant;

public class TestPromotion{
  public static void main(String[] args){
    Promotion p1=new Promotion();
    Promotion p2=new Promotion(1998);
    System.out.println(p2.getAnnee());
    
  }
}
