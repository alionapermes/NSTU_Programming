SELECT
    *
FROM
    "order"
WHERE
    distance = (SELECT MAX(distance) FROM "order")
LIMIT 1;

