CREATE TABLE "journal" (
    id        SERIAL,
    time      TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    statement CHAR(6)   NOT NULL,
    username  VARCHAR   NOT NULL,
    tablename VARCHAR   NOT NULL,
    row_id    INTEGER   NOT NULL,

    PRIMARY KEY (id)
);

CREATE OR REPLACE FUNCTION log() RETURNS TRIGGER AS $$
BEGIN
    IF TG_OP = 'DELETE' THEN
        INSERT INTO "journal"(statement, username, tablename, row_id)
        VALUES (TG_OP, USER, TG_TABLE_NAME, OLD.id - 1);
        RETURN OLD;
    ELSIF TG_OP IN ('INSERT', 'UPDATE') THEN
        INSERT INTO "journal"(statement, username, tablename, row_id)
        VALUES (TG_OP, USER, TG_TABLE_NAME, NEW.id);
        RETURN NEW;
    END IF;
    RETURN NULL;
END
$$ LANGUAGE 'plpgsql';

CREATE TRIGGER "tr_log_city"
    AFTER INSERT OR UPDATE OR DELETE
    ON "city"
    FOR EACH ROW EXECUTE PROCEDURE log();

CREATE TRIGGER "tr_log_supplier"
    AFTER INSERT OR UPDATE OR DELETE
    ON "supplier"
    FOR EACH ROW EXECUTE PROCEDURE log();

CREATE TRIGGER "tr_log_receiver"
    AFTER INSERT OR UPDATE OR DELETE
    ON "receiver"
    FOR EACH ROW EXECUTE PROCEDURE log();

CREATE TRIGGER "tr_log_car"
    AFTER INSERT OR UPDATE OR DELETE
    ON "car"
    FOR EACH ROW EXECUTE PROCEDURE log();

CREATE TRIGGER "tr_log_driver"
    AFTER INSERT OR UPDATE OR DELETE
    ON "driver"
    FOR EACH ROW EXECUTE PROCEDURE log();

CREATE TRIGGER "tr_log_order"
    AFTER INSERT OR UPDATE OR DELETE
    ON "order"
    FOR EACH ROW EXECUTE PROCEDURE log();

