WITH
    payments(methods, num) AS (
        VALUES ('[0:1]={cash, cashless}'::PaymentMethod[], 2)
    )
UPDATE
    "order"
SET
    payment_method = methods[floor(random() * num)]
FROM
    payments
WHERE
    payment_method IS NULL;

SELECT
    *
FROM
    "order"
LEFT JOIN
    "product_type"
    ON "product_type".id = product_type_id
WHERE
    "product_type".title = 'ticket'
ORDER BY
    total_price ASC
LIMIT 1;

SELECT
    *
FROM
    "order"
LEFT JOIN
    "product_type"
    ON "product_type".id = product_type_id
WHERE
    "product_type".title = 'note'
ORDER BY
    total_price DESC
LIMIT 1;

SELECT
    AVG(total_price) AS avg_cash
FROM
    "order"
WHERE
    payment_method = 'cash';

SELECT
    AVG(total_price) AS avg_cashless
FROM
    "order"
WHERE
    payment_method = 'cashless';

SELECT
    SUM(total_price)
FROM
    "order"
LEFT JOIN
    "order_details"
    ON "order".id = "order_details".order_id
LEFT JOIN
    "city"
    ON  "city".id = "order_details".city_id
WHERE
    "city".title = 'Moscow';

