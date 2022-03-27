CREATE DATABASE Games;

CREATE TABLE JOGO (Id_Jogo INTEGER AUTO_INCREMENT NOT NULL,
Titulo varchar(25),
Lancamento date, 
Conquistas integer, 
Classificacao_Inditiva integer, 
Multiplayer_Singleplayer varchar(20),
PRIMARY KEY(Id_jogo));

CREATE TABLE GENERO (Id_Genero INTEGER AUTO_INCREMENT NOT NULL, 
Nome varchar(25), 
Conteudo_Adulto bool, 
PRIMARY KEY(Id_Genero));

CREATE TABLE PERTENCE (Id_Jogo integer, 
Id_Genero integer, 
PRIMARY KEY (Id_Jogo, Id_Genero), 
FOREIGN KEY (Id_Jogo) REFERENCES JOGO (Id_Jogo), 
FOREIGN KEY (Id_Genero) REFERENCES GENERO (Id_Genero));

CREATE TABLE CONSOLE (Id_Console INTEGER AUTO_INCREMENT NOT NULL, 
Nome varchar(25), 
Specs varchar(100), 
Lancamento date, 
PRIMARY KEY(Id_Console));

CREATE TABLE COMPATIVEL (Id_Jogo integer, 
Id_Console integer, 
PRIMARY KEY (Id_Jogo, Id_Console), 
FOREIGN KEY (Id_Jogo) REFERENCES JOGO (Id_Jogo), 
FOREIGN KEY (Id_Console) REFERENCES CONSOLE (Id_Console));

CREATE TABLE CAMPEONATO(Id_Jogo integer, 
Id_Camp integer, 
Localizacao varchar(25), 
Premiacao integer, 
Vencedor integer,
Data date, 
PRIMARY KEY(Id_Camp), 
FOREIGN KEY (Vencedor) REFERENCES PESSOA(Id_Pessoa),
FOREIGN KEY (Id_Jogo) REFERENCES JOGO(Id_Jogo));

CREATE TABLE SERVIDOR (Localizacao varchar(50), 
IP varchar(50), 
Id_Servidor integer,
Id_Jogo integer,  
PRIMARY KEY (Id_Jogo, Id_Servidor), 
FOREIGN KEY (Id_Jogo) REFERENCES JOGO (Id_Jogo));

CREATE TABLE PESSOA (Nome varchar(50), 
Idade integer, 
CPF varchar(50), 
Email varchar(50), 
Id_Pessoa INTEGER AUTO_INCREMENT NOT NULL, 
PRIMARY KEY (Id_Pessoa));

CREATE TABLE EMPRESA (Nome varchar(50), 
CNPJ varchar(50), 
Data_de_criacao date, 
Id_Empresa INTEGER AUTO_INCREMENT NOT NULL, 
Id_Pessoa integer, 
Distribuidora bool,
Desenvolvedora bool,
PRIMARY KEY (Id_Empresa), 
FOREIGN KEY (Id_Pessoa) REFERENCES PESSOA (Id_Pessoa));

CREATE TABLE USUARIO (Senha CHAR(32), 
Login VARCHAR(10), 
Id_Pessoa integer, 
PRIMARY KEY (Login), 
FOREIGN KEY (Id_Pessoa) REFERENCES PESSOA (Id_Pessoa));

CREATE TABLE DISTRIBUIDO (Id_Empresa integer, 
Id_Jogo integer, 
PRIMARY KEY(Id_Empresa, Id_Jogo), 
FOREIGN KEY (Id_Empresa) REFERENCES EMPRESA(Id_Empresa), 
FOREIGN KEY (Id_Jogo) REFERENCES JOGO(Id_Jogo));

CREATE TABLE DESENVOLVIDO (Id_Empresa integer, 
Id_Jogo integer, 
Id_Pessoa integer, 
PRIMARY KEY(Id_Empresa, Id_Jogo, Id_Pessoa), 
FOREIGN KEY (Id_Empresa) REFERENCES EMPRESA(Id_Empresa), 
FOREIGN KEY (Id_Jogo) REFERENCES JOGO(Id_Jogo), 
FOREIGN KEY (Id_Pessoa) REFERENCES PESSOA(Id_Pessoa));

