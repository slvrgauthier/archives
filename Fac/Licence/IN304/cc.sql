DROP TABLE personne CASCADE CONSTRAINT;
DROP TABLE voiture CASCADE CONSTRAINT;

CREATE TABLE personne
(
	id CHARACTER(4) primary key,
	nom CHARACTER(20),
	prenom CHARACTER(20),
	dateNaiss date
);

CREATE TABLE voiture
(
	immat CHARACTER(8) primary key,
	marque CHARACTER(20),
	annee NUMERIC(4),
	prix NUMERIC(5) CHECK(prix > 0),
	idProp CHARACTER(4) REFERENCES personne(id)
);

ALTER SESSION SET NLS_DATE_FORMAT='dd/mm/yyyy';

INSERT INTO personne VALUES('Id01','Martin','Paul','01/02/1967');
INSERT INTO personne VALUES('Id02','Duval','','03/09/1980');

INSERT INTO voiture VALUES('1111AA01','Peugeot',1997,16000,'Id01');
INSERT INTO voiture VALUES('2222BB02','Peugeot',2000,41200,'Id01');
INSERT INTO voiture VALUES('4444DD13','Fiat',1995,30300,'Id02');

SELECT * FROM personne;
SELECT * FROM voiture;

SELECT COUNT(*) FROM personne;

SELECT COUNT(*) FROM personne WHERE prenom IS NULL;

SELECT nom FROM personne WHERE TO_CHAR(dateNaiss,'mon')='sep';

SELECT idProp,COUNT(*) FROM voiture GROUP BY idProp ORDER BY idProp;

SELECT nom,prenom,SUM(prix) AS capital FROM personne,voiture WHERE idProp=id GROUP BY nom,prenom ORDER BY nom,prenom;

SELECT marque,AVG(prix) FROM voiture GROUP BY marque ORDER BY marque;

SELECT nom,prenom,COUNT(*) FROM personne,voiture WHERE idProp=id AND prix>20000 GROUP BY nom,prenom ORDER BY nom,prenom;

SELECT idProp,SUM(prix) AS capital FROM voiture HAVING SUM(prix)>50000 GROUP BY idProp ORDER BY idProp;

SELECT idProp,annee,SUM(prix) AS capital FROM voiture GROUP BY idProp,annee ORDER BY idProp,annee;

SELECT nom,prenom,annee,SUM(prix) AS capital FROM voiture,personne WHERE idProp=id GROUP BY nom,prenom,annee ORDER BY nom,prenom,annee;