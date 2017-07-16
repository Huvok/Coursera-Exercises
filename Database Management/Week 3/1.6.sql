SELECT
    EventPlan.planNo,
    count(EventPlanLine.planNo),
    sum(EventPlanLine.numberFLD)
FROM 
    EventPlan, 
    EventPlanLine
WHERE 
    EventPlan.planNo = EventPlanLine.planNo
GROUP BY 
    EventPlan.planNo;