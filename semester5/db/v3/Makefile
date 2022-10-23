USERNAME ?= postgres
DATABASE ?= v3

DMS  = psql
LABS = lab1 lab2 lab3 lab4
lab1 = schema insert complex
lab2 = schema insert role constraints transaction
lab3 = schema insert array max_distance toyota avg_distance experience sum
lab4 = schema insert under recent_months olds

auth:
	pgcli -u $(USERNAME) -d $(DATABASE)

init:
	$(DMS) -U $(USERNAME) -qc '\i src/$@.sql'

$(LABS): init
	for script in $($@); do \
		$(DMS) -U me -d $(DATABASE) -qc '\i ./src/$@/'$$script'.sql' ; \
	done

