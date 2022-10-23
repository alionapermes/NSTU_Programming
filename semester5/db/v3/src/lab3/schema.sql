DROP TABLE IF EXISTS "order";
DROP TABLE IF EXISTS "driver";
DROP TABLE IF EXISTS "city";
DROP TABLE IF EXISTS "car";

CREATE TABLE "city" (
    id   SERIAL,
    name VARCHAR NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE "car" (
    id       SERIAL,
    model    VARCHAR NOT NULL,
    km_price REAL    NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE "driver" (
    id            SERIAL,
    name          VARCHAR NOT NULL,
    surname       VARCHAR NOT NULL,
    birth_date    DATE    NOT NULL,
    driving_since DATE    NOT NULL,
    car_id        INTEGER NOT NULL,
    city_id       INTEGER NOT NULL,

    PRIMARY KEY (id),

    FOREIGN KEY (car_id) REFERENCES car(id),

    FOREIGN KEY (city_id) REFERENCES city(id)
        ON DELETE CASCADE
);

CREATE TABLE "order" (
    id          SERIAL,
    date        TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    distance    REAL      NOT NULL,
    driver_id   INTEGER   NOT NULL,
    total_price REAL      NOT NULL,

    PRIMARY KEY (id),

    FOREIGN KEY (driver_id) REFERENCES driver(id)
);

SET timezone = 'Asia/Novosibirsk';

