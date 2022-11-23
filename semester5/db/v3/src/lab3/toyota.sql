SELECT
    *
FROM
    "order"
WHERE
    distance = (
        SELECT
            MIN(distance)
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
    )
LIMIT 1;

