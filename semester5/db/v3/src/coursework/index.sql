DROP INDEX IF EXISTS "city_name_idx";
CREATE INDEX "city_name_idx" ON "product_info" USING HASH (city_name);

DROP INDEX IF EXISTS "country_name_idx";
CREATE INDEX "country_name_idx" ON "product_info" USING HASH (country_name);

DROP INDEX IF EXISTS "producer_name_idx";
CREATE INDEX "producer_name_idx" ON "product_info" (producer_name);

DROP INDEX IF EXISTS "provider_name_idx";
CREATE INDEX "provider_name_idx" ON "product_info" (provider_name);

DROP INDEX IF EXISTS "customer_id_idx";
CREATE INDEX "customer_id_idx" ON "sales" USING HASH (customer_id);

DROP INDEX IF EXISTS "product_type_name_idx";
CREATE INDEX "product_type_name_idx" ON "product_info" USING HASH (type);

DROP INDEX IF EXISTS "product_provider_id_idx";
CREATE INDEX "product_provider_id_idx" ON "product" (provider_id);

DROP INDEX IF EXISTS "product_released_idx";
CREATE INDEX "product_released_idx" ON "product" (released);

DROP INDEX IF EXISTS "product_price_idx";
CREATE INDEX "product_price_idx" ON "product" (price);

