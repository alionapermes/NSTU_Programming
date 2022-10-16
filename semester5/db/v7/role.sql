DROP ROLE IF EXISTS abobus;

CREATE USER
    abobus
WITH
    LOGIN;

ALTER DATABASE
    v7
OWNER TO
    abobus;

REASSIGN OWNED BY
    me
TO
    abobus;

