SELECT
    "driver".*
FROM
    "driver"
LEFT JOIN
    "order"
    ON "driver".id = "order".driver_id
WHERE
    AGE("driver".birth_date) < '30 years'::interval
    AND "driver".wage > (
        SELECT
            AVG(wage)
        FROM
            "driver"
        WHERE
            (DATE_PART('year', driving_since) - DATE_PART('year', birth_date))
            BETWEEN 18 AND 20
    )
GROUP BY
    "driver".id;

