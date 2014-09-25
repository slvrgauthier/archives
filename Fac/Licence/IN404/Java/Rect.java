package rect;

public class Rect
{
  private float longueur;
  private float largeur;
  private float aire;
  private float perimetre;
  private String couleur;
  private Point2D position;
  private static Rect pgRect;
  private static final int nbCot=4;
  private static final int angle=90;

    public Rect(float lo, float la){
      this.longueur=lo;
      this.largeur=la;
      this.aire=aire();
      this.perimetre=perimetre();
      if(this.aire>pgRect.aire){
        pgRect=this
      }
    }

    public Rect(float lo, float la, String col, Point2D pos){
      this.longueur=lo;
      this.largeur=la;
      this.aire=aire();
      this.perimetre=perimetre();
      this.couleur=col;
      this.position=pos;
      if(this.aire>pgRect.aire){
        pgRect=this;
      }

    public getLongueur(){ return this.longueur; }
    public setLongueur(float la){

    }

    public getLargeur(){ return this.largeur; }
    public setLargeur(float la){

    }

    public getAire(){ return this.aire; }

    public getPerimetre(){ return this.perimetre; }

    public getCouleur(){ return this.couleur; }
    public setCouleur(String col){

    }

    public getPosition(){ return this.position; }
    public setPosition(Point2D pos){

    }

    public getNbCot(){ return Rect.nbCot; }
    public getAngle(){ return Rect.angle; }
    public getPgRect(){ return Rect.pgRect; }

}