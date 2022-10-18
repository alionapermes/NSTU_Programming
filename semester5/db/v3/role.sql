DROP ROLE IF EXISTS student;

CREATE ROLE
    student
WITH
    LOGIN
    PASSWORD 'password';

ALTER DATABASE
    v7
OWNER TO
    student;

