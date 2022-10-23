INSERT INTO
    "city"
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
    "car"
    (model, km_price)
VALUES
    ('Subaru R2',             30),
    ('Kia Optima',            35),
    ('Volkswagen Jetta',      33),
    ('LADA Classic',          50),
    ('Toyota Vista',          31),
    ('Nissan Cube',           24),
    ('Honda City',            29),
    ('Nissan Wingroad',       26),
    ('Mercedes Menz A-Class', 25),
    ('Nissan Sentra',         28);

INSERT INTO
    "driver"
    (name, surname, birth_date, car_id, city_id, driving_since)
VALUES
    ('Vladislave', 'Kheynov',    '2000-12-17', 1,  1,  '2019-06-06'),
    ('Galina',     'Sidorenko',  '2000-07-09', 2,  2,  '2019-05-12'),
    ('Timur',      'Igenov',     '2000-01-21', 3,  3,  '2019-09-17'),
    ('Ermak',      'Abdkdrve',   '2000-05-06', 4,  4,  '2019-09-16'),
    ('Andrew',     'Obidientov', '2000-05-02', 5,  5,  '2019-09-18'),
    ('Aboba',      'Bibinus',    '2000-12-27', 6,  6,  '2019-06-26'),
    ('Chivap',     'Chichi',     '2000-07-19', 7,  7,  '2019-01-12'),
    ('Teddy',      'Bear',       '2000-01-11', 8,  8,  '2019-05-17'),
    ('Wakeme',     'Upwhen',     '2000-03-26', 9,  9,  '2019-02-24'),
    ('February',   'Ends',       '2000-03-26', 10, 10, '2019-02-14');

INSERT INTO
    "order"
    (date, distance, driver_id, total_price)
VALUES
    (TIMESTAMP '2022-09-15 04:01:34', 5.1, 1,  150),
    (TIMESTAMP '2022-09-14 03:01:34', 5.5, 2,  150),
    (TIMESTAMP '2022-09-13 02:01:34', 6.0, 3,  150),
    (TIMESTAMP '2022-09-12 01:01:34', 5.3, 4,  150),
    (TIMESTAMP '2022-09-11 23:01:34', 7.3, 5,  150),
    (TIMESTAMP '2022-09-10 22:01:34', 7.5, 6,  150),
    (TIMESTAMP '2022-09-09 21:01:34', 6.1, 7,  150),
    (TIMESTAMP '2022-09-08 20:01:34', 8.4, 8,  150),
    (TIMESTAMP '2022-09-07 19:01:34', 5.0, 9,  150),
    (TIMESTAMP '2022-09-06 18:01:34', 4.9, 10, 150);

