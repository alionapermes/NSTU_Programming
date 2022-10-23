DROP TABLE IF EXISTS "complex";

CREATE TABLE "complex" AS (
    SELECT
        "order".id                        AS order_id,
        "order".date                      AS date,
        "order".distance                  AS distance,
        "car".km_price                    AS fare,
        "car".km_price * "order".distance AS total_price,
        "driver".surname                  AS driver_surname,
        "city".name                       AS driver_city,
        "car".model                       AS car_model
    FROM
        "order"
    LEFT JOIN
        "driver"
        ON "order".driver_id = "driver".id
    LEFT JOIN
        "city"
        ON "driver".city_id = "city".id
    LEFT JOIN
        "car"
        ON "driver".car_id = "car".id
);

