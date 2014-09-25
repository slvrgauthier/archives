package carburant;
import java.util.ArrayList;

public class Convoi {
	private ArrayList<Vehicule> convoi;
	private int nombre=0;
	
	public Convoi() {
		convoi = new ArrayList<Vehicule>();
	}
	public Convoi(ArrayList<Vehicule> c) {
		convoi=c;
	}
	public void insertVehi(Vehicule v) {
		convoi.add(v);
		nombre++;
	}
	public int vitMax() {
		int vit=9999;
		for(Vehicule v : convoi)
			if(v.vitMax()<vit)
				vit=v.vitMax();
		return vit;
	}
	public String toString() {
		String str="Le convoi comporte "+nombre+" vehicule. vitMax = "+vitMax()+"km/h. En voici la liste :";
		for(Vehicule v : convoi)
			str+=" "+v.toString();
		return str;
	}
}


