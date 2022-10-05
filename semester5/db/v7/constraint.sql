DROP ROLE IF EXISTS abobus;

CREATE ROLE
    abobus
WITH
    LOGIN
    PASSWORD 'onetwo';

DROP TYPE IF EXISTS PaymentMethod;

CREATE TYPE PaymentMethod AS ENUM('cash', 'cashless');

ALTER TABLE
    v7."order"
ADD COLUMN
    payment_method PaymentMethod;

ALTER TABLE
    v7."order"
DROP CONSTRAINT IF EXISTS ge100;

-- delivery had come
UPDATE
    v7."order"
SET
    amount = amount + 100
WHERE
    amount < 100;

ALTER TABLE
    v7."order"
ADD CONSTRAINT
    ge100
    CHECK (amount >= 100);

ALTER TABLE
    v7."order"
DROP CONSTRAINT IF EXISTS ge0;

ALTER TABLE
    v7."order"
ADD CONSTRAINT
    ge0
    CHECK (total_price >= 0.0);

ALTER TABLE
    v7."product_type"
    DROP CONSTRAINT IF EXISTS title_set;

-- packing products
UPDATE
    v7."product_type"
SET
    title = 'box'
WHERE
    title NOT IN ('ticket', 'box', 'note');

ALTER TABLE
    v7."product_type"
ADD CONSTRAINT
    title_set
    CHECK (title IN ('ticket', 'box', 'note'));

