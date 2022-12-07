WITH "driver_income" (driver_id, income) AS (
    SELECT
      driver_id, SUM(total_price) AS income
    FROM
      "order"
    WHERE
      AGE(date) <= '1 week'::interval
    GROUP BY
      driver_id
)
SELECT
  "driver".*, "driver_income".income
FROM
  "driver_income"
LEFT JOIN
  "driver"
  ON "driver".id = "driver_income".driver_id;

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
  EXTRACT('year' FROM AGE(driving_since, birth_date)) = 18;

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
  EXTRACT('year' FROM AGE("driver".driving_since, "driver".birth_date))
    BETWEEN 15 AND 20
  AND ("car".model = 'Toyota' OR "car".model = 'Ford')
  AND ("city".name = 'Kemerovo' OR "city".name = 'Krasnoyarsk');

