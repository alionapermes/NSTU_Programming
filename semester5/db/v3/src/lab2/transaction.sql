BEGIN;

-- step_1 start
SAVEPOINT before_all;

ALTER TABLE
    "city"
ADD COLUMN
    code INTEGER;

SAVEPOINT add_city_code;
-- step_1 end

-- step_2 start
DROP TABLE IF EXISTS "pet";

CREATE TABLE "pet" (
    id   SERIAL,
    name VARCHAR NOT NULL
);
-- step_2 end

-- step_3 start
ROLLBACK TO add_city_code;
ROLLBACK TO before_all;
-- step_3 end

COMMIT;

