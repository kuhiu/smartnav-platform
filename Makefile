MAKE_DRIVERS = ./Drivers/

WHITE        := $(shell tput -Txterm setaf 7)
RED          := $(shell tput -Txterm setaf 1)

all: 
# Delete gen dir
	@echo "    ${WHITE}:: ${RED}Delete gen dir${RESET} ${WHITE}::${RESET}"
	rm -rf ./gen
# Run makefile to build all drivers	
	@echo "    ${WHITE}:: ${RED}Running drivers Makefile${RESET} ${WHITE}::${RESET}"
	cd $(MAKE_DRIVERS) && $(MAKE)

