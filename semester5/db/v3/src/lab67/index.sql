SET ENABLE_SEQSCAN TO OFF;

DROP INDEX IF EXISTS "order_date_idx";
CREATE INDEX "order_date_idx" ON "order" (date);

DROP INDEX IF EXISTS "order_season_idx";
CREATE INDEX "order_season_idx" ON "order" (get_season(date));

DROP INDEX IF EXISTS "order_driver_id_idx";
CREATE INDEX "order_driver_id_idx" ON "order" USING HASH (driver_id);

DROP INDEX IF EXISTS "destination_city_id_idx";
CREATE INDEX "destination_city_id_idx" ON "order" USING HASH (destination_city_id);
