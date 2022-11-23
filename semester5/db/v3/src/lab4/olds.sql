SELECT
    "driver".*
FROM
    "driver"
LEFT JOIN
    "city"
    ON "driver".city_id = "city".id
WHERE
    AGE("driver".birth_date)
        BETWEEN '30 years'::interval AND '50 years'::interval
    AND "city".name = 'Novosibirsk'
    AND "driver".wage > (
        SELECT
            AVG(wage)
        FROM
            "driver"
        LEFT JOIN
            "city"
            ON "driver".city_id = "city".id
        WHERE
            "city".name IN ('Omsk', 'Tomsk')
    );

