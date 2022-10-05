DROP SCHEMA IF EXISTS v7 CASCADE;

CREATE SCHEMA v7;

CREATE TABLE v7.city (
    id    SERIAL,
    title VARCHAR NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE v7.product_type (
    id    SERIAL,
    title VARCHAR NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE v7.material (
    id             SERIAL,
    title          VARCHAR NOT NULL,
    amount         INTEGER NOT NULL,
    supplies_price REAL    NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE v7.order (
    id              SERIAL,
    product_id      INTEGER NOT NULL,
    product_type_id INTEGER NOT NULL,
    material_id     INTEGER NOT NULL,
    amount          INTEGER NOT NULL,
    total_price     REAL    NOT NULL,

    PRIMARY KEY (id),

    FOREIGN KEY (product_type_id) REFERENCES v7.product_type(id),

    FOREIGN KEY (material_id) REFERENCES v7.material(id)

    -- FOREIGN KEY (product_id) REFERENCES v7.product(id)
);

CREATE TABLE v7.order_details (
    order_id      INTEGER,
    city_id       INTEGER NOT NULL,
    customer_id   INTEGER NOT NULL,
    customer_name VARCHAR NOT NULL,

    PRIMARY KEY (order_id),

    FOREIGN KEY (order_id) REFERENCES v7.order(id)
        ON DELETE CASCADE,

    FOREIGN KEY (city_id) REFERENCES v7.city(id)
    
    -- FOREIGN KEY (customer_id) REFERENCES v7.customer(id)
);

