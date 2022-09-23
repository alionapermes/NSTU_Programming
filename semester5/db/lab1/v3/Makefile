FLAGS=-U $(USER) -d $(DB) -q

.PHONY: all
all: schema insert complex

.PHONY: schema
schema:
	psql -c '\i $@.sql' $(FLAGS)

.PHONY: insert
insert:
	psql -c '\i $@.sql' $(FLAGS)

.PHONY: complex
complex:
	psql -c '\i $@.sql' $(FLAGS)

