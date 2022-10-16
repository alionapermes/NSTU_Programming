CREATE TABLE "city" (
    id    SERIAL,
    title VARCHAR NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE "product_type" (
    id    SERIAL,
    title VARCHAR NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE "material" (
    id             SERIAL,
    title          VARCHAR NOT NULL,
    amount         INTEGER NOT NULL,
    supplies_price REAL    NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE "order" (
    id              SERIAL,
    product_id      INTEGER NOT NULL,
    product_type_id INTEGER NOT NULL,
    material_id     INTEGER NOT NULL,
    amount          INTEGER NOT NULL,
    total_price     REAL    NOT NULL,

    PRIMARY KEY (id),

    FOREIGN KEY (product_type_id) REFERENCES "product_type"(id),

    FOREIGN KEY (material_id) REFERENCES "material"(id)

    -- FOREIGN KEY (product_id) REFERENCES product(id)
);

CREATE TABLE "order_details" (
    order_id      INTEGER,
    city_id       INTEGER NOT NULL,
    customer_id   INTEGER NOT NULL,
    customer_name VARCHAR NOT NULL,

    PRIMARY KEY (order_id),

    FOREIGN KEY (order_id) REFERENCES "order"(id)
        ON DELETE CASCADE,

    FOREIGN KEY (city_id) REFERENCES "city"(id)
    
    -- FOREIGN KEY (customer_id) REFERENCES customer(id)
);

