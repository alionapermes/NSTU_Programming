.PHONY: lab1 lab2 lab3 lab4

USERNAMEX ?= me
DATABASE  ?= v7

DMS   = psql
FLAGS = -U $(USERNAMEX) -d $(DATABASE) -qc

LAB1    = schema insert
LAB2    = role types constraints transaction
LAB3    = table_array insert_array display_array update_array where
LAB4    = join
LABS    = lab1 lab2 lab3
DEFERED = complex
ALL     = $(LAB1) $(LAB2) $(LAB3) $(DEFERED)

#public
auth:
	pgcli -u $(USERNAMEX) -d $(DATABASE)

init:
	$(DMS) -U postgres -qc '\i $@.sql'

all: $(ALL)

$(ALL):
	$(DMS) $(FLAGS) '\i $@.sql'

$(LABS):
	$(MAKE) "_$@" $(DEFERED)

#private
_lab1: init $(LAB1)

_lab2: _lab1 $(LAB2)

_lab3: _lab2 $(LAB3)

