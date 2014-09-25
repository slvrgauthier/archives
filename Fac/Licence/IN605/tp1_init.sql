drop table fournisseurs;
drop table prix;
drop table clients;
drop table commandes;


------------------------------FOURNISSEURS-------------------------------------
create table fournisseurs(
    nomf char(20) primary key,       -- cle primaire de la table 
    adressef char(20) not null
);

insert into fournisseurs values ('Abounayan', '92190 Meudon');
insert into fournisseurs values ('Cima','75010 Paris');
insert into fournisseurs values ('Preblocs','92230 Genevilliers');
insert into fournisseurs values ('Samaco','75116 Paris');
--------------------------------PRIX----------------------------------------------
create table prix(
        nomf char(20),
        nomp char(20),
        cout number(8),         
     primary key (nomf, nomp) -- cle primaire de la table
);

insert into prix values ('Abounayan', 'sable',300);
insert into prix values ('Abounayan', 'brique',1500);
insert into prix values ('Abounayan', 'parpaing',1150);
insert into prix values ('Preblocs','tuile',1150);
insert into prix values ('Preblocs','parpaing',1200);
insert into prix values ('Samaco','parpaing',1150);
insert into prix values ('Samaco','ciment',125);
insert into prix values ('Samaco','brique',1200);


------------------------------CLIENT------------------------------------------------
create table clients(
     nomc char(20)  primary key,       -- cle primaire de la table
     adrsc char(20),      
     solde number(8)
);

insert into clients values ('Jean','75006 Paris',-12000);
insert into clients values ('Paul','75003 Paris',0);
insert into clients values ('Vincent','94200 Ivry',3000);
insert into clients values ('Pierre','92400 Courbevoie',7000);
insert into clients values ('Nina','34000 Montpellier',2000);
insert into clients values ('Rene','30000 Nimes',-2000);

-----------------------------COMMANDE--------------------------------------------
create table commandes(
    ncom number(3) primary key,        -- cle primaire de la table
    nomc char(20) ,          
    nomp char(20),         
    qte number(8) 
    );

insert into commandes values (1,'Jean','brique',5);
insert into commandes values (2,'Jean','ciment',1);
insert into commandes values (3,'Paul','brique',3);
insert into commandes values (4,'Paul','parpaing',9);
insert into commandes values (5,'Vincent','parpaing',7);
insert into commandes values (6,'Vincent','parpaing',10);
insert into commandes values (7,'Jean','brique',8);
insert into commandes values (8,'Nina','brique',6);