FLAGS=-U $(USER) -d $(DB) -q

.PHONY: all
all: lab1 lab2 complex

##### lab2 #####
.PHONY: lab2
lab2: lab1 constraint

.PHONY: constraint
constraint:
	psql -c '\i $@.sql' $(FLAGS)

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

