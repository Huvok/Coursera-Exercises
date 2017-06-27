CREATE TABLE Employee 
(
  empNo      CHAR(11)      NOT NULL,
  empName    VARCHAR2(30)  NOT NULL,
  department VARCHAR2(30)  NOT NULL,
  email      VARCHAR2(255) NOT NULL,
  phone      VARCHAR2(30)  NOT NULL,
  CONSTRAINT EmployeePK PRIMARY KEY (empNo)
);

Insert into EMPLOYEE (EMPNO,EMPNAME,DEPARTMENT,EMAIL,PHONE) values ('E100','Chuck Coordinator','Administration','chuck@colorado.edu','3-1111');
Insert into EMPLOYEE (EMPNO,EMPNAME,DEPARTMENT,EMAIL,PHONE) values ('E101','Mary Manager','Football','mary@colorado.edu','5-1111');
Insert into EMPLOYEE (EMPNO,EMPNAME,DEPARTMENT,EMAIL,PHONE) values ('E102','Sally Supervisor','Planning','sally@colorado.edu','3-2222');
Insert into EMPLOYEE (EMPNO,EMPNAME,DEPARTMENT,EMAIL,PHONE) values ('E103','Alan Administrator','Administration','alan@colorado.edu','3-3333');