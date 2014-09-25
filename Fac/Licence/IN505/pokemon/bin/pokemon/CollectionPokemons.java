package pokemon;
import java.util.ArrayList;

public class CollectionPokemons {
	private ArrayList<Pokemon> pokedex;
	
	public CollectionPokemons() {
		pokedex = new ArrayList<Pokemon>();
	}
	public void insertPoke(Pokemon p) {
		pokedex.add(p);
	}
	public float vMoy() {
		float moy=0;
		for(Pokemon p : pokedex)
			moy=moy+p.vitesse();
		return moy/pokedex.size();
	}
	public float vMoySpo() {
		float moy=0;
		for(Pokemon p : pokedex)
			if (p instanceof Sportif)
				moy=moy+p.vitesse();
		return moy/pokedex.size();
	}
}