INSERT INTO JOGO (Id_Jogo, Titulo, Lancamento, Conquistas, Classificacao_Inditiva, Multiplayer_Singleplayer) VALUES 
(NULL, 'Jogo 1', '2022-01-10', 15, '15', 'SinglePlayer'),
(NULL, 'Jogo 2', '2022-01-09', 17, '18', 'SinglePlayer'),
(NULL, 'Jogo 3', '2022-01-08', 20, '10', 'SinglePlayer'),
(NULL, 'Jogo 4', '2022-01-07', 23, '18', 'MultiPlayer'),
(NULL, 'Jogo 5', '2022-01-06', 10, '10', 'SinglePlayer'),
(NULL, 'Jogo 6', '2022-01-05', 25, '15', 'MultiPlayer'),
(NULL, 'Jogo 7', '2022-01-04', 22, '18', 'SinglePlayer'),
(NULL, 'Jogo 8', '2022-01-03', 17, '10', 'MultiPlayer'),
(NULL, 'Jogo 9', '2022-01-02', 9, '18', 'MultiPlayer'),
(NULL, 'Jogo 10', '2022-01-01', 11, '18', 'SinglePlayer');

INSERT INTO GENERO(Id_Genero, Nome, Conteudo_Adulto) 
VALUES 
(NULL, 'Nome 1', 0),
(NULL, 'Nome 2', 1),
(NULL, 'Nome 3', 0),
(NULL, 'Nome 4', 1),
(NULL, 'Nome 5', 0),
(NULL, 'Nome 6', 1),
(NULL, 'Nome 7', 0),
(NULL, 'Nome 8', 1),
(NULL, 'Nome 9', 0),
(NULL, 'Nome 10', 0);

INSERT INTO PERTENCE (Id_Jogo, Id_Genero) 
VALUES 
(1, 2),
(2, 3),
(4, 7),
(5, 7),
(5, 2),
(6, 6),
(5, 3),
(1, 7),
(9, 10),
(3, 6);

INSERT INTO CONSOLE (Id_Console, Nome, Specs, Lancamento)
VALUES 
(NULL, 'Console 1', 'Specs 1, specs 2...', '2022-01-31'),
(NULL, 'Console 2', 'Specs 1, specs 2...', '2022-01-12'),
(NULL, 'Console 3', 'Specs 1, specs 2...', '2022-01-22'),
(NULL, 'Console 4', 'Specs 1, specs 2...', '2022-01-11'),
(NULL, 'Console 5', 'Specs 1, specs 2...', '2022-01-15'),
(NULL, 'Console 6', 'Specs 1, specs 2...', '2022-01-16'),
(NULL, 'Console 7', 'Specs 1, specs 2...', '2022-01-18'),
(NULL, 'Console 8', 'Specs 1, specs 2...', '2022-01-26'),
(NULL, 'Console 9', 'Specs 1, specs 2...', '2022-01-21'),
(NULL, 'Console 10', 'Specs 1, specs 2...', '2022-01-28');

INSERT INTO COMPATIVEL (Id_Jogo, Id_Console)
VALUES 
(1, 2),
(2, 8),
(4, 7),
(2, 7),
(5, 2),
(6, 6),
(5, 3),
(1, 5),
(9, 10),
(3, 6);

INSERT INTO CAMPEONATO ( Id_Camp, Id_Jogo, Localizacao, Premiacao, Vencedor, Data)
VALUES
(1, 1, 'local 1', 1000000, 1 ,'2022-01-31'),
(2, 2, 'local 2', '500000', 1 ,'2022-01-21'),
(3, 2, 'local 3', '700000', 7 ,'2022-01-11'),
(4, 3, 'local 4', '1000000', 4 ,'2022-01-10'),
(5, 3, 'local 5', '350000', 5 ,'2022-01-22'),
(6, 4, 'local 6', '1500000', 1 ,'2022-01-30'),
(7, 5, 'local 7', '1200000', 7 ,'2022-01-05'),
(8, 6, 'local 8', '750000', 3 ,'2022-01-03'),
(9, 7, 'local 9', '900000', 2 ,'2022-01-19'),
(10, 8, 'local 10', '820000', 3 ,'2022-01-24');

