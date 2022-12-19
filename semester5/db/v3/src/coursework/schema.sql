DROP SCHEMA IF EXISTS "public" CASCADE;
CREATE SCHEMA "public";

CREATE TABLE "city" (
    id   SERIAL,
    name VARCHAR NOT NULL UNIQUE,

    PRIMARY KEY (id)
);

CREATE TABLE "country" (
    id   SERIAL,
    name VARCHAR NOT NULL UNIQUE,

    PRIMARY KEY (id)
);

CREATE TABLE "producer" (
    id   SERIAL,
    name VARCHAR NOT NULL UNIQUE,

    PRIMARY KEY (id)
);

CREATE TABLE "provider" (
    id   SERIAL,
    name VARCHAR NOT NULL UNIQUE,

    PRIMARY KEY (id)
);

CREATE TABLE "customer" (
    id       SERIAL,
    fullname VARCHAR NOT NULL,
    age      INTEGER NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE "product_type" (
    id   SERIAL,
    name VARCHAR NOT NULL UNIQUE,

    PRIMARY KEY (id)
);

CREATE TABLE "product" (
    id          SERIAL,
    name        VARCHAR NOT NULL,
    type_id     INTEGER NOT NULL,
    released    DATE    NOT NULL,
    price       REAL    NOT NULL,
    city_id     INTEGER NOT NULL,
    country_id  INTEGER NOT NULL,
    producer_id INTEGER NOT NULL,
    provider_id INTEGER NOT NULL,

    CHECK(released <= NOW()),
    CHECK(price >= 0),

    FOREIGN KEY (type_id) REFERENCES "product_type"(id)
        ON DELETE SET NULL,

    FOREIGN KEY (city_id) REFERENCES "city"(id)
        ON DELETE SET NULL,

    FOREIGN KEY (country_id) REFERENCES "country"(id)
        ON DELETE SET NULL,

    FOREIGN KEY (provider_id) REFERENCES "provider"(id)
        ON DELETE SET NULL,

    PRIMARY KEY (id)
);

CREATE TABLE "sales" (
    id          SERIAL,
    date        TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    qty         INTEGER   NOT NULL DEFAULT 1,
    product_id  INTEGER   NOT NULL,
    customer_id INTEGER   NOT NULL,

    CHECK(date <= NOW()),
    CHECK(qty > 0),

    FOREIGN KEY (product_id) REFERENCES "product"(id)
        ON DELETE SET NULL,

    FOREIGN KEY (customer_id) REFERENCES "customer"(id)
        ON DELETE SET NULL,

    PRIMARY KEY (id)
);
