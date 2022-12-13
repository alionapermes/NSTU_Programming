DROP ROLE IF EXISTS "operator";
DROP ROLE IF EXISTS "user";
DROP ROLE IF EXISTS "analyst";

CREATE ROLE "operator" WITH LOGIN;
CREATE ROLE "user"     WITH LOGIN;
CREATE ROLE "analyst"  WITH LOGIN;

GRANT USAGE ON SCHEMA "public" TO "operator";
GRANT USAGE ON SCHEMA "public" TO "user";

GRANT ALL ON SCHEMA "public" TO "operator";
GRANT ALL ON SCHEMA "public" TO "user";

GRANT SELECT, USAGE ON ALL SEQUENCES IN SCHEMA "public" TO "operator";
GRANT SELECT, USAGE ON ALL SEQUENCES IN SCHEMA "public" TO "user";
GRANT SELECT ON ALL SEQUENCES IN SCHEMA "public" TO "analyst";

GRANT INSERT, SELECT, UPDATE, DELETE
    ON "car", "receiver", "supplier", "driver", "order", "city"
    TO "operator";
GRANT INSERT ON "journal" TO "operator";

GRANT INSERT, SELECT, UPDATE, DELETE
    ON "car", "receiver", "supplier", "driver", "order", "city"
    TO "user";
GRANT INSERT ON "journal" TO "user";

GRANT SELECT ON ALL TABLES IN SCHEMA "public" TO "analyst";
REVOKE ALL PRIVILEGES ON "journal" FROM "analyst";

