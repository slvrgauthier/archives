package pokemon;

import java.lang.reflect.*;
import java.util.Scanner;

public class PokeFactory {
	public static void main(String[] args) throws Exception{
		System.out.println("Quel type de pokémon souhaitez-vous faire naître ?");
		Scanner s = new Scanner(System.in);
		String clName = s.nextLine();
		System.out.println(pokeBirth(clName));
	}
	
	public static Pokemon pokeBirth(String clName) throws Exception{
		Class<?> cl=Class.forName(clName);
		Constructor<?> cons=cl.getConstructor();
		Object child=cons.newInstance();
		Pokemon p = (Pokemon)child;
		pokeTeach(p);
		return p;
	}

	public static void pokeTeach(Pokemon p) throws Exception{
		Scanner s=new Scanner(System.in);
		Field f[]=p.getClass().getFields();
		for(Field ff : f) {
			System.out.println("Entrez la valeur de l'attribut : "+ff.getName());
			String param=s.nextLine();
			if(ff.getType().getName().endsWith("int")) {
				int x = Integer.parseInt(param);
				ff.set(p, x);
			}
			else if((ff.getType().getName().endsWith("float"))) {
				float x = Float.parseFloat(param);
				ff.set(p, x);
			}
			else
				ff.set(p, param);
		}
	}
}
