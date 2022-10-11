ALTER TABLE
    v3."order"
DROP COLUMN IF EXISTS
    total_price;

ALTER TABLE
    v3."order"
ADD COLUMN IF NOT EXISTS
    total_price REAL DEFAULT 100.0
    CONSTRAINT
        greater_or_equal_100
        CHECK (total_price >= 100.0);

ALTER TABLE
    v3."driver"
DROP CONSTRAINT IF EXISTS
    age_older21;

UPDATE
    v3."driver"
SET
    birth_date = birth_date - '21 years'::interval
WHERE
    AGE(birth_date) < '21 years'::interval;

ALTER TABLE
    v3."driver"
ADD CONSTRAINT
    age_older21
    CHECK (AGE(birth_date) >= '21 years'::interval);

ALTER TABLE
    v3."driver"
DROP CONSTRAINT IF EXISTS
    driving_older3;

UPDATE
    v3."driver"
SET
    driving_since = driving_since - '3 years'::interval
WHERE
    AGE(driving_since) < '3 years'::interval;

ALTER TABLE
    v3."driver"
ADD CONSTRAINT
    driving_older3
    CHECK (AGE(driving_since) >= '3 years'::interval);

ALTER TABLE
    v3."order"
DROP CONSTRAINT IF EXISTS
    non_negative;

ALTER TABLE
    v3."order"
ADD CONSTRAINT
    non_negative
    CHECK (distance >= 0.0);

