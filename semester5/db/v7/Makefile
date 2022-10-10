USERNAME ?= postgres
DATABASE ?= labs

EXEC = psql -U $(USERNAME) -d $(DATABASE) -qc

LAB1    = schema insert
LAB2    = role types constraints transaction
DEFERED = complex
ALL     = $(LAB1) $(LAB2) $(DEFERED)

auth:
	pgcli -u $(USERNAME) -d $(DATABASE)

all: $(ALL)

lab1: $(LAB1) $(DEFERED)

lab2: $(LAB1) $(LAB2) $(DEFERED)

$(ALL):
	$(EXEC) '\i $@.sql'

