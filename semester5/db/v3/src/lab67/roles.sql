DROP ROLE IF EXISTS "admin";
DROP ROLE IF EXISTS "operator";
DROP ROLE IF EXISTS "db_user";
DROP ROLE IF EXISTS "analyst";

CREATE ROLE "admin"    WITH LOGIN PASSWORD 'admin';
CREATE ROLE "operator" WITH LOGIN PASSWORD 'opeartor';
CREATE ROLE "db_user"  WITH LOGIN PASSWORD 'db_user';
CREATE ROLE "analyst"  WITH LOGIN PASSWORD 'analyst';

GRANT USAGE ON SCHEMA "public" TO "admin";
GRANT USAGE ON SCHEMA "public" TO "operator";
GRANT USAGE ON SCHEMA "public" TO "db_user";
GRANT USAGE ON SCHEMA "public" TO "analyst";

GRANT ALL PRIVILEGES ON SCHEMA "public" TO "admin";
GRANT ALL PRIVILEGES ON SCHEMA "public" TO "operator";
GRANT ALL PRIVILEGES ON SCHEMA "public" TO "db_user";
GRANT ALL PRIVILEGES ON SCHEMA "public" TO "analyst";

GRANT SELECT, USAGE ON ALL SEQUENCES IN SCHEMA "public" TO "admin";
GRANT SELECT, USAGE ON ALL SEQUENCES IN SCHEMA "public" TO "operator";
GRANT SELECT, USAGE ON ALL SEQUENCES IN SCHEMA "public" TO "db_user";
GRANT SELECT        ON ALL SEQUENCES IN SCHEMA "public" TO "analyst";

GRANT INSERT, SELECT, UPDATE, DELETE
    ON "receiver", "supplier", "city", "car"
    TO "operator";
GRANT INSERT ON "journal" TO "operator";

GRANT INSERT, SELECT, UPDATE, DELETE
    ON "driver", "order"
    TO "db_user";
GRANT INSERT ON "journal" TO "db_user";

REVOKE ALL PRIVILEGES ON "journal" FROM "analyst";
GRANT SELECT ON ALL TABLES IN SCHEMA "public" TO "analyst";

GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA "public" TO "admin";

