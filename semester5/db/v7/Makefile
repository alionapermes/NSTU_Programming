FLAGS=-U $(USER) -d $(DB) -q

.PHONY: all
all: lab1 lab2 complex

##### lab2 #####
.PHONY: lab2
lab2: lab1 constraint dry_transaction

.PHONY: constraint
constraint:
	psql -c '\i $@.sql' $(FLAGS)

.PHONY: transaction
transaction:
	psql -c '\i $@_step$(STEP).sql' $(FLAGS)

.PHONY: dry_transaction
transaction:
	psql -c '\i $@_step1.sql' $(FLAGS)
	psql -c '\i $@_step2.sql' $(FLAGS)
	psql -c '\i $@_step3.sql' $(FLAGS)

##### lab1 #####
.PHONY: lab1
lab1: schema insert

.PHONY: schema
schema:
	psql -c '\i $@.sql' $(FLAGS)

.PHONY: insert
insert:
	psql -c '\i $@.sql' $(FLAGS)

.PHONY: complex
complex:
	psql -c '\i $@.sql' $(FLAGS)

