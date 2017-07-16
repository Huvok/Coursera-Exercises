SELECT
    EventRequest.eventNo,
    EventRequest.dateHeld,
    count(*) AS eventPlanCount
FROM 
    EventRequest
INNER JOIN 
    EventPlan ON EventRequest.eventNo = EventPlan.eventNo
WHERE 
    EventPlan.workDate BETWEEN TO_DATE('2013-12-01', 'YYYY-MM-DD') AND TO_DATE('2013-12-31', 'YYYY-MM-DD')
GROUP BY 
    EventRequest.eventNo,
    EventRequest.dateHeld
HAVING 
    count(*) > 1;