\c v7 abobus

DROP TABLE IF EXISTS cargo_container;
DROP TABLE IF EXISTS cargo_ship;

CREATE TABLE cargo_container(
    id       SERIAL,
    products ProductType[],

    PRIMARY KEY (id)
);

CREATE TABLE cargo_ship(
    id                 SERIAL,
    occupied_positions INTEGER[][],

    PRIMARY KEY (id)
);

