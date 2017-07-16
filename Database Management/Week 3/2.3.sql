SELECT
    EventRequest.eventNo,
    EventRequest.dateHeld,
    EventRequest.dateReq,
    EventRequest.estCost,
    EventRequest.status
FROM 
    EventRequest
INNER JOIN 
    EventPlan ON EventRequest.eventNo = EventPlan.eventNo
INNER JOIN 
    Employee ON EventPlan.empNo = Employee.empNo
INNER JOIN 
    Facility ON EventRequest.facNo = Facility.facNo
WHERE 
    Facility.facName = 'Basketball arena' AND 
    (EventRequest.dateHeld BETWEEN TO_DATE('2013-10-01', 'YYYY-MM-DD') AND TO_DATE('2013-12-31', 'YYYY-MM-DD')) AND
    Employee.empName = 'Mary Manager';