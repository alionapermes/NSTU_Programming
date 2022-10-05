DROP TABLE IF EXISTS v7.person;

CREATE TABLE v7.person (
    id   SERIAL,
    age  INTEGER NOT NULL,
    name VARCHAR NOT NULL
);

COMMIT;

