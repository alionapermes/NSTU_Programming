SELECT
    SUM("order".total_price)
FROM
    "order"
LEFT JOIN
    "driver"
    ON "order".driver_id = "driver".id
LEFT JOIN
    "city"
    ON "driver".city_id = "city".id
WHERE
    "city".name = 'Saint Petersburg';

