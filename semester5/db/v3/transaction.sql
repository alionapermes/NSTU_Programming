BEGIN;

-- step_1 start
SAVEPOINT before_all;

ALTER TABLE
    v3.city
ADD COLUMN
    code INTEGER;

SAVEPOINT add_city_code;
-- step_1 end

-- step_2 start
DROP TABLE IF EXISTS v3.pet;

CREATE TABLE v3.pet (
    id   SERIAL,
    name VARCHAR NOT NULL
);
-- step_2 end

-- step_3 start
ROLLBACK TO add_city_code;
ROLLBACK TO before_all;
-- step_3 end

COMMIT;

