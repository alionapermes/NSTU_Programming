CREATE OR REPLACE FUNCTION handle_driver_insert() RETURNS TRIGGER AS $$
DECLARE
    spb_id INTEGER;
BEGIN
    SELECT id INTO spb_id FROM "city" WHERE name = 'Saint Petersburg';
    IF NOT FOUND THEN
        RAISE EXCEPTION 'city Saint Petersburg not found';
    END IF;

    IF NEW.name IS NULL THEN
        NEW.name = 'Driver' || NEW.id;
    END IF;

    IF NEW.city_id IS NULL THEN
        NEW.city_id = spb_id;
    END IF;

    IF AGE(NEW.driving_since) <= '3 years'::interval THEN
        IF NEW.city_id = spb_id THEN
            NEW.driving_since = NOW() - '3 years'::interval;
        ELSE
            NEW.driving_since = NOW();
        END IF;
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION handle_driver_delete() RETURNS TRIGGER AS $$
BEGIN
    DELETE FROM "order" WHERE driver_id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE 'plpgsql';

DROP TRIGGER IF EXISTS "on_driver_insert" ON "driver";
CREATE TRIGGER "on_driver_insert"
    BEFORE INSERT ON "driver"
    FOR EACH ROW EXECUTE PROCEDURE handle_driver_insert();

DROP TRIGGER IF EXISTS "on_driver_delete" ON "driver";
CREATE TRIGGER "on_driver_delete"
    BEFORE DELETE ON "driver"
    FOR EACH ROW EXECUTE PROCEDURE handle_driver_delete();

