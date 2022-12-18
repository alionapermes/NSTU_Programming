-- Для каждого вида товара выдать список, отсортированный: по году выпуска, по поставщику, по стоимости
SELECT * FROM "product"
    LEFT JOIN "provider" ON "product".provider_id = "provider".id
    WHERE "product".type_id = find_product('product name')
    ORDER BY "product".released DESC; -- сортировка по дате выпуска
    -- ORDER BY "product".price DESC; -- сортировка по цене
    -- ORDER BY "provider".name DESC; -- сортировка по поставщику

-- Найти самый дорогой головной убор, самый дешёвый, среднюю стоимость
SELECT * FROM "product" WHERE price = (SELECT MAX(price) FROM "product"); -- самый дорогой
SELECT * FROM "product" WHERE price = (SELECT MIN(price) FROM "product"); -- самый дешёвый
SELECT AVG(price) AS avg_price FROM "product";                            -- средняя стоимость

-- Найти головные уборы с ценой свыше 1000 р
SELECT * FROM "product" WHERE price > 123;

-- Найти количество и среднюю стоимость головных уборов выпущенных за определённый период
SELECT COUNT(*) AS qty, MIN(price), MAX(price), AVG(price)
    FROM "product"
    -- за определённый месяц
    -- WHERE EXTRACT('month' FROM released) = 1
    -- за период по месяцам всех лет
    -- WHERE EXTRACT('month', released) BETWEEN 1 AND 12
    -- за период по датам
    -- WHERE released BETWEEN '2022-01-01' AND '2022-12-31'
;

-- Найти долю головных уборов, поступивших из заданного города от общего числа головных уборов
SELECT city_part_of_total('Seoul');

-- Найти все головные уборы с заданной датой выпуска
SELECT * FROM "product" WHERE released = '2022-12-31';

-- Найти все головные уборы заданного поставщика, чья стоимость находится в заданных пределах
SELECT * FROM "product"
    WHERE provider_id = find_provider('Yandex')
        AND price BETWEEN 1 AND 10000;

-- Найти долю головных уборов, поступивших от заданного поставщика от общего числа поставщиков
SELECT provider_part_of_total('Yandex');

-- Найти все головные уборы заданного года выпуска, чья стоимость больше заданной
SELECT * FROM "product"
    WHERE EXTRACT('year' FROM released) = 2022
        AND price > 5000;

SELECT "product".* FROM "product"
    LEFT JOIN "producer" ON "product".producer_id = "producer".id
    WHERE "producer".name = 'provider name';

-- Найти долю головных уборов, проданных за определённый период времени от общего времени продажи
SELECT sale_period_part_of_total('2022-01-01', '2022-12-31');

-- Найти все головные уборы, поступившие от заданного поставщика,
-- чья стоимость больше, чем средняя стоимость головных уборов, поступивших из заданной страны
SELECT "product".* FROM "product"
WHERE provider_id = find_provider('provider name')
    AND price > (
        SELECT AVG(price) FROM "product"
        WHERE country_id = find_country('country name'));

-- Найти долю дешёвых головных уборов (чья стоимость меньше заданной), проданных заданному клиенту, и в целом
SELECT cheap_part_of_total(1111, 1);

-- Найти среднюю стоимость головных уборов, проданных за определённый промежуток времени
SELECT AVG(price) FROM "product"
WHERE id IN (
    SELECT DISTINCT product_id FROM "sales"
    WHERE date BETWEEN '2022-01-01' AND '2022-12-31');

-- Найти все головные уборы, чья стоимость выше, чем средняя стоимость головных уборов заданного производителя
SELECT * FROM "product"
WHERE price > (
    SELECT AVG(price) FROM "product"
    WHERE provider_id = find_producer('producer name'));
