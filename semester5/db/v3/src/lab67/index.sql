SET ENABLE_SEQSCAN TO OFF;

DROP INDEX IF EXISTS "order_date_idx";
CREATE INDEX "order_date_idx" ON "order" (date);

DROP INDEX IF EXISTS "order_season_idx";
CREATE INDEX "order_season_idx" ON "order" (get_season(date));

