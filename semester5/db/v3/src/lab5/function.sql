CREATE OR REPLACE FUNCTION add_n(n INTEGER) RETURNS CHAR AS $$
BEGIN
    FOR i IN 0..n LOOP
        INSERT INTO
            car(model, km_price, number)
        VALUES
            (
                (SELECT (ARRAY ['Toyota','Ford','Nissan'])[FLOOR(RANDOM() * 3 + 1)]),
                (SELECT FLOOR(RANDOM() * 200 + 100)),
                (SELECT CONCAT('a', FLOOR(RANDOM() * 898 + 101), 'aa'))
            );
    END LOOP;

    RETURN n || ' items inserted';
END;
$$ LANGUAGE "plpgsql";

SELECT add_n(1000);

