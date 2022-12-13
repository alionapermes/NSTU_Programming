CREATE OR REPLACE FUNCTION get_order(_id INTEGER) RETURNS "order" AS $$
DECLARE
    result RECORD;
BEGIN
    SELECT * INTO result FROM "order" WHERE id = _id;
    IF NOT FOUND THEN
        RAISE EXCEPTION 'order with id % not found', _id;
    END IF;
    RETURN result;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION city_name(_id INTEGER) RETURNS CHAR AS $$
DECLARE
    cityname VARCHAR;
BEGIN
    SELECT name INTO cityname FROM "city" WHERE id = _id;
    IF NOT FOUND THEN
        RAISE EXCEPTION 'city with id % not found', _id;
    END IF;
    RETURN cityname;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION supplier_name(_id INTEGER) RETURNS CHAR AS $$
DECLARE
    suppliername VARCHAR;
BEGIN
    SELECT name FROM "supplier" WHERE id = _id;
    IF NOT FOUND THEN
        RAISE EXCEPTION 'supplier with id % not found', _id;
    END IF;
    RETURN suppliername;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION receiver_name(_id INTEGER) RETURNS CHAR AS $$
DECLARE
    receivername VARCHAR;
BEGIN
    SELECT name INTO receivername FROM "receiver" WHERE id = _id;
    IF NOT FOUND THEN
        RAISE EXCEPTION 'receiver with id % not found', _id;
    END IF;
    RETURN receivername;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION get_car(_id INTEGER) RETURNS "car" AS $$
DECLARE
    result RECORD;
BEGIN
    SELECT * INTO result FROM "car" WHERE id = _id;
    IF NOT FOUND THEN
        RAISE EXCEPTION 'car with id % not found', _id;
    END IF;
    RETURN result;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION get_driver(_id INTEGER) RETURNS "driver" AS $$
DECLARE
    result RECORD;
BEGIN
    SELECT * INTO result FROM "driver" WHERE id = _id;
    IF NOT FOUND THEN
        RAISE EXCEPTION 'driver with id % not found', _id;
    END IF;
    RETURN result;
END;
$$ LANGUAGE 'plpgsql';

