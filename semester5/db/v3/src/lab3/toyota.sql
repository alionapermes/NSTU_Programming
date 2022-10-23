SELECT
    "order".*
FROM
    "order"
LEFT JOIN
    "driver"
    ON "order".driver_id = "driver".id
LEFT JOIN
    "car"
    ON "driver".car_id = "car".id
WHERE
    "car".model LIKE '%Toyota%'
ORDER BY
    "order".distance ASC
LIMIT 1;

