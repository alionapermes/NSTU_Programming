WITH recent(driver_id, total) AS (
    SELECT
        driver_id, SUM(total_price) AS total
    FROM
        "order"
    WHERE
        AGE(date) <= '3 months'::interval
    GROUP BY
        driver_id
)
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
            recent
        WHERE
            total > 20000
    )
GROUP BY
    "driver".id;

