-- cd 'Desktop/Prog/C++ Qt/Swich/Swich'
-- mysql.exe -u Wizer -puseraccount swichdb
-- source SwichDB.sql

DROP TABLE IF EXISTS SWICHITEM;
DROP TABLE IF EXISTS SimonTable;

CREATE TABLE IF NOT EXISTS SWICHITEM(
    password_table TEXT,
    id_item INT UNSIGNED AUTO_INCREMENT,
    name_item TEXT,
    stock_item DOUBLE(10,3),
    buyp_item DOUBLE(10,3),
    sellp_item DOUBLE(10,3),
    
    stock_city1 DOUBLE(10,3),
    stock_city2 DOUBLE(10,3),
    stock_city3 DOUBLE(10,3),
    PRIMARY KEY(id_item)
);

INSERT INTO SWICHITEM (id_item, name_item, stock_item, buyp_item, sellp_item, stock_city1, stock_city2, stock_city3 ) VALUES(NULL, 'mug','0' ,'8','16', '0', '0','0');
INSERT INTO SWICHITEM (id_item, name_item, stock_item, buyp_item, sellp_item, stock_city1, stock_city2, stock_city3 ) VALUES(NULL, 'forch','0', '2','5', '0', '0','0');

CREATE TABLE IF NOT EXISTS SIMONTABLE(
    password_table TEXT,
    id_item INT UNSIGNED AUTO_INCREMENT,
    name_item TEXT,
    stock_item DOUBLE(10,3) NOT NULL,
    buyp_item DOUBLE(10,3),
    sellp_item DOUBLE(10,3),

    stock_city1 DOUBLE(10,3) NOT NULL,
    stock_city2 DOUBLE(10,3) NOT NULL,
    stock_city3 DOUBLE(10,3) NOT NULL,
    PRIMARY KEY(id_item)
);

INSERT INTO SIMONTABLE (password_table, id_item, name_item, buyp_item, sellp_item ) VALUES('motdepass' ,NULL, 'chaussette','8','16');
INSERT INTO SIMONTABLE (id_item, name_item, buyp_item, sellp_item) VALUES(NULL, 'forch','2','5');

CREATE TABLE IF NOT EXISTS SIMONTABLE$graph$(
    sellvolume_graph DOUBLE(10,3) NOT NULL,
    bank_graph DOUBLE(10,3) NOT NULL,
    tax_graph DOUBLE(10,3) NOT NULL,
    prd_graph DOUBLE(10,3) NOT NULL
);


--   queryDB.exec(QString("CREATE TABLE IF NOT EXISTS %1( "
--                        "banque_data DOUBLE(10, 3) NOT NULL "
--                        ");")
--                  .arg(name + "$bank$"));

--   queryDB.exec(QString("CREATE TABLE IF NOT EXISTS %1( "
--                        "level_factory INT(10, 3) NOT NULL, "
--                        "upgrade_factory INT(10, 3) NOT NULL "
--                        ");")
--                  .arg(name + "$factory$"));

--   queryDB.exec(QString("CREATE TABLE IF NOT EXISTS %1( "
--                        "name_employe INT(10, 3) NOT NULL, "
--                        "salary_employe INT(10, 3) NOT NULL, "
--                        "level_employe INT(10, 3) NOT NULL "
--                        ");")
--                  .arg(name + "$emplyoye$"));

SELECT password_table FROM SIMONTABLE;