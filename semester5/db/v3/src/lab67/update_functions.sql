CREATE OR REPLACE FUNCTION update_order(
    _id                  INTEGER,
    _date                TIMESTAMP,
    _distance            REAL,
    _supplier_id         INTEGER,
    _receiver_id         INTEGER,
    _driver_id           INTEGER,
    _total_price         REAL,
    _departure_city_id   INTEGER,
    _destination_city_id INTEGER,
    _downtime            INTERVAL,
    _status              order_status
) RETURNS VOID AS $$
BEGIN
    UPDATE "order"
    SET
        date                = _date,
        distance            = _distance,
        supplier_id         = _supplier_id,
        receiver_id         = _receiver_id,
        driver_id           = _driver_id,
        total_price         = _total_price,
        departure_city_id   = _departure_city_id,
        destination_city_id = _destination_city_id,
        downtime            = _downtime,
        status              = _status
    WHERE id = _id;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'order with id % not found', _id;
    END IF;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION rename_city(_id INTEGER, _new_name VARCHAR)
    RETURNS VOID AS $$
BEGIN
    UPDATE "city" SET name = _new_name WHERE id = _id;
    IF NOT FOUND THEN
        RAISE EXCEPTION 'city with id % not found', _id;
    END IF;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION rename_supplier(_id INTEGER, _new_name VARCHAR)
    RETURNS VOID AS $$
BEGIN
    UPDATE "supplier" SET name = _new_name WHERE id = _id;
    IF NOT FOUND THEN
        RAISE EXCEPTION 'supplier with id % not found', _id;
    END IF;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION rename_receiver(_id INTEGER, _new_name VARCHAR)
    RETURNS VOID AS $$
BEGIN
    UPDATE "receiver" SET name = _new_name WHERE id = _id;
    IF NOT FOUND THEN
        RAISE EXCEPTION 'receiver with id % not found', _id;
    END IF;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION update_car(
    _id       INTEGER,
    _model    VARCHAR,
    _km_price REAL,
    _number   CHAR(6)
) RETURNS VOID AS $$
BEGIN
    UPDATE "car"
    SET
        model    = _model,
        km_price = _km_price,
        number   = _number
    WHERE id = _id;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'car with id % not found', _id;
    END IF;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION update_driver(
    _id            VARCHAR,
    _name          VARCHAR,
    _surname       VARCHAR,
    _birth_date    TIMESTAMP,
    _driving_since TIMESTAMP,
    _car_id        INTEGER,
    _city_id       INTEGER,
    _married       BOOLEAN,
    _wage          REAL
) RETURNS VOID AS $$
BEGIN
    UPDATE "driver"
    SET
        name          = _name,
        surname       = _surname,
        birth_date    = _birth_date,
        driving_since = _driving_since,
        car_id        = _car_id,
        city_id       = _city_id,
        married       = _married,
        wage          = _wage
    WHERE id = _id;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'driver with id % not found', _id;
    END IF;
END;
$$ LANGUAGE 'plpgsql';

