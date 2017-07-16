SELECT
    EventNo,
    DateAuth,
    Status
FROM 
    EventRequest
WHERE 
    (Status = 'Approved' OR Status = 'Denied') AND 
    DateAuth BETWEEN TO_DATE('2013-07-01','YYYY-MM-DD') AND TO_DATE('2013-07-31','YYYY-MM-DD');