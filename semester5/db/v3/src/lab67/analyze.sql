DROP TYPE IF EXISTS "season";
CREATE TYPE "season" AS ENUM('spring', 'summer', 'autumn', 'winter');

CREATE OR REPLACE FUNCTION get_season(date TIMESTAMP) RETURNS season AS $$
DECLARE
    month_num INTEGER;
BEGIN
    SELECT EXTRACT('MONTH' FROM date) INTO month_num;

    IF (12 <= month_num OR month_num <= 2) THEN
        RETURN 'winter'::season;
    ELSIF (month_num BETWEEN 3 AND 5) THEN
        RETURN 'spring'::season;
    ELSIF (month_num BETWEEN 6 AND 8) THEN
        RETURN 'summer'::season;
    ELSIF (month_num BETWEEN 9 AND 11) THEN
        RETURN 'autumn'::season;
    END IF;
END;
$$ LANGUAGE 'plpgsql';

-- average driver downtime
CREATE OR REPLACE FUNCTION get_avg_driver_downtime(_driver_id INTEGER)
    RETURNS INTERVAL AS $$
DECLARE
    avg_downtime INTERVAL;
BEGIN
    SELECT AVG(downtime) INTO avg_downtime
    FROM "order"
    WHERE driver_id = _driver_id;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'driver with id % not found', _driver_id;
    END IF;

    RETURN avg_downtime;
END;
$$ LANGUAGE 'plpgsql';

-- ratio of intercity to intracity orders qty
CREATE OR REPLACE FUNCTION get_transit_ratio()
    RETURNS REAL AS $$
DECLARE
    intercity_count INTEGER;
    intracity_count INTEGER;
BEGIN
    SELECT COUNT(*) INTO intracity_count
    FROM "order"
    WHERE departure_city_id = destination_city_id;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'no one intracity delivery found';
    END IF;

    SELECT COUNT(*) - intracity_count INTO intercity_count FROM "order";

    RETURN intercity_count / intracity_count;
END;
$$ LANGUAGE 'plpgsql';

-- quantity of daily orders
CREATE OR REPLACE FUNCTION get_daily_orders_qty() RETURNS INTEGER AS $$
BEGIN
    RETURN (
        SELECT COUNT(*)
        FROM "order"
        WHERE EXTRACT('HOUR' FROM date) BETWEEN 5 AND 24
    );
END;
$$ LANGUAGE 'plpgsql';

-- quantity of nightly orders
CREATE OR REPLACE FUNCTION get_nightly_orders_qty() RETURNS INTEGER AS $$
BEGIN
    RETURN (
        SELECT COUNT(*)
        FROM "order"
        WHERE EXTRACT('HOUR' FROM date) BETWEEN 0 AND 4
    );
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION analyze_failures_by_seasons() RETURNS TABLE (
    season        season,
    qty           BIGINT,
    avg_price     DOUBLE PRECISION,
    season_income REAL
) AS $$
BEGIN
    RETURN QUERY (
        SELECT
            get_season(date) AS "season",
            COUNT(*)         AS "qty",
            AVG(total_price) AS "avg_price",
            SUM(total_price) AS "season_income"
        FROM "order"
        GROUP BY get_season(date)
        ORDER BY "season" ASC
    );
END;
$$ LANGUAGE 'plpgsql';

