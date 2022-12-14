CREATE OR REPLACE FUNCTION random_date(
    date_from TIMESTAMP,
    date_to   TIMESTAMP
) RETURNS TIMESTAMP AS $$
BEGIN
    IF date_from > date_to THEN
        RAISE EXCEPTION 'date_from cannot be greater than date_to';
    END IF;

    RETURN (SELECT date_from + RANDOM() * (date_to - date_from));
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION generate_cars(n INTEGER) RETURNS CHAR AS $$
BEGIN
    FOR i IN 0..n LOOP
        INSERT INTO "car"(model, km_price, number)
        VALUES
            (
                (SELECT (ARRAY ['Toyota','Ford','Nissan','LADA','Honda','Subaru','Kia'])[FLOOR(RANDOM() * 7 + 1)]),
                (SELECT FLOOR(RANDOM() * 100 + 25)),
                (SELECT CONCAT('a', FLOOR(RANDOM() * 898 + 101), 'aa'))
            );
    END LOOP;

    RETURN n || ' items inserted';
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION generate_drivers(n INTEGER) RETURNS CHAR AS $$
DECLARE
    tmp_birth_date    TIMESTAMP;
    tmp_driving_since TIMESTAMP;
BEGIN
    FOR i IN 0..n LOOP
        SELECT random_date(
            '1970-01-01'::timestamp, '2004-12-31 23:59:59'::timestamp)
            INTO tmp_birth_date;

        SELECT tmp_birth_date + RANDOM() * (NOW() - tmp_birth_date)
            INTO tmp_driving_since;

        INSERT INTO "driver"
            (name, surname, birth_date, car_id,
             city_id, driving_since, married, wage)
        VALUES
            (
                (SELECT (ARRAY ['uga','buga','UwU','T_T','xD',':(','one','two','three','four','five','six'])[FLOOR(RANDOM() * 12 + 1)]),
                (SELECT (ARRAY ['uga','buga','UwU','T_T','xD',':(','one','two','three','four','five','six'])[FLOOR(RANDOM() * 12 + 1)]),
                tmp_birth_date,
                (SELECT FLOOR(RANDOM() * 10 + 1)),
                (SELECT FLOOR(RANDOM() * 10 + 1)),
                tmp_driving_since,
                (SELECT (ARRAY [true, false])[FLOOR(RANDOM() * 2 + 1)]),
                (SELECT FLOOR(RANDOM() * 32000 + 16000))
            );
    END LOOP;

    RETURN n || ' items inserted';
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION generate_orders(n INTEGER) RETURNS CHAR AS $$
DECLARE
    _date      TIMESTAMP;
    _driver_id INTEGER;
    _distance  INTEGER;
    _downtime  INTERVAL;
BEGIN
    FOR i IN 0..n LOOP
        SELECT FLOOR(RANDOM() * COUNT(*) + 1) INTO _driver_id FROM "driver";
        SELECT FLOOR(RANDOM() * 10 + 1) INTO _distance;
        SELECT random_date('1970-01-01'::timestamp, NOW()::timestamp)
            INTO _date;
        SELECT ((FLOOR(RANDOM() * 100) + 1) || ' seconds')::interval
            INTO _downtime;

        INSERT INTO "order"
            (date, distance, driver_id, total_price, departure_city_id,
             destination_city_id, downtime, supplier_id, receiver_id, status)
        VALUES
            (
                _date,                               -- date
                _distance,                           -- distance
                _driver_id,                          -- driver_id
                (SELECT "car".km_price * _distance
                    FROM "driver" LEFT JOIN "car" ON "driver".car_id = "car".id
                    WHERE "driver".id = _driver_id), -- total_price
                (SELECT FLOOR(RANDOM() * 10 + 1)),   -- departure_city_id
                (SELECT FLOOR(RANDOM() * 10 + 1)),   -- destination_city_id
                _downtime,                           -- downtime
                (SELECT FLOOR(RANDOM() * 10 + 1)),   -- supplier_id
                (SELECT FLOOR(RANDOM() * 10 + 1)),   -- receiver_id
                (SELECT ('[0:1]={success,failed}'::order_status[])
                    [FLOOR(RANDOM() * 2)])           -- status
            );
    END LOOP;

    RETURN n || ' items inserted';
END;
$$ LANGUAGE 'plpgsql';

INSERT INTO "city"(name)
VALUES
    ('Novosibirsk'),
    ('Berdsk'),
    ('Tomsk'),
    ('Novokuznetsk'),
    ('Kemerovo'),
    ('Saint Petersburg'),
    ('Moscow'),
    ('Omsk'),
    ('Belgorod'),
    ('Ekaterinburg');

INSERT INTO "receiver"(name)
VALUES
    ('abobus'),
    ('bibinus'),
    ('cick'),
    ('dump'),
    ('eight'),
    ('france'),
    ('guardian'),
    ('cockumber'),
    ('tractor'),
    ('cactus');

INSERT INTO "supplier"(name)
VALUES
    ('one'),
    ('two'),
    ('three'),
    ('four'),
    ('five'),
    ('six'),
    ('seven'),
    ('eight'),
    ('nine'),
    ('ten');

select generate_cars(100);
select generate_drivers(100);
select generate_orders(100);
