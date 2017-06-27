CREATE TABLE Customer 
(
  custNo   CHAR(8)       NOT NULL,
  custName VARCHAR2(30)  NOT NULL,
  address  VARCHAR2(50)  NOT NULL,
  internal CHAR(1)       NOT NULL,
  contact  VARCHAR2(50)  NOT NULL,
  phone    VARCHAR2(30)  NOT NULL,
  city     VARCHAR2(30)  NOT NULL,
  zip      VARCHAR2(10)  NOT NULL,
  state    VARCHAR2(2)   NOT NULL,
  CONSTRAINT CustomerPk PRIMARY KEY (custNo)
);

Insert into CUSTOMER (CUSTNO,CUSTNAME,ADDRESS,INTERNAL,CONTACT,PHONE,CITY,STATE,ZIP) values ('C100','Football','Box 352200','Y','Mary Manager','6857100','Boulder','CO','80309');
Insert into CUSTOMER (CUSTNO,CUSTNAME,ADDRESS,INTERNAL,CONTACT,PHONE,CITY,STATE,ZIP) values ('C101','Men''s Basketball','Box 352400','Y','Sally Supervisor','5431700','Boulder','CO','80309');
Insert into CUSTOMER (CUSTNO,CUSTNAME,ADDRESS,INTERNAL,CONTACT,PHONE,CITY,STATE,ZIP) values ('C103','Baseball','Box 352020','Y','Bill Baseball','5431234','Boulder','CO','80309');
Insert into CUSTOMER (CUSTNO,CUSTNAME,ADDRESS,INTERNAL,CONTACT,PHONE,CITY,STATE,ZIP) values ('C104','Women''s Softball','Box 351200','Y','Sue Softball','5434321','Boulder','CO','80309');
Insert into CUSTOMER (CUSTNO,CUSTNAME,ADDRESS,INTERNAL,CONTACT,PHONE,CITY,STATE,ZIP) values ('C105','High School Football','123 AnyStreet','N','Coach Bob','4441234','Louisville','CO','80027');