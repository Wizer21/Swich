DROP TABLE IF EXISTS SWICHITEM;

CREATE TABLE IF NOT EXISTS SWICHITEM(
    id_item INT UNSIGNED AUTO_INCREMENT,
    nom_item TEXT,
    pachat_item INT,
    pvente_item INT,
    
    PRIMARY KEY(id_item)
);

INSERT INTO SWICHITEM VALUES(NULL, 'mug', '8','16');
INSERT INTO SWICHITEM VALUES(NULL, 'forch', '2','5');

SELECT * FROM SWICHITEM;