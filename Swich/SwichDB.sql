-- cd 'Desktop/Prog/C++ Qt/Swich/Swich'
-- mysql.exe -u Wizer -puseraccount swichdb
-- source SwichDB.sql

DROP TABLE IF EXISTS SWICH;
DROP TABLE IF EXISTS SWICH$graph$;
DROP TABLE IF EXISTS SWICH$bank$;
DROP TABLE IF EXISTS SWICH$factory$;
DROP TABLE IF EXISTS SWICH$employe$;

CREATE TABLE IF NOT EXISTS SWICH(
    id_item INT UNSIGNED AUTO_INCREMENT,
    name_item TEXT,
    stock_item DOUBLE(10,3) DEFAULT '0',
    buyp_item DOUBLE(10,3),
    sellp_item DOUBLE(10,3),
    
    stock_city1 DOUBLE(10,3) DEFAULT '0',
    stock_city2 DOUBLE(10,3) DEFAULT '0',
    stock_city3 DOUBLE(10,3) DEFAULT '0',
    PRIMARY KEY(id_item)
);

CREATE TABLE IF NOT EXISTS SWICH$graph$(
    sellvolume_graph DOUBLE(10,3) NOT NULL,
    bank_graph DOUBLE(10,3) NOT NULL,
    tax_graph DOUBLE(10,3) NOT NULL,
    prd_graph DOUBLE(10,3) NOT NULL
);

CREATE TABLE IF NOT EXISTS SWICH$bank$(
    password_table TEXT,
    banque_data DOUBLE(10,3)
);

CREATE TABLE IF NOT EXISTS SWICH$factory$(
    level_factory INT NOT NULL,
    upgrade_factory INT NOT NULL
);

CREATE TABLE IF NOT EXISTS SWICH$employe$(
    name_employe TEXT NOT NULL,
    salary_employe INT NOT NULL,
    level_employe INT NOT NULL,
    commercial_employe INT NOT NULL
);

INSERT INTO SWICH (id_item, name_item, buyp_item, sellp_item ) VALUES(NULL, 'mug','8','16');
INSERT INTO SWICH (id_item, name_item, buyp_item, sellp_item ) VALUES(NULL, 'forch','2','5');
INSERT INTO SWICH$graph$ VALUES('0','1203','153','135');
INSERT INTO SWICH$bank$ (banque_data) VALUE ('5430');
INSERT INTO SWICH$factory$ VALUES('1','750');
INSERT INTO SWICH$factory$ VALUES('0','670');
INSERT INTO SWICH$factory$ VALUES('0','780');


SELECT * FROM SWICH;
SELECT * FROM SWICH$graph$;
SELECT * FROM SWICH$bank$;
SELECT * FROM SWICH$factory$;
SELECT * FROM SWICH$employe$;