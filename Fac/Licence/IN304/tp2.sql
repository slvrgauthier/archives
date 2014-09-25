DROP TABLE Operateur CASCADE CONSTRAINT;
DROP TABLE Machine CASCADE CONSTRAINT;
DROP TABLE Piece CASCADE CONSTRAINT;
DROP TABLE Qualifie_sur CASCADE CONSTRAINT;

CREATE TABLE Operateur 
(
	numero CHARACTER(4) primary key,
	nom CHARACTER(15),
	age NUMERIC(2)
);
CREATE TABLE Machine
(
	referenceM CHARACTER(3) primary key,
	designationM CHARACTER(20)
);
CREATE TABLE Piece
(
	referenceP CHARACTER(2) primary key,
	designationP CHARACTER(6),
	reference_machine CHARACTER(3) REFERENCES Machine(referenceM),
	numero_operateur CHARACTER(4) REFERENCES Operateur(numero),
	quantite NUMERIC(3)
);
CREATE TABLE Qualifie_sur
(
	numero_operateur CHARACTER(4),
	reference_machine CHARACTER(3),
	ddate date,
	primary key(numero_operateur,reference_machine)
);

ALTER SESSION SET NLS_FORMAT_DATE='dd/mm/rr';

INSERT INTO Operateur VALUES('OP42','Robert','32');
INSERT INTO Operateur VALUES('OP10','Sophie','41');
INSERT INTO Operateur VALUES('OP78','Lucette','25');
INSERT INTO Operateur VALUES('OP22','Albert','25');
INSERT INTO Operateur VALUES('OP57','Marc','38');

INSERT INTO Machine VALUES('M12','Perceuse');
INSERT INTO Machine VALUES('M13','Ponceuse');
INSERT INTO Machine VALUES('M14','Tour numerique');

INSERT INTO Piece VALUES('P1','Piece1','M12','OP10','250');
INSERT INTO Piece VALUES('P2','Piece2','M12','OP22','600');
INSERT INTO Piece VALUES('P3','Piece3','M14','OP22','200');
INSERT INTO Piece VALUES('P4','Piece4','M13','OP78','150');

INSERT INTO Qualifie_sur VALUES('OP10','M12','15/01/00');
INSERT INTO Qualifie_sur VALUES('OP22','M12','20/05/01');
INSERT INTO Qualifie_sur VALUES('OP10','M13','10/10/99');
INSERT INTO Qualifie_sur VALUES('OP42','M13','17/01/02');
INSERT INTO Qualifie_sur VALUES('OP78','M12','19/07/98');
INSERT INTO Qualifie_sur VALUES('OP10','M14','04/05/01');


SELECT nom,SUM(quantite) FROM Piece,Operateur WHERE numero_operateur=numero GROUP BY nom ORDER BY nom;

SELECT nom FROM Piece,Operateur WHERE numero_operateur=numero GROUP BY nom HAVING SUM(quantite)>500 ORDER BY nom;

SELECT reference_machine,COUNT(*) FROM Qualifie_sur GROUP BY reference_machine ORDER BY reference_machine;

SELECT reference_machine,SUM(quantite) FROM Piece GROUP BY reference_machine ORDER BY reference_machine;

SELECT nom,COUNT(*) FROM Operateur,Qualifie_sur WHERE numero_operateur=numero GROUP BY nom ORDER BY nom;

SELECT reference_machine,SUM(quantite) FROM Piece GROUP BY reference_machine ORDER BY reference_machine;