CREATE TABLE Facility 
(
  facNo   CHAR(11)     NOT NULL,
  facName VARCHAR2(30) NOT NULL,
  CONSTRAINT FacilityPK PRIMARY KEY (facNo)
);

Insert into FACILITY (FACNO,FACNAME) values ('F100','Football stadium');
Insert into FACILITY (FACNO,FACNAME) values ('F101','Basketball arena');
Insert into FACILITY (FACNO,FACNAME) values ('F102','Baseball field');
Insert into FACILITY (FACNO,FACNAME) values ('F103','Recreation room');