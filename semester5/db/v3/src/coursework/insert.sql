CREATE OR REPLACE FUNCTION random_date(
    date_from TIMESTAMP,
    date_to   TIMESTAMP
) RETURNS TIMESTAMP AS $$
BEGIN
    IF date_from > date_to THEN
        RAISE EXCEPTION 'date_from cannot be greater than date_to';
    END IF;

    RETURN (SELECT date_from + RANDOM() * (date_to - date_from));
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION generate_products(n INTEGER) RETURNS CHAR AS $$
DECLARE
    set_1    VARCHAR[];
    set_2    VARCHAR[];
    name_1   INTEGER;
    name_2   INTEGER;
    _type_id INTEGER;
    _name    VARCHAR;
BEGIN
    set_1 := ARRAY ['massive', 'lightweight', 'painless', 'painful', 'sunny'];
    set_2 := ARRAY ['beauty', 'cute', 'wonder', 'strange', 'holy', 'bloody'];
    
    FOR i IN 1..n LOOP
        SELECT FLOOR(RANDOM() * 4 + 1) INTO name_1;
        SELECT FLOOR(RANDOM() * 5 + 1) INTO name_2;
        SELECT FLOOR(RANDOM() * COUNT(*) + 1) INTO _type_id FROM "product_type";

        SELECT name INTO _name FROM "product_type"
            WHERE id = _type_id;
            
        _name := format('%s %s %s', set_1[name_1], set_2[name_2], _name);
       
        INSERT INTO "product"
            (name, type_id, released, price, city_id,
            country_id, producer_id, provider_id)
        VALUES
            (
                _name,
                _type_id,
                random_date('1970-01-01'::timestamp, NOW()::timestamp),
                (SELECT RANDOM() * 10000),
                (SELECT FLOOR(RANDOM() * COUNT(*) + 1) FROM "city"),
                (SELECT FLOOR(RANDOM() * COUNT(*) + 1) FROM "country"),
                (SELECT FLOOR(RANDOM() * COUNT(*) + 1) FROM "producer"),
                (SELECT FLOOR(RANDOM() * COUNT(*) + 1) FROM "provider")
            );
    END LOOP;

    RETURN n || ' products inserted';
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION generate_sales(n INTEGER) RETURNS CHAR AS $$
DECLARE
    _product_date TIMESTAMP;
    _product_id   INTEGER;
BEGIN
    FOR i IN 1..n LOOP
        SELECT FLOOR(RANDOM() * COUNT(*) + 1) INTO _product_id FROM "product";
        SELECT released INTO _product_date FROM "product"
            WHERE id = _product_id;
    
        INSERT INTO "sales"(date, qty, product_id, customer_id)
        VALUES
            (
                random_date(_product_date, NOW()::timestamp),
                (SELECT FLOOR(RANDOM() * 98 + 1)),
                _product_id,
                (SELECT FLOOR(RANDOM() * COUNT(*) + 1) FROM "customer")
            );
    END LOOP;

    RETURN n || ' sales inserted';
END;
$$ LANGUAGE 'plpgsql';

INSERT INTO "city"(name)
VALUES
    ('Novosibirsk'),
    ('Berdsk'),
    ('Tomsk'),
    ('Novokuznetsk'),
    ('Kemerovo'),
    ('Saint Petersburg'),
    ('Moscow'),
    ('Omsk'),
    ('Belgorod'),
    ('Ekaterinburg'),
    ('London'),
    ('Seoul'),
    ('Tokyo'),
    ('LA'),
    ('Berlin'), 
    ('Munich'),
    ('Vienn'),
    ('Jakarta'),
    ('Beijin'),
    ('Vorkuta');

INSERT INTO "country"(name)
VALUES
    ('USA'),
    ('China'),
    ('Russia'),
    ('Japan'),
    ('SKorea'),
    ('Hungary'),
    ('Italy'),
    ('France'),
    ('Hongkong');

INSERT INTO "producer"(name)
VALUES
    ('one'),
    ('two'),
    ('three'),
    ('four'),
    ('six'),
    ('seven'),
    ('eight'),
    ('nine'),
    ('ten');

INSERT INTO "provider"(name)
VALUES
    ('Tesla'),
    ('Amazon'),
    ('Yandex'),
    ('Alphabet'),
    ('IBM'),
    ('Microsoft'),
    ('Sun Microsystems'),
    ('Apple'),
    ('Facebook');

INSERT INTO "customer"(fullname, age)
VALUES
    ('abobus', 22),
    ('bibinus', 21),
    ('cick', 32),
    ('dump', 52),
    ('eight', 33),
    ('france', 41),
    ('guardian', 45),
    ('cockumber', 54),
    ('tractor', 34),
    ('cactus', 53);

INSERT INTO "product_type"(name)
VALUES
    ('titfer'),
    ('cap'),
    ('beret'),
    ('chapeau'),
    ('porkpie'),
    ('beanie');

select generate_products(100);
select generate_sales(100);
