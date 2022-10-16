UPDATE
    "cargo_container"
SET
    products = '{"box", "box", "box"}'
WHERE
    id = 1;

UPDATE
    "cargo_container"
SET
    products[2:3] = '{"note", "note"}'
WHERE
    id = 2;

