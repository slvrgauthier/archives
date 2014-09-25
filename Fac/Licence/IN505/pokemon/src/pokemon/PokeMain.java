package pokemon;

public class PokeMain {
	public static void main(String[] args) {
		Sportif pikachu = new Sportif("Pikachu",18,2,(float)0.85,120);
		Casanier salameche = new Casanier("Salameche",12,2,(float)0.65,8);
		Mer rondoudou = new Mer("Rondoudou",45,2);
		Croisiere bulbizarre = new Croisiere("Bulbizarre",15,3);
		System.out.println(pikachu);
		System.out.println(salameche);
		System.out.println(rondoudou);
		System.out.println(bulbizarre);
		CollectionPokemons collec = new CollectionPokemons();
		collec.insertPoke(pikachu);
		collec.insertPoke(salameche);
		collec.insertPoke(rondoudou);
		collec.insertPoke(bulbizarre);
		System.out.println("Vmoy : "+collec.vMoy());
		System.out.println("VmoySpo : "+collec.vMoySpo());
	}
}

abstract class Pokemon {
	public String nom;
	public int poids;
	
	public Pokemon(){}
	
	public Pokemon(String n, int p){
		nom=n; poids=p;
	}
	public String toString() { 
		return "Je suis le pokémon "+nom+" mon poids est de "+poids+" kg";
	}
	public abstract float vitesse();
}

abstract class Terrestre extends Pokemon {
	public int nb_pattes;
	public float taille;
	
	public Terrestre(){}
	
	public Terrestre(String n, int p, int np, float t) {
		super(n,p);
		nb_pattes=np; taille=t;
	}
	public float vitesse() {
		String str = String.valueOf(nb_pattes*taille*3);
		str = str.substring(0,str.indexOf('.')+2);
		return Float.parseFloat(str);
	}
	public String toString() {
		return super.toString()+", ma vitesse est de "+vitesse()+" j'ai "+nb_pattes+" pattes, ma taille est de "+taille+"m";
	}
}

abstract class Aquatique extends Pokemon {
	public int nb_nageoires;
	
	public Aquatique() {}

	public Aquatique(String n, int p, int nn) {
		super(n,p);
		nb_nageoires=nn;
	}
}

class Sportif extends Terrestre {
	public int pulse;
	
	public Sportif(){}
	
	public Sportif(String n, int p, int np, float t) {
		super(n, p, np, t);
	}

	public Sportif(String n, int p, int np, float t, int pu) {
		super(n,p,np,t);
		pulse=pu;
	}
	public String toString() {
		return super.toString()+" ma fréquence cardiaque est de "+pulse+" pulsations à la minute";
	}
}

class Casanier extends Terrestre {
	public int heure;
	
	public Casanier(){}
	
	public Casanier(String n, int p, int np, float t, int h) {
		super(n,p,np,t);
		heure=h;
	}
	public String toString() {
		return super.toString()+" je regarde la télé "+heure+"h par jour";
	}
}

class Mer extends Aquatique {
	public Mer(){}
	
	public Mer(String n, int p, int nn) {
		super(n,p,nn);
	}
	public float vitesse() {
		String str = String.valueOf(poids/25*nb_nageoires);
		str = str.substring(0,str.indexOf('.')+2);
		return Float.parseFloat(str);
	}
	public String toString() {
		return super.toString()+", ma vitesse est de "+vitesse()+" km/h j'ai "+nb_nageoires+" nageoires";
	}
}

class Croisiere extends Aquatique {
	public Croisiere(){}
	
	public Croisiere(String n, int p, int nn) {
		super(n,p,nn);
	}
	public float vitesse() {
		String str = String.valueOf((poids/25*nb_nageoires)/2);
		str = str.substring(0,str.indexOf('.')+2);
		return Float.parseFloat(str);
	}
	public String toString() {
		return super.toString()+", ma vitesse est de "+vitesse()+" km/h j'ai "+nb_nageoires+" nageoires";
	}
}

