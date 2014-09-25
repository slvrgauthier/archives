SELECT nomc AS client_solde_negatif FROM clients WHERE solde<0;
SELECT DISTINCT nomf AS f_brique_ou_parpaing FROM prix WHERE nomp='brique' OR nomp='parpaing';
SELECT nomc,adrsc FROM clients WHERE nomc LIKE 'J%';
SELECT clients.nomc,adrsc FROM clients,commandes WHERE clients.nomc=commandes.nomc AND nomp='brique' AND qte BETWEEN 5 AND 10;
SELECT nomp,AVG(cout) AS prix_moyen FROM prix GROUP BY nomp;
SELECT nomp,AVG(cout) AS prix_moyen FROM prix GROUP BY nomp HAVING COUNT(nomp)>1;
SELECT DISTINCT nomp FROM prix WHERE cout>(SELECT AVG(cout) FROM prix);
SELECT DISTINCT nomp,nomf FROM prix WHERE cout>ALL(SELECT AVG(cout) FROM prix GROUP BY nomp);

INSERT INTO commandes values (9,'Paul','ciment',12);
INSERT INTO commandes values (10,'Pierre','parpaing',8);
UPDATE clients SET adrsc='83000 Toulon' WHERE nomc='Jean';
UPDATE prix SET cout=cout*1.15 WHERE nomf='Samaco';
UPDATE fournisseurs SET nomf='Technal',adressef='69005 Lyon' WHERE nomf='Samaco';
UPDATE prix SET nomf='Technal' WHERE nomf='Samaco';