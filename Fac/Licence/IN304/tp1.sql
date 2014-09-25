DROP TABLE acteur CASCADE CONSTRAINT;
DROP TABLE realisateur CASCADE CONSTRAINT;
DROP TABLE genre CASCADE CONSTRAINT;
DROP TABLE film CASCADE CONSTRAINT;
DROP TABLE jouer CASCADE CONSTRAINT;

CREATE TABLE acteur 
(
	idA CHARACTER(4) primary key,
	nom CHARACTER(15),
	prenom CHARACTER(15),
	nationalite CHARACTER(15)
);
CREATE TABLE realisateur
(
	idR CHARACTER(4) primary key,
	nom CHARACTER(15),
	prenom CHARACTER(15),
	nationalite CHARACTER(15)
);
CREATE TABLE genre
(
	idG CHARACTER(4) primary key,
	description CHARACTER(50)
);
CREATE TABLE film
(
	idF CHARACTER(4) primary key,
	titre CHARACTER(25),
	annee NUMERIC(4),
	pays CHARACTER(15),
	nbspectateurs NUMERIC(15) CHECK(nbspectateurs>0),
	idRealisateur CHARACTER(4) REFERENCES realisateur(idR),
	idGenre CHARACTER(4) REFERENCES genre(idG)
);
CREATE TABLE jouer
(
	idActeur CHARACTER(4),
	idFilm CHARACTER(4),
	salaire NUMERIC(15) CHECK(salaire>0),
	primary key(idActeur,idFilm)
);


INSERT INTO acteur VALUES('JoDe','Depp','Johnny','USA');
INSERT INTO acteur VALUES('LeDi','Dicaprio','Leonardo','USA');
INSERT INTO acteur VALUES('AlPa','Pacino','Alfredo','ITA');

INSERT INTO realisateur VALUES('StSp','Spielberg','Steven','USA');
INSERT INTO realisateur VALUES('JaCa','Cameron','James','USA');
INSERT INTO realisateur VALUES('TiBu','Burton','Tim','USA');
INSERT INTO realisateur VALUES('Daro','Daroussin',' ',' ');

INSERT INTO genre VALUES('Fant','Fantastique');
INSERT INTO genre VALUES('Roma','Romantique');
INSERT INTO genre VALUES('Come','Comedie');
INSERT INTO genre VALUES('Poli','Policier');
INSERT INTO genre VALUES('CoMu','Comedie musicale');

INSERT INTO film VALUES('AlWo','Alice in Wonderland',2010,'USA',1000000,'TiBu','Fant');
INSERT INTO film VALUES('Tita','Titanic',1997,'USA',1000000,'JaCa','Roma');
INSERT INTO film VALUES('aaaa','a',1998,'f',1,'Daro','Poli');
INSERT INTO film VALUES('bbbb','b',2000,'i',1,'Daro','CoMu');
INSERT INTO film VALUES('cccc','c',2005,'a',1,'Daro','Come');

INSERT INTO jouer VALUES('JoDe','AlWo',1000000);
INSERT INTO jouer VALUES('LeDi','Tita',1000000);
INSERT INTO jouer VALUES('AlPa','aaaa',500000);
INSERT INTO jouer VALUES('AlPa','bbbb',500000);


UPDATE jouer SET salaire=salaire*1.2;

DELETE FROM realisateur WHERE idR='StSp';

SELECT nom,prenom FROM acteur,genre,jouer,film WHERE idA=idActeur AND idG=idGenre AND idF=idFilm AND (description='Comedie' OR description='Policier');

SELECT titre FROM film,realisateur WHERE idRealisateur=idR AND nom='Daroussin' AND annee>1999;

SELECT realisateur.nom,realisateur.prenom,acteur.nom,acteur.prenom FROM realisateur,acteur,jouer,film WHERE idA=idActeur AND idR=idRealisateur AND idF=idFilm;

SELECT description FROM genre,film,acteur,jouer WHERE idActeur=idA AND idFilm=idF AND idGenre=idG AND nom='Pacino';

SELECT nom,prenom FROM realisateur,genre,film WHERE idG=idGenre AND idR=idRealisateur AND description='Comedie musicale' ORDER BY annee;

SELECT COUNT(*) FROM film;

SELECT MIN(annee) FROM film;

SELECT MAX(salaire),MIN(salaire),AVG(salaire) FROM jouer;

SELECT MAX(nbspectateurs),MIN(nbspectateurs),AVG(nbspectateurs) FROM film,genre WHERE idG=idGenre AND description='Comedie';

SELECT AVG(salaire)/AVG(nbspectateurs) FROM jouer,film,acteur WHERE idA=idActeur AND idF=idFilm AND nom='Pacino';

SELECT annee,COUNT(*) FROM film GROUP BY annee ORDER BY annee;

SELECT annee,MAX(nbspectateurs) FROM film GROUP BY annee ORDER BY annee;

SELECT annee,COUNT(*) FROM film GROUP BY annee HAVING annee>=1990 ORDER BY annee;

SELECT annee,COUNT(*) FROM film GROUP BY annee HAVING MIN(nbspectateurs)>=1000000 ORDER BY annee;