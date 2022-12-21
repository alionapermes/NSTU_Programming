USERNAME ?= postgres
DATABASE ?= v3

DMS   = psql
LABS  = lab1 lab2 lab3 lab4 lab5 lab67 lab8
lab1  = schema insert complex
lab2  = schema insert role constraints transaction
lab3  = schema insert array max_distance toyota avg_distance experience sum
lab4  = schema insert under recent_months olds
lab5  = schema function insert analyze select
lab67 = schema insert log roles analyze index \
		add_functions get_functions delete_functions update_functions
lab8  = schema insert common triggers
cw    = schema insert functions role

meow:
	pgcli -u $(USERNAME) -d $(DATABASE) --echo-all

cw_meow:
	psql -U admin -d v83

init:
	$(DMS) -U $(USERNAME) -qc '\i src/$@.sql'

$(LABS): init
	for script in $($@); do \
		$(DMS) -U me -d $(DATABASE) -qc '\i ./src/$@/'$$script'.sql' ; \
	done

cw:
	$(DMS) -U $(USERNAME) -d postgres -qc '\i ./src/coursework/init.sql'
	for script in $($@); do \
		$(DMS) -U $(USERNAME) -d v83 -qc '\i ./src/coursework/'$$script'.sql'; \
	done

