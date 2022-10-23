SELECT
    COUNT(*) AS driving_over_10
FROM
    "driver"
WHERE
    AGE("driver".driving_since) > '10 years'::interval;

