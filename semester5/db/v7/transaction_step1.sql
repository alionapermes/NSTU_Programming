BEGIN;

SAVEPOINT before_all;

ALTER TABLE
    v7.city
ADD COLUMN
    code INTEGER;

SAVEPOINT add_city_code;

