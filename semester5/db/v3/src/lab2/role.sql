DROP ROLE IF EXISTS student;

CREATE ROLE
    student
WITH
    LOGIN
    PASSWORD 'password';

ALTER DATABASE v3    OWNER TO student;
ALTER TABLE "order"  OWNER TO student;
ALTER TABLE "driver" OWNER TO student;
ALTER TABLE "city"   OWNER TO student;
ALTER TABLE "car"    OWNER TO student;

