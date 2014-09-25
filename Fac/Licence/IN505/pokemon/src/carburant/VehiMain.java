package carburant;

public class VehiMain {
	public static void main(String[] args) {
		Bus bus = new Bus("AB-1587-FGH");
		Citerne citerne = new Citerne("BG-2648-FJS",5);
		Bache bache1 = new Bache("KI-6732-AZT",4);
		Bache bache2 = new Bache("OT-9463-DFP",12);
		System.out.println(bus);
		System.out.println(citerne);
		System.out.println(bache1+" vitMax = "+bache1.vitMax()+"km/h");
		System.out.println(bache2+" vitMax = "+bache2.vitMax()+"km/h");
		Convoi c1 = new Convoi();
		Convoi c2 = new Convoi();
		c1.insertVehi(bus);
		c1.insertVehi(citerne);
		c2.insertVehi(bache1);
		c2.insertVehi(bache2);
		System.out.println(c1);
		System.out.println(c2);
	}
}

abstract class Vehicule {
	protected String immat;
	protected int poidsVide;
	
	public Vehicule(String i, int pv){
		immat=i; poidsVide=pv;
	}
	public abstract int vitMax();
	public String toString() {
		return "Le vehicule immatricule "+immat+" a un PV de "+poidsVide+" tonnes";
	}
}

abstract class Chargement extends Vehicule {
	protected int charge;
	protected int chargeMax;
	
	public Chargement(String i, int pv, int c, int cm) {
		super(i, pv); charge=c; chargeMax=cm;
	}
	public String toString() {
		return super.toString()+", une charge de "+charge+" tonnes sur "+chargeMax;
	}
}

class Bus extends Vehicule {
	public Bus(String i){
		super(i,4);
	}
	public int vitMax() {
		return 150;
	}
}

class Citerne extends Chargement {
	public Citerne(String i, int c) {
		super(i,3,c,10);
	}
	public int vitMax() {
		if(charge==0)
			return 130;
		else if(charge<=1)
			return 110;
		else if(charge<=4)
			return 90;
		else
			return 80;
	}
}

class Bache extends Chargement {
	public Bache(String i, int c) {
		super(i,4,c,20);
	}
	public int vitMax() {
		if(charge==0)
			return 130;
		else if(charge<=3)
			return 110;
		else if(charge<=7)
			return 90;
		else
			return 80;
	}
}

