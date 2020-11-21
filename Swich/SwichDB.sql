-- cd 'Desktop/Prog/C++ Qt/Swich/Swich'
-- mysql.exe -u Wizer -puseraccount swichdb
-- source SwichDB.sql

DROP TABLE IF EXISTS SWICHITEM;
DROP TABLE IF EXISTS SimonTable;

CREATE TABLE IF NOT EXISTS SWICHITEM(
    password_table INT,
    id_item INT UNSIGNED AUTO_INCREMENT,
    name_item TEXT,
    stock_item DOUBLE(10,3),
    buyp_item DOUBLE(10,3),
    sellp_item DOUBLE(10,3),
    
    PRIMARY KEY(id_item)
);

INSERT INTO SWICHITEM (id_item, name_item, stock_item, buyp_item, sellp_item ) VALUES(NULL, 'mug','0' ,'8','16');
INSERT INTO SWICHITEM (id_item, name_item, stock_item, buyp_item, sellp_item ) VALUES(NULL, 'forch','0', '2','5');

CREATE TABLE IF NOT EXISTS SIMONTABLE(
    password_table INT,
    id_item INT UNSIGNED AUTO_INCREMENT,
    name_item TEXT,
    stock_item DOUBLE(10,3),
    buyp_item DOUBLE(10,3),
    sellp_item DOUBLE(10,3),
    
    PRIMARY KEY(id_item)
);

INSERT INTO SIMONTABLE (id_item, name_item, stock_item, buyp_item, sellp_item ) VALUES(NULL, 'chaussette','2.2' ,'8','16');
INSERT INTO SIMONTABLE (id_item, name_item, stock_item, buyp_item, sellp_item ) VALUES(NULL, 'forch','0', '2','5');

--SELECT * FROM SWICHITEM;

SELECT * FROM SIMONTABLE;
