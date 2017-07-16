SELECT
    Location.locNo,
    Location.locName
FROM 
    Location, Facility
WHERE 
    Location.facNo = Facility.facNo AND 
    Facility.facName = 'Basketball arena';