SELECT
    EventPlanLine.planNo,
    EventPlanLine.lineNo,
    EventPlanLine.numberFLD,
    EventPlanLine.timeStart,
    EventPlanLine.timeEnd,
    Location.locName,
    ResourceTbl.resName
FROM 
    EventPlanLine
INNER JOIN EventPlan ON EventPlanLine.planNo = EventPlan.planNo
INNER JOIN Location ON EventPlanLine.locNo = Location.locNo
INNER JOIN ResourceTbl ON EventPlanLine.resNo = ResourceTbl.resNo
INNER JOIN Facility ON Location.facNo = Facility.facNo
WHERE 
    Facility.facName = 'Basketball arena' AND 
    EventPlan.activity = 'Operation' AND
    (EventPlan.workDate BETWEEN TO_DATE('2013-10-01', 'YYYY-MM-DD') AND TO_DATE('2013-12-31', 'YYYY-MM-DD'))
ORDER BY 
    EventPlanLine.planNo;