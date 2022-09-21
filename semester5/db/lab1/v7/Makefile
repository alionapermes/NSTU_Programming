SQL_SCHEMA=schema.sql
SQL_INSERT=insert.sql
SQL_COMPLEX=complex.sql


.PHONY: all
all: schema data complex

.PHONY: schema
schema:
	psql -U $(USER) -d $(DB) -c '$(shell cat $(SQL_SCHEMA))'

.PHONY: data
data:
	pqsl -U $(USER) -d $(DB) -c $(SQL_INSERT)

.PHONY: complex
complex:
	psql -U $(USER) -d $(DB) -c $(SQL_COMPLEX)

