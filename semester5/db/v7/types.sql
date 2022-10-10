DROP TYPE IF EXISTS PaymentMethod;
DROP TYPE IF EXISTS ProductType;

CREATE TYPE PaymentMethod AS ENUM('cash', 'cashless');
CREATE TYPE ProductType   AS ENUM('ticket', 'note', 'box');

