CREATE OR REPLACE FUNCTION delete_order(_id INTEGER) RETURNS BOOLEAN AS $$
BEGIN
    DELETE FROM "order" WHERE id = _id;

    IF NOT FOUND THEN
        RETURN false;
    END IF;

    RETURN true;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION delete_supplier(_id INTEGER) RETURNS BOOLEAN AS $$
BEGIN
    DELETE FROM "supplier" WHERE id = _id;

    IF NOT FOUND THEN
        RETURN false;
    END IF;

    RETURN true;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION delete_receiver(_id INTEGER) RETURNS BOOLEAN AS $$
BEGIN
    DELETE FROM "receiver" WHERE id = _id;

    IF NOT FOUND THEN
        RETURN false;
    END IF;

    RETURN true;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION delete_city(_id INTEGER) RETURNS BOOLEAN AS $$
BEGIN
    DELETE FROM "city" WHERE id = _id;

    IF NOT FOUND THEN
        RETURN false;
    END IF;

    RETURN true;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION delete_car(_id INTEGER) RETURNS BOOLEAN AS $$
BEGIN
    DELETE FROM "car" WHERE id = _id;

    IF NOT FOUND THEN
        RETURN false;
    END IF;

    RETURN true;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION delete_driver(_id INTEGER) RETURNS BOOLEAN AS $$
BEGIN
    DELETE FROM "driver" WHERE id = _id;

    IF NOT FOUND THEN
        RETURN false;
    END IF;

    RETURN true;
END;
$$ LANGUAGE 'plpgsql';
