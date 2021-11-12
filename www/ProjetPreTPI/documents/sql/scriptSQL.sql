#------------------------------------------------------------
#        Script MySQL.
#------------------------------------------------------------


#------------------------------------------------------------
# Table: t_arduino
#------------------------------------------------------------

CREATE TABLE t_arduino(
        ardMacAddress Varchar (12) NOT NULL
	,CONSTRAINT t_arduino_PK PRIMARY KEY (ardMacAddress)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: t_region
#------------------------------------------------------------

CREATE TABLE t_region(
        regId   Int  Auto_increment  NOT NULL ,
        regType Varchar (50) NOT NULL ,
        regName Varchar (50) NOT NULL
	,CONSTRAINT t_region_Idx INDEX (regName)
	,CONSTRAINT t_region_PK PRIMARY KEY (regId)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: t_record
#------------------------------------------------------------

CREATE TABLE t_record(
        recId         Int  Auto_increment  NOT NULL ,
        recDate       Datetime NOT NULL ,
        recType       Varchar (50) NOT NULL ,
        ardMacAddress Varchar (12) NOT NULL
	,CONSTRAINT t_record_Idx INDEX (recType)
	,CONSTRAINT t_record_PK PRIMARY KEY (recId)

	,CONSTRAINT t_record_t_arduino_FK FOREIGN KEY (ardMacAddress) REFERENCES t_arduino(ardMacAddress)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: linkedTo
#------------------------------------------------------------

CREATE TABLE linkedTo(
        regId         Int NOT NULL ,
        ardMacAddress Varchar (12) NOT NULL
	,CONSTRAINT linkedTo_PK PRIMARY KEY (regId,ardMacAddress)

	,CONSTRAINT linkedTo_t_region_FK FOREIGN KEY (regId) REFERENCES t_region(regId)
	,CONSTRAINT linkedTo_t_arduino0_FK FOREIGN KEY (ardMacAddress) REFERENCES t_arduino(ardMacAddress)
)ENGINE=InnoDB;

