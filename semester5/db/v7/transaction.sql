BEGIN;

-- step_1 start
SAVEPOINT before_all;

ALTER TABLE
    v7.city
ADD COLUMN
    code INTEGER;

SAVEPOINT add_city_code;
-- step_1 end

-- step_2 start
DROP TABLE IF EXISTS v7.person;

CREATE TABLE v7.person (
    id   SERIAL,
    age  INTEGER NOT NULL,
    name VARCHAR NOT NULL
);
-- step_2 end

-- step_3 start
ROLLBACK TO add_city_code;
ROLLBACK TO before_all;
-- step_3 end

COMMIT;

