-- cd 'Desktop/Prog/C++ Qt/Swich/Swich'
-- mysql.exe -u Wizer -puseraccount swichdb
-- source SwichDB.sql

DROP TABLE IF EXISTS SWICHITEM;

CREATE TABLE IF NOT EXISTS SWICHITEM(
    id_item INT UNSIGNED AUTO_INCREMENT,
    name_item TEXT,
    stock_item INT,
    buyp_item INT,
    sellp_item INT,
    
    PRIMARY KEY(id_item)
);

INSERT INTO SWICHITEM VALUES(NULL, 'mug','0' ,'8','16');
INSERT INTO SWICHITEM VALUES(NULL, 'forch','0', '2','5');

SELECT * FROM SWICHITEM;

UPDATE SWICHITEM SET stock_item = 5 WHERE id_item = 1;

SELECT * FROM SWICHITEM;