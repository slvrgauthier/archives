package seminaire;

import java.util.Date;

public class Creneau {
	private Date debut;
	private Date fin;
	
	public Creneau(Date d, Date f) {
		debut = d;
		fin = f;
	}

	public Date getDebut() {
		return debut;
	}

	public Date getFin() {
		return fin;
	}
}
