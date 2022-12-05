-- CREATE OR REPLACE FUNCTION driving_experience

SELECT
  "driver".*,
  SUM("order".total_price) AS "income"
FROM
  "driver"
LEFT JOIN
  "order"
  ON "order".driver_id = "driver".id
GROUP BY
  "driver".id;

SELECT
  *
FROM
  "driver"
WHERE
  "driver".id IN (
    SELECT
      "order".driver_id
    FROM
      "order"
    WHERE
      AGE("order".date) <= '1 day'::interval
    GROUP BY
      "order".driver_id
    HAVING
      SUM("order".total_price) > 1000
  )
  AND AGE("driver".birth_date) < '25 years'::interval;

SELECT
  *
FROM
  "driver"
WHERE
  AGE(driving_since, birth_date) = '18 years'::interval;

SELECT
  *
FROM
  "driver"
WHERE
  married = true;

SELECT
  "driver".*
FROM
  "driver"
LEFT JOIN
  "car"
  ON "driver".car_id = "car".id
LEFT JOIN
  "city"
  ON "driver".city_id = "city".id
WHERE
  AGE("driver".driving_since, "driver".birth_date) BETWEEN
    '15 years'::interval AND '20 years'::interval
  AND ("car".model = 'Toyota' OR "car".model = 'Ford')
  AND ("city".name = 'Kemerovo' OR "city".name = 'Krasnoyarsk');

