CREATE DATABASE MC;

CREATE TABLE Medico (cod integer, nome varchar(20), telefone varchar(15),
PRiMARY KEY(cod)) Engine=iNNODB;

CREATE TABLE Especialidade(cod integer, nome varchar(20),
PRiMARY KEY(cod)) Engine=iNNODB;

CREATE TABLE Clinica (cod integer, nome varchar(20), endereco varchar(15),
PRiMARY KEY(cod)) Engine=iNNODB;

CREATE TABLE Consulta(cod integer, data date, hora time, especialidade_cod integer, medico_cod integer, clinica_cod integer,
PRiMARY KEY(cod),
FOREIGN KEY(especialidade_cod) REFERENCES Especialidade(cod),
FOREIGN KEY(medico_cod) REFERENCES Medico(cod),
FOREIGN KEY(clinica_cod) REFERENCES Clinica(cod)
) Engine=iNNODB;


CREATE TABLE MedicoEspecialidade(            
medico_cod integer,        
especialidade_cod integer, 
PRIMARY KEY (medico_cod,especialidade_cod),          
FOREIGN KEY (medico_cod) REFERENCES Medico(cod),             
FOREIGN KEY (especialidade_cod) REFERENCES Especialidade(cod))Engine=INNODB;

CREATE TABLE EspecialidadeClinica(
especialidade_cod integer,
clinica_cod integer,
PRIMARY KEY  (especialidade_cod, clinica_cod),
FOREIGN KEY (especialidade_cod)  REFERENCES Especialidade(cod),
FOREIGN KEY (clinica_cod) REFERENCES Clinica(cod))Engine=INNODB;
             

CREATE TABLE MedicoClinica(
medico_cod integer,
clinica_cod integer,
PRIMARY KEY  (medico_cod, clinica_cod),
FOREIGN KEY   (medico_cod) REFERENCES  Medico(cod),
FOREIGN KEY (clinica_cod) REFERENCES Clinica(cod) )Engine=INNODB;

iNSERT iNTO Medico VALUES (1,'Andre', '1111-1111');
iNSERT iNTO Medico VALUES (2,'Arthur', '2222-2222');
iNSERT iNTO Medico VALUES (3, 'Marcia', '3333-3333');
iNSERT iNTO Medico VALUES (4, 'Jessica', '4444-4444' );
iNSERT iNTO Medico VALUES (5, 'Leonardo', '5555-5555');
iNSERT iNTO Medico VALUES (6, 'Paulo', '6666-6666');
iNSERT iNTO Medico VALUES (7, 'Joao', '7777-7777');
iNSERT iNTO Medico VALUES (8, 'Soraia', '8888-8888');
iNSERT iNTO Medico VALUES  (9, 'Elaine', '9999-9999');
iNSERT iNTO Medico VALUES (10, 'Jose Maria', '1010-1010');

iNSERT iNTO Especialidade VALUES (1, 'OTORRiNOLARiNGOLOGiA');
iNSERT iNTO Especialidade VALUES (2, 'PEDiATRiA');
iNSERT iNTO Especialidade VALUES (3, 'GiNECOLOGiA');
iNSERT iNTO Especialidade VALUES (4, 'CARDiOLOGiA');
iNSERT iNTO Especialidade VALUES (5, 'UROLOGiA');
iNSERT iNTO Especialidade VALUES (6, 'DERMATOLOGiA');
iNSERT iNTO Especialidade VALUES (7, 'OFTALMOLOGiA');
iNSERT iNTO Especialidade VALUES (8, 'GERiATRiA');
iNSERT iNTO Especialidade VALUES (9, 'ORTOPEDiA');
iNSERT iNTO Especialidade VALUES (10,'CLiNiCO GERAL');

iNSERT iNTO Clinica VALUES (1, 'centro de otorrino', 'Centro');
iNSERT iNTO Clinica VALUES (2, 'clinica pediatrica', 'barro preto');
iNSERT iNTO Clinica VALUES (3, 'clinica papa nicolau',  'barro preto');
iNSERT iNTO Clinica VALUES (4, 'clinica sagrado', 'sagrada familia');
iNSERT iNTO Clinica VALUES (5, 'clinica urológica', 'sagrada familia');
iNSERT iNTO Clinica VALUES (6, 'clinica flor da pele',  'funcionarios');
iNSERT iNTO Clinica VALUES (7, 'ortocentro', 'padre eustaquio');
iNSERT iNTO Clinica VALUES (8, 'clinica bem estar', 'mangabeiras');
iNSERT iNTO Clinica VALUES (9, 'clinica oftalmo', 'santa efigenia');
iNSERT iNTO Clinica VALUES (10, 'centro de geriatria', 'centro' );

iNSERT iNTO Consulta VALUES (1, '2010-05-06', '2010-05-06 13:00:00.0', 4, 1, 4);
iNSERT iNTO Consulta VALUES (2, '2010-05-06', '2010-05-06 15:00:00.0', 8, 1, 10 );
iNSERT iNTO Consulta VALUES (3, '2010-06-09', '2010-06-09 13:00:00.0', 2, 2, 2 );

iNSERT iNTO Consulta VALUES (4, '2010-06-09', '2010-06-09 09:30:00.0', 10, 2, 8 );

iNSERT iNTO Consulta VALUES (5, '2010-03-30', '2010-03-30 10:00:00.0', 1, 3, 1 );
iNSERT iNTO Consulta VALUES (6, '2010-03-30', '2010-03-30 21:30:00.0', 3, 4, 3 );
iNSERT iNTO Consulta VALUES (7, '2010-03-15', '2010-03-15 15:00:00.0', 5, 5, 5 );

iNSERT iNTO Consulta VALUES (8, '2010-03-21', '2010-03-21 18:00:00.0', 7, 6, 9 );
iNSERT iNTO Consulta VALUES(9, '2010-03-20', '2010-03-20 22:00:00.0', 9, 7, 7 );
iNSERT iNTO Consulta VALUES (10, '2010-03-20', '2010-03-20 22:00:00.0', 6, 8, 6 );

iNSERT iNTO Consulta VALUES (11,'2010-03-14', '2010-03-14 13:00:00.0', 10, 9, 8 );
iNSERT iNTO Consulta VALUES (12, '2010-03-30', '2010-03-30 09:00:00.0', 4, 10, 4 );

INSERT INTO MedicoEspecialidade VALUES (1,4 );
INSERT INTO MedicoEspecialidade VALUES (1, 8);
INSERT INTO MedicoEspecialidade VALUES (2, 2);
INSERT INTO MedicoEspecialidade VALUES (2, 10);
INSERT INTO MedicoEspecialidade VALUES (3, 1);
INSERT INTO MedicoEspecialidade VALUES (4, 3);
INSERT INTO MedicoEspecialidade VALUES (5, 5);
INSERT INTO MedicoEspecialidade VALUES (6, 7);
INSERT INTO MedicoEspecialidade VALUES (7, 9);
INSERT INTO MedicoEspecialidade VALUES (8, 6);
INSERT INTO MedicoEspecialidade VALUES (9,10);
INSERT INTO MedicoEspecialidade VALUES (10, 4);




INSERT INTO EspecialidadeClinica VALUES (1, 1);
INSERT INTO EspecialidadeClinica VALUES (2, 2);
INSERT INTO EspecialidadeClinica VALUES (3, 3);
INSERT INTO EspecialidadeClinica VALUES (4, 4);
INSERT INTO EspecialidadeClinica VALUES (5, 5);
INSERT INTO EspecialidadeClinica VALUES (6, 6);
INSERT INTO EspecialidadeClinica VALUES (7, 9);
INSERT INTO EspecialidadeClinica VALUES (8, 10);
INSERT INTO EspecialidadeClinica VALUES (9, 7);
INSERT INTO EspecialidadeClinica VALUES (10,8);





INSERT INTO MedicoClinica VALUES (1,4);
INSERT INTO MedicoClinica VALUES (1, 10);
INSERT INTO MedicoClinica VALUES (2, 2);
INSERT INTO MedicoClinica VALUES (2, 8);
INSERT INTO MedicoClinica VALUES (3, 1);
INSERT INTO MedicoClinica VALUES (4, 3);
INSERT INTO MedicoClinica VALUES (5, 5);
INSERT INTO MedicoClinica VALUES (6, 9);
INSERT INTO MedicoClinica VALUES (7, 7);
INSERT INTO MedicoClinica VALUES (8, 6);
INSERT INTO MedicoClinica VALUES (9, 8);
INSERT INTO MedicoClinica VALUES (10, 4);

INSERT INTO Clinica VALUES (11, 'Oftalmocare', 'São João');
INSERT INTO Clinica VALUES (12, 'Policlin', 'Nove de Julho');

INSERT INTO EspecialidadeClinica VALUES (7, 11);
INSERT INTO EspecialidadeClinica VALUES (9, 12);

INSERT INTO Medico VALUES (11, 'Guilherme', '99627-6597');
INSERT INTO Medico VALUES (12, 'Bruna', '99627-6596');

INSERT INTO MedicoEspecialidade VALUES (11, 9);
INSERT INTO MedicoEspecialidade VALUES (12, 7);

INSERT INTO MedicoClinica VALUES (11, 12);
INSERT INTO MedicoClinica VALUES (12, 11);

INSERT INTO Clinica VALUES (13, 'Vicentina Aranha', 'R Eng Prudente');

CREATE TABLE Folha_Pagto ( medico_cod int, consulta_cod int, valor float,
primary key(medico_cod, consulta_cod),
foreign key (medico_cod) references Medico(cod),
foreign key (consulta_cod) references Consulta(cod) );
INSERT INTO Folha_Pagto VALUES (1,1,100), (1,2,150),(2,3,100), (2, 4, 150), (3,5,50);