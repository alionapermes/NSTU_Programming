CREATE OR REPLACE FUNCTION hello(name CHAR) RETURNS CHAR AS $$
BEGIN
    RETURN 'Hello, ' || name;
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION hello(age INTEGER) RETURNS CHAR AS $$
BEGIN
    RETURN 'Hello, ' || age || ' years old guest';
END;
$$ LANGUAGE 'plpgsql';

