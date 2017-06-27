CREATE TABLE EventPlan 
(
  planNo   CHAR(8)  NOT NULL,
  eventNo   CHAR(8) NOT NULL,
  workDate DATE     NOT NULL,
  notes    VARCHAR2(200),
  activity CHAR(10) NOT NULL,
  empNo    CHAR(11),
  CONSTRAINT PK_EventPlan PRIMARY KEY (planNo),
  CONSTRAINT FK_EventRequest FOREIGN KEY (eventNo) REFERENCES EventRequest (eventNo),
  CONSTRAINT FK_Employee FOREIGN KEY (empNo) REFERENCES Employee (empNo)
);

Insert into EVENTPLAN (PLANNO,EVENTNO,WORKDATE,NOTES,ACTIVITY,EMPNO) values ('P100','E100',to_date('25-OCT-13','DD-MON-RR'),'Standard operation','Operation','E102');
Insert into EVENTPLAN (PLANNO,EVENTNO,WORKDATE,NOTES,ACTIVITY,EMPNO) values ('P101','E104',to_date('03-DEC-13','DD-MON-RR'),'Watch for gate crashers','Operation','E100');
Insert into EVENTPLAN (PLANNO,EVENTNO,WORKDATE,NOTES,ACTIVITY,EMPNO) values ('P102','E105',to_date('05-DEC-13','DD-MON-RR'),'Standard operation','Operation','E102');
Insert into EVENTPLAN (PLANNO,EVENTNO,WORKDATE,NOTES,ACTIVITY,EMPNO) values ('P103','E106',to_date('12-DEC-13','DD-MON-RR'),'Watch for seat switching','Operation',null);
Insert into EVENTPLAN (PLANNO,EVENTNO,WORKDATE,NOTES,ACTIVITY,EMPNO) values ('P104','E101',to_date('26-OCT-13','DD-MON-RR'),'Standard cleanup','Cleanup','E101');
Insert into EVENTPLAN (PLANNO,EVENTNO,WORKDATE,NOTES,ACTIVITY,EMPNO) values ('P105','E100',to_date('25-OCT-13','DD-MON-RR'),'Light cleanup','Cleanup','E101');
Insert into EVENTPLAN (PLANNO,EVENTNO,WORKDATE,NOTES,ACTIVITY,EMPNO) values ('P199','E102',to_date('10-DEC-13','DD-MON-RR'),'ABC','Operation','E101');
Insert into EVENTPLAN (PLANNO,EVENTNO,WORKDATE,NOTES,ACTIVITY,EMPNO) values ('P299','E101',to_date('26-OCT-13','DD-MON-RR'),null,'Operation','E101');
Insert into EVENTPLAN (PLANNO,EVENTNO,WORKDATE,NOTES,ACTIVITY,EMPNO) values ('P349','E106',to_date('12-DEC-13','DD-MON-RR'),null,'Setup','E101');
Insert into EVENTPLAN (PLANNO,EVENTNO,WORKDATE,NOTES,ACTIVITY,EMPNO) values ('P85','E100',to_date('25-OCT-13','DD-MON-RR'),'Standard operation','Cleanup','E102');
Insert into EVENTPLAN (PLANNO,EVENTNO,WORKDATE,NOTES,ACTIVITY,EMPNO) values ('P95','E101',to_date('26-OCT-13','DD-MON-RR'),'Extra security','Cleanup','E102');