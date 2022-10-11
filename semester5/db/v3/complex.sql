CREATE TABLE v3.complex AS (
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
        v3.order AS "order"
    LEFT JOIN
        v3.driver AS "driver"
        ON "order".driver_id = driver.id
    LEFT JOIN
        v3.city AS "city"
        ON "driver".city_id = city.id
    LEFT JOIN
        v3.car AS "car"
        ON "driver".car_id = car.id
);

