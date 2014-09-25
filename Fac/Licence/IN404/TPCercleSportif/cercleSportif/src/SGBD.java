package cercleSportif;

import java.sql.Date;

public class SGBD {

	private Planning planning;
	
	private String nom;
	private Date archivage;
	
	public SGBD(String nom) {
		this.nom = nom;
	}
	public SGBD(String nom, Date archivage) {
		this.nom = nom;
		this.archivage = archivage;
	}
	
	public Planning getPlanning() {
		return planning;
	}
	public void setPlanning(Planning planning) {
		this.planning = planning;
	}
	public String getNom() {
		return nom;
	}
	public void setNom(String nom) {
		this.nom = nom;
	}
	public Date getArchivage() {
		return archivage;
	}
	public void setArchivage(Date archivage) {
		this.archivage = archivage;
	}
	
}
