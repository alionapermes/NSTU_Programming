DROP ROLE IF EXISTS "admin";
DROP ROLE IF EXISTS "db_user";
DROP ROLE IF EXISTS "operator";

CREATE ROLE "admin"    WITH LOGIN PASSWORD 'admin';
CREATE ROLE "db_user"  WITH LOGIN PASSWORD 'db_user';
CREATE ROLE "operator" WITH LOGIN PASSWORD 'operator';

GRANT USAGE ON SCHEMA "public" TO "admin";
GRANT USAGE ON SCHEMA "public" TO "db_user";
GRANT USAGE ON SCHEMA "public" TO "operator";

GRANT ALL ON SCHEMA "public" TO "admin";
GRANT ALL ON SCHEMA "public" TO "db_user";
GRANT ALL ON SCHEMA "public" TO "operator";

GRANT ALL PRIVILEGES ON ALL SEQUENCES IN SCHEMA "public" TO "admin";
GRANT SELECT, USAGE  ON ALL SEQUENCES IN SCHEMA "public" TO "db_user";
GRANT SELECT, USAGE  ON ALL SEQUENCES IN SCHEMA "public" TO "operator";

-- Оператор имеет права на все действия в таблицах-справочниках: город, страна, тип товара, поставщик, производитель
GRANT INSERT, SELECT, UPDATE, DELETE
    ON "city", "country", "product_type", "provider", "producer"
    TO "operator";

-- Пользователь имеет права на все дейсвтия в таблицах клиентов, товаров и продаж
GRANT INSERT, SELECT, UPDATE, DELETE
    ON "customer", "sales", "product", "product_info" TO "db_user";

-- Администратор имеет права на все действия во всех таблицах
GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA "public" TO "admin";

