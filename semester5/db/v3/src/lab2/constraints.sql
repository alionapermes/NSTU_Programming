ALTER TABLE
    "order"
DROP CONSTRAINT IF EXISTS
    greater_or_equal_100;

ALTER TABLE
    "order"
ADD CONSTRAINT
    greater_or_equal_100
    CHECK (total_price >= 100.0);

ALTER TABLE
    "driver"
DROP CONSTRAINT IF EXISTS
    age_older21;

ALTER TABLE
    "driver"
ADD CONSTRAINT
    age_older21
    CHECK (AGE(birth_date) >= '21 years'::interval);

ALTER TABLE
    "driver"
DROP CONSTRAINT IF EXISTS
    driving_older3;

ALTER TABLE
    "driver"
ADD CONSTRAINT
    driving_older3
    CHECK (AGE(driving_since) >= '3 years'::interval);

ALTER TABLE
    "order"
DROP CONSTRAINT IF EXISTS
    non_negative;

ALTER TABLE
    "order"
ADD CONSTRAINT
    non_negative
    CHECK (distance >= 0.0);

