package tp2;

import java.util.*;

public class Promotion{
  private Vector<Etudiant> listeEtudiants;
  private int annee;

    public Promotion(){ this.listeEtudiants=new Vector<Etudiant>(); this.annee=0; }
    public Promotion(int a){ this.listeEtudiants=new Vector<Etudiant>(); this.annee=a; }

    public int getAnnee(){ return this.annee; }
    public void setAnnee(int a){ this.annee=a; }

    public Etudiant getEtudiant(int i){ return this.listeEtudiants.get(i); }
    public int getNbEtudiants(){ return this.listeEtudiants.size(); }

    public void inscrire(Etudiant e){ this.listeEtudiants.add(e); }
    
}