INSERT INTO SERVIDOR (Localizacao , IP, Id_Servidor, Id_Jogo)  
VALUES
('Localizacao 1', '192.168.111.001', 1, 10),
('Localizacao 2', '192.168.111.002', 2, 5),
('Localizacao 3', '192.168.111.003', 3, 1),
('Localizacao 4', '192.168.111.004', 4, 2),
('Localizacao 5', '192.168.111.005', 5, 9),
('Localizacao 6', '192.168.111.006', 6, 7),
('Localizacao 7', '192.168.111.007', 7, 3),
('Localizacao 8', '192.168.111.008', 8, 4),
('Localizacao 9', '192.168.111.009', 9, 6),
('Localizacao 10', '192.168.111.0010', 10, 8);

INSERT INTO PESSOA (Nome, Idade, CPF, Email, Id_Pessoa)
VALUES
('Nome 1', 22, '413.695.658-98', 'email1@gmail.com', NULL),
('Nome 2', 13, '213.895.678-96', 'email2@hotmail.com', NULL),
('Nome 3', 37, '113.895.678-97', 'email3@uol.com.br', NULL),
('Nome 4', 54, '313.895.678-98', 'email4@outlook.com', NULL),
('Nome 5', 25, '218.899.988-96', 'email5@hotmail.com', NULL),
('Nome 6', 18, '213.796.679-97', 'email6@gmail.com', NULL),
('Nome 7', 17, '713.845.678-96', 'email7@hotmail.com', NULL),
('Nome 8', 20, '513.695.658-97', 'email8@unifesp.br', NULL),
('Nome 9', 28, '514.694.758-96', 'email9@gmail.com', NULL),
('Nome 10', 33, '614.494.758-96', 'email10@hotmail.com', NULL);

INSERT INTO EMPRESA (Id_Empresa, Id_Pessoa, Nome, CNPJ, Data_de_criacao, Distribuidora,
Desenvolvedora )
VALUES
(NULL, 1, 'Nome 1', '12.315.678/0001-90' ,'2022-01-31', 1, 0),
(NULL, 2, 'Nome 2', '12.325.678/0001-90' ,'2022-01-31', 0, 1),
(NULL, 3, 'Nome 3', '12.375.678/0001-90' ,'2022-01-31', 1, 0),
(NULL, 4, 'Nome 4', '12.335.678/0001-90' ,'2022-01-31', 0, 1),
(NULL, 4, 'Nome 5', '12.385.678/0001-90' ,'2022-01-31', 1, 0),
(NULL, 5, 'Nome 6', '12.345.678/0001-90' ,'2022-01-31', 0, 1),
(NULL, 5, 'Nome 7', '12.395.678/0001-90' ,'2022-01-31', 1, 0),
(NULL, 6, 'Nome 8', '12.325.678/0001-90' ,'2022-01-31', 0, 0),
(NULL, 6, 'Nome 9', '12.315.688/0001-90' ,'2022-01-31', 1, 0),
(NULL, 6, 'Nome 10', '12.045.678/0001-90' ,'2022-01-31',0, 1);

INSERT INTO USUARIO (Login, Id_Pessoa, Senha)
VALUES
('user1', 1, 'e7d80ffeefa212b7c5c55700e4f7193e'),
('user2', 2, 'a2e63ee01401aaeca78be023dfbb8c59'),
('user3', 3, 'e7d80ffeefa212b7c5c55700e4f7193e'),
('user4', 4, 'a2e63ee01401aaeca78be023dfbb8c59'),
('user5', 5, 'e7d80ffeefa212b7c5c55700e4f7193e'),
('user6', 6, 'a2e63ee01401aaeca78be023dfbb8c59'),
('user7', 7, 'e7d80ffeefa212b7c5c55700e4f7193e'),
('user8', 8, 'a2e63ee01401aaeca78be023dfbb8c59'),
('user9', 9, 'e7d80ffeefa212b7c5c55700e4f7193e'),
('user10', 10, 'a2e63ee01401aaeca78be023dfbb8c59');

INSERT INTO DISTRIBUIDO (Id_Empresa, Id_Jogo)
VALUES
(1, 10),
(3, 5),
(3, 2),
(3, 9),
(5, 7),
(5, 1),
(7, 3),
(7, 5),
(7, 10),
(9, 4);

INSERT INTO DESENVOLVIDO (Id_Empresa, Id_Jogo, Id_Pessoa)
VALUES
(2,10,1),
(4,9,5),
(6,8,7),
(2,1,5),
(4,2,9),
(4,3,3),
(6,8,8),
(6,7,5),
(2,6,3),
(2,4,6);