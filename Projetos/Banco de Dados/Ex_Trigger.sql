CREATE DATABASE ex_trigger;

CREATE TABLE DEPARTAMENTO (Dnum INT, nome VARCHAR(10), TotalSal FLOAT);
ALTER TABLE DEPARTAMENTO ADD PRIMARY KEY (Dnum);

CREATE TABLE EMPREGADO (id INT, nome VARCHAR(10), salario FLOAT, dnum INT);
ALTER TABLE EMPREGADO ADD PRIMARY KEY (id);
ALTER TABLE EMPREGADO ADD FOREIGN KEY(Dnum) REFERENCES DEPARTAMENTO(Dnum);

INSERT INTO DEPARTAMENTO VALUES(1, 'computação', 0);
INSERT INTO DEPARTAMENTO VALUES(2, 'matemática', 0); 

CREATE TRIGGER tgr AFTER INSERT 
ON EMPREGADO
FOR EACH ROW
UPDATE DEPARTAMENTO SET TotalSal = TotalSal + NEW.salario
WHERE Dnum = NEW.dnum;

INSERT INTO EMPREGADO VALUES(1, 'Guilherme', 15000, 1);
INSERT INTO EMPREGADO VALUES(2, 'Bruna', 20000, 1);
INSERT INTO EMPREGADO VALUES(3, 'Jefferson', 8000, 2);

SELECT nome, TotalSal
FROM DEPARTAMENTO;
#Saída:
# computação | 35000
# matemática | 8000
#Saída Correta!


delimiter //
CREATE TRIGGER tgr2 AFTER UPDATE
ON EMPREGADO
FOR EACH ROW
BEGIN
	UPDATE DEPARTAMENTO SET TotalSal = TotalSal + NEW.salario
	WHERE Dnum = NEW.dnum;
    UPDATE DEPARTAMENTO SET TotalSal = TotalSal - OLD.salario
    WHERE Dnum = OLD.dnum;
END;

// delimiter ;

UPDATE EMPREGADO 
SET dnum = 2
WHERE id = 2; 

SELECT nome, TotalSal
FROM DEPARTAMENTO;
#Saída:
# computação | 15000
# matemática | 28000
#Saída Correta!

CREATE TABLE FolhaPagto (id INT auto_increment, salario FLOAT, codemp INT,
primary key(id));
ALTER TABLE FolhaPagto ADD FOREIGN KEY(codemp) REFERENCES empregado(id);

DROP TRIGGER tgr;

CREATE TRIGGER tgr3 AFTER INSERT 
ON EMPREGADO
FOR EACH ROW
INSERT INTO FolhaPagto (salario, codemp) VALUES (NEW.salario, NEW.id);

INSERT INTO EMPREGADO VALUES(4, 'Jorge', 13000, 1);

SELECT f.id, e.nome, f.salario 
FROM EMPREGADO e,
	 FolhaPagto f
WHERE e.nome = 'Jorge';
#Saída:
# 1 | Jorge | 13000
#Saída Correta!