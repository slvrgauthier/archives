package tp2;

import java.util.*;
import java.text.*;

public class Etudiant
{
  private String nom;
  private String prenom;
  private int age;
  private Date naissance;
  private String codeIns;
  private String codePays;
  private float note1;
  private float note2;
  private float note3;

    public Etudiant(String N,String p,Date n,String cI,String cP,float n1,float n2,float n3){
      this.nom=N; this.prenom=p; this.age=age(); this.naissance=n;
      this.codeIns=cI; this.codePays=cP; this.note1=n1; this.note2=n2; this.note3=n3;
    }

    public String getNom(){return this.nom;}
    public String getPrenom(){return this.prenom;}
    public int getAge(){return this.age;}
    public Date getNaissance(){return this.naissance;}
    public String getCodeIns(){return this.codeIns;}
    public String getCodePays(){return this.codePays;}
    public float getNote1(){return this.note1;}
    public float getNote2(){return this.note2;}
    public float getNote3(){return this.note3;}

    public void setNom(String n){this.nom=n;}
    public void setPrenom(String p){this.prenom=p;}
    public void setNaissance(Date n){this.naissance=n; this.age=age();}
    public void setCodeIns(String cI){this.codeIns=cI;}
    public void setCodePays(String cP){this.codePays=cP;}
    public void setNote1(float n1){this.note1=n1;}
    public void setNote2(float n2){this.note2=n2;}
    public void setNote3(float n3){this.note3=n3;}

    public int age(){
      Calendar cal=new GregorianCalendar();
      cal.setTime(new Date());
      int anneeActuelle=cal.get(Calendar.YEAR);
      cal.setTime(this.naissance);
      int annee=cal.get(Calendar.YEAR);
      return anneeActuelle-annee;
    }
    public float moyenne(){return (this.note1+this.note2+this.note3)/3;}
    public String mention(){
      if(moyenne()>=16)
        return "Admis mention Très Bien";
      else if(moyenne()>=14)
        return "Admis mention Bien";
      else if(moyenne()>=12)
        return "Admis mention Assez Bien";
      else if(moyenne()>=10)
        return "Admis";
      else
        return "Ajourné";
    }
    public void ligneResultats(){
      String result=nom+" "+prenom+" "+moyenne()+" "+mention();
      if(moyenne()<10){
        if(this.note1>=10)
          result=result+" Module1";
        if(this.note2>=10)
          result=result+" Module2";
        if(this.note3>=10)
          result=result+" Module3";
      }
      System.out.println(result);
    }
    public String toString(){
      return this.getClass().getName()+" "+nom+" "+prenom;
    }
}
