SELECT
    "driver".*
FROM
    "driver"
LEFT JOIN
    "order"
    ON "driver".id = "order".driver_id
WHERE
    AGE("driver".birth_date) > (
        SELECT
            AVG(AGE(birth_date))
        FROM
            "driver"
        WHERE
            married = false
    ) AND "driver".id IN (
        SELECT
            driver_id
        FROM
            "order"
        WHERE
            AGE(date) <= '3 months'::interval
        GROUP BY
            driver_id
        HAVING
            SUM(total_price) > 20000
    )
GROUP BY
    "driver".id;

