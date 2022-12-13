DROP SCHEMA IF EXISTS "public" CASCADE;
CREATE SCHEMA "public";

CREATE TYPE "order_status" AS ENUM('success', 'failed');

CREATE TABLE "receiver" (
    id   SERIAL,
    name VARCHAR NOT NULL UNIQUE,

    PRIMARY KEY (id)
);

CREATE TABLE "supplier" (
    id   SERIAL,
    name VARCHAR NOT NULL UNIQUE,

    PRIMARY KEY (id)
);

CREATE TABLE "city" (
    id   SERIAL,
    name VARCHAR NOT NULL UNIQUE,

    PRIMARY KEY (id)
);

CREATE TABLE "car" (
    id       SERIAL,
    model    VARCHAR NOT NULL,
    km_price REAL    NOT NULL,
    number   CHAR(6),

    CHECK(km_price >= 0),

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
    married       BOOLEAN NOT NULL,
    wage          REAL    NOT NULL,

    CHECK(wage >= 0),
    CHECK(birth_date <= NOW()),
    CHECK(driving_since <= NOW()),
    CHECK(birth_date < driving_since),

    FOREIGN KEY (car_id) REFERENCES car(id)
        ON DELETE SET NULL,

    FOREIGN KEY (city_id) REFERENCES city(id)
        ON DELETE CASCADE,

    PRIMARY KEY (id)
);

CREATE TABLE "order" (
    id                  SERIAL,
    date                TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    distance            REAL      NOT NULL,
    supplier_id         INTEGER   NOT NULL,
    receiver_id         INTEGER   NOT NULL,
    driver_id           INTEGER   NOT NULL,
    total_price         REAL      NOT NULL,
    departure_city_id   INTEGER   NOT NULL,
    destination_city_id INTEGER   NOT NULL,
    downtime            INTERVAL,
    status              order_status,

    CHECK(date <= NOW()),
    CHECK(distance >= 0.0),
    CHECK(total_price >= 0.0),
    CHECK(downtime > '0 seconds'),

    FOREIGN KEY (supplier_id) REFERENCES supplier(id)
        ON DELETE SET NULL,

    FOREIGN KEY (receiver_id) REFERENCES receiver(id)
        ON DELETE SET NULL,

    FOREIGN KEY (driver_id) REFERENCES driver(id)
        ON DELETE SET NULL,

    FOREIGN KEY (departure_city_id) REFERENCES city(id)
        ON DELETE SET NULL,

    FOREIGN KEY (destination_city_id) REFERENCES city(id)
        ON DELETE SET NULL,

    PRIMARY KEY (id)
);

SET timezone = 'Asia/Novosibirsk';

