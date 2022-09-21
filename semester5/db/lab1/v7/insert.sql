INSERT INTO
    lab_1v7.product_type
    (title)
VALUES
    ('note'),
    ('box'),
    ('ticket'),
    ('laptop'),
    ('glass'),
    ('headphones'),
    ('toy'),
    ('bag'),
    ('door'),
    ('lamp');

INSERT INTO
    lab_1v7.city
    (name)
VALUES
    ('Novosibirsk'),
    ('Berdsk'),
    ('Tomsk'),
    ('Novokuznetsk'),
    ('Kemerovo'),
    ('Saint Petersburg'),
    ('Moscow'),
    ('Kaliningrad'),
    ('Belgorod'),
    ('Ekaterinburg');

INSERT INTO
    lab_1v7.material
    (title, amount, supplies_price)
VALUES
    ('leather',   412, 8880),
    ('plastic',   123, 9998),
    ('paper',     321, 7779),
    ('glass',     214, 7896),
    ('wood',      111, 9877),
    ('metal',     222, 7863),
    ('cardboard', 333, 9674),
    ('tissue',    444, 5672),
    ('linen',     555, 3521),
    ('silks',     666, 1535);

INSERT INTO
    lab_1v7.order
    (product_id, product_type_id, material_id, amount, total_price)
VALUES
    (1,  1,  1,  12, 3948),
    (2,  2,  2,  32, 1397),
    (3,  3,  3,  13, 1342),
    (4,  4,  4,  31, 5661),
    (5,  5,  5,  23, 5311),
    (6,  6,  6,  21, 6573),
    (7,  7,  7,  44, 8739),
    (8,  8,  8,  33, 3547),
    (9,  9,  9,  22, 3577),
    (10, 10, 10, 11, 6532);

INSERT INTO
    lab_1v7.order_details
    (order_id, city_id, customer_id, customer_name)
VALUES
    (1,  1,  1,  'aboba'),
    (2,  2,  2,  'buba'),
    (3,  3,  3,  'biba'),
    (4,  4,  4,  'lupa'),
    (5,  5,  5,  'pupa'),
    (6,  6,  6,  'vupsane'),
    (7,  7,  7,  'pupsane'),
    (8,  8,  8,  'moontick'),
    (9,  9,  9,  'shniyok'),
    (10, 10, 10, 'meela');

