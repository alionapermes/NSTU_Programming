SELECT * FROM "product_info";

-- Для каждого вида товара выдать список, отсортированный: по году выпуска, по поставщику, по стоимости
SELECT * FROM "product_info"
    WHERE type = 'cap' -- вид товара
    ORDER BY released DESC; -- критерий сортировки

-- Найти самый дорогой головной убор, самый дешёвый, среднюю стоимость
SELECT MIN(price), MAX(price), AVG(price) FROM "product_info";
-- Найти головные уборы с ценой свыше 1000 р (или любая другая сумма по выбору)
SELECT * FROM "product_info" WHERE price > 1000; -- выбор цены

-- Найти количество и среднюю стоимость головных уборов выпущенных за определённый период
SELECT COUNT(*) AS qty, MIN(price), MAX(price), AVG(price)
    FROM "product_info"
    WHERE released BETWEEN '2022-01-01' AND '2022-12-31'; -- период

-- Найти долю головных уборов, поступивших из заданного города от общего числа головных уборов
SELECT city_part_of_total('Seoul'); -- выбор города

-- Найти все головные уборы с заданной датой выпуска
SELECT * FROM "product_info" WHERE released = '2022-09-18'; -- выбор даты

-- Найти все головные уборы заданного поставщика, чья стоимость находится в заданных пределах
SELECT * FROM "product_info"
    WHERE provider_name = 'Yandex' -- выбор поставщика
        AND price BETWEEN 3333 AND 5555; -- выбор пределов смтоимости

-- Найти долю головных уборов, поступивших от заданного поставщика от общего числа поставщиков
SELECT provider_part_of_total('Yandex'); -- выбор поставщика

-- Найти все головные уборы заданного года выпуска, чья стоимость больше заданной
SELECT * FROM "product_info"
    WHERE EXTRACT('year' FROM released) = 2021 -- выбор года
        AND price > 1234; -- выбор стоимости

-- Найти все головные уборы заданного производителя
SELECT * FROM "product_info" WHERE producer_name = 'three'; -- выбор производителя

-- Найти долю головных уборов, проданных за определённый период времени от общего времени продажи
SELECT sale_period_part_of_total('2022-01-01', '2022-12-31'); -- выбор периода

-- Найти все головные уборы, поступившие от заданного поставщика,
-- чья стоимость больше, чем средняя стоимость головных уборов, поступивших из заданной страны
SELECT * FROM "product_info"
WHERE provider_name = 'IBM' -- выбор поставщика
    AND price > (
        SELECT AVG(price) FROM "product_info"
        WHERE country_name = 'Japan'); -- выбор страны

-- Найти долю дешёвых головных уборов (чья стоимость меньше заданной), проданных заданному клиенту, и в целом
SELECT * FROM cheap_part_of_total(5432, 5);

-- Найти среднюю стоимость головных уборов, проданных за определённый промежуток времени
SELECT AVG(price) FROM "product"
WHERE id IN (
    SELECT DISTINCT product_id FROM "sales"
    WHERE date BETWEEN '2022-01-01' AND '2022-12-31'); -- выбор временного промежутка

-- Найти все головные уборы, чья стоимость выше, чем средняя стоимость головных уборов заданного производителя
SELECT * FROM "product_info"
WHERE price > (
    SELECT AVG(price) FROM "product_info" WHERE producer_name = 'one');
