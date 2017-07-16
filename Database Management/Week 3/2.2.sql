SELECT
    EventPlan.planNo,
    EventPlan.eventNo,
    EventPlan.workDate,
    EventPlan.activity
FROM 
    EventPlan
INNER JOIN EventRequest ON EventPlan.eventNo = EventRequest.eventNo
INNER JOIN Facility ON EventRequest.facNo = Facility.facNo
WHERE 
    Facility.facName = 'Basketball arena' AND 
    EventPlan.workDate BETWEEN TO_DATE('2013-12-01', 'YYYY-MM-DD') AND TO_DATE('2013-12-31', 'YYYY-MM-DD');