-- cd 'Desktop/Prog/C++ Qt/Swich/Swich'
-- mysql.exe -u Wizer -puseraccount swichdb
-- source SwichDB.sql

DROP TABLE IF EXISTS SWICHITEM;
DROP TABLE IF EXISTS SimonTable;

CREATE TABLE IF NOT EXISTS SWICHITEM(
    id_item INT UNSIGNED AUTO_INCREMENT,
    name_item TEXT,
    stock_item DOUBLE(10,3),
    buyp_item DOUBLE(10,3),
    sellp_item DOUBLE(10,3),
    
    PRIMARY KEY(id_item)
);

INSERT INTO SWICHITEM VALUES(NULL, 'mug','0' ,'8','16');
INSERT INTO SWICHITEM VALUES(NULL, 'forch','0', '2','5');

CREATE TABLE IF NOT EXISTS SIMONTABLE(
    id_item INT UNSIGNED AUTO_INCREMENT,
    name_item TEXT,
    stock_item DOUBLE(10,3),
    buyp_item DOUBLE(10,3),
    sellp_item DOUBLE(10,3),
    
    PRIMARY KEY(id_item)
);

INSERT INTO SIMONTABLE VALUES(NULL, 'chaussette','2.2' ,'8','16');
INSERT INTO SIMONTABLE VALUES(NULL, 'forch','0', '2','5');

--SELECT * FROM SWICHITEM;

SELECT * FROM SIMONTABLE;
