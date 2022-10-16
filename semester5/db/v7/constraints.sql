\c v7 abobus

ALTER TABLE
    "order"
ADD COLUMN IF NOT EXISTS
    payment_method PaymentMethod;

ALTER TABLE
    "order"
DROP CONSTRAINT IF EXISTS
    ge100;

-- delivery had come
UPDATE
    "order"
SET
    amount = amount + 100
WHERE
    amount < 100;

ALTER TABLE
    "order"
ADD CONSTRAINT
    ge100
    CHECK (amount >= 100);

ALTER TABLE
    "order"
DROP CONSTRAINT IF EXISTS
    ge0;

ALTER TABLE
    "order"
ADD CONSTRAINT
    ge0
    CHECK (total_price >= 0.0);

ALTER TABLE
    "product_type"
DROP CONSTRAINT IF EXISTS
    title_set;

-- packing products
WITH
    types(names, num) AS (
        VALUES ('[0:2]={note,ticket,box}'::ProductType[], 3)
    )
UPDATE
    "product_type"
SET
    title = names[floor(random() * num)]
FROM
    types
WHERE
    title NOT IN ('ticket', 'box', 'note');

ALTER TABLE
    "product_type"
ALTER COLUMN
    title TYPE ProductType USING title::ProductType;

