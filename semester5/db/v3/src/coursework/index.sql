DROP INDEX IF EXISTS "city_name_idx";
CREATE INDEX "city_name_idx" ON "city" USING HASH (name);

DROP INDEX IF EXISTS "country_name_idx";
CREATE INDEX "country_name_idx" ON "country" USING HASH (name);

DROP INDEX IF EXISTS "producer_name_idx";
CREATE INDEX "producer_name_idx" ON "producer" USING HASH (name);

DROP INDEX IF EXISTS "provider_name_idx";
CREATE INDEX "provider_name_idx" ON "provider" USING HASH (name);

DROP INDEX IF EXISTS "customer_fullname_idx";
CREATE INDEX "customer_fullname_idx" ON "customer" USING HASH (fullname);

DROP INDEX IF EXISTS "product_type_name_idx";
CREATE INDEX "product_type_name_idx" ON "product_type" USING HASH (name);

DROP INDEX IF EXISTS "product_provider_id_idx";
CREATE INDEX "product_provider_id_idx" ON "product" (provider_id);

DROP INDEX IF EXISTS "product_type_id_idx";
CREATE INDEX "product_type_id_idx" ON "product" (type_id);

DROP INDEX IF EXISTS "product_released_idx";
CREATE INDEX "product_released_idx" ON "product" (released);

DROP INDEX IF EXISTS "product_price_idx";
CREATE INDEX "product_price_idx" ON "product" (price);
