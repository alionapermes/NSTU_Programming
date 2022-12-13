CREATE OR REPLACE FUNCTION add_order(
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
) RETURNS INTEGER AS $$
BEGIN
    INSERT INTO "order"
        (date, distance, supplier_id, driver_id, total_price,
         departure_city_id, destination_city_id, downtime, status)
    VALUES
        (_date, _distance, _supplier_id, _driver_id, _total_price,
         _departure_city_id, _destination_city_id, _downtime, _status);
    RETURN NEW.id;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION add_city(_name VARCHAR) RETURNS INTEGER AS $$
BEGIN
    INSERT INTO "city"(name) VALUES(_name);
    RETURN NEW.id;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION add_supplier(_name VARCHAR) RETURNS INTEGER AS $$
BEGIN
    INSERT INTO "supplier"(name) VALUES(_name);
    RETURN NEW.id;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION add_receiver(_name VARCHAR) RETURNS INTEGER AS $$
BEGIN
    INSERT INTO "receiver"(name) VALUES(_name);
    RETURN NEW.id;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION add_car(
    _model    VARCHAR,
    _km_price REAL,
    _number   CHAR(6)
) RETURNS INTEGER AS $$
BEGIN
    INSERT INTO "car"
        (model, km_price, number)
    VALUES
        (_model, _km_price, _number);
    RETURN NEW.id;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION add_driver(
    _name          VARCHAR,
    _surname       VARCHAR,
    _birth_date    TIMESTAMP,
    _driving_since TIMESTAMP,
    _car_id        INTEGER,
    _city_id       INTEGER,
    _married       BOOLEAN,
    _wage          REAL
) RETURNS INTEGER AS $$
BEGIN
    INSERT INTO "driver"
        (name, surname, birth_date, driving_since,
         car_id, city_id, married, wage)
    VALUES
        (_name, _surname, _birth_date, _driving_since,
         _car_id, _city_id, _married, _wage);
    RETURN NEW.id;
END;
$$ LANGUAGE 'plpgsql';

