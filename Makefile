MAKE_DRIVERS 		= ./Drivers/
MAKE_DRIVERS_APPS 	= ./Apps/
MAKE_FUZZY			= ./modules/FuzzyControlAI/
PNG_SERVER_DIR		= ./modules/PngServer/
MAKE_READSTATE 		= ./modules/readSTATE/
MAKE_SMNAVSYS		= ./modules/smartNavSys/
MAKE_BUTTCTRL		= ./modules/buttonsControl/
MAKE_DISTSENS		= ./modules/distanceSensors/

# Colors
WHITE        := $(shell tput -Txterm setaf 7)
RED          := $(shell tput -Txterm setaf 1)

all: 
# Delete gen dir
	@echo "    ${WHITE}:: ${RED}Delete gen dir${RESET} ${WHITE}::${RESET}"
	rm -rf ./gen
# Run makefile to build all drivers	
	@echo "    ${WHITE}:: ${RED}Running drivers Makefile${RESET} ${WHITE}::${RESET}"
	cd $(MAKE_DRIVERS) && $(MAKE)
# Run makefile to build all drivers apps	
	@echo "    ${WHITE}:: ${RED}Running drivers apps Makefile${RESET} ${WHITE}::${RESET}"
	cd $(MAKE_DRIVERS_APPS) && $(MAKE)
# Run makefile to build FuzzyControl	
	@echo "    ${WHITE}:: ${RED}Running FuzzyControl${RESET} ${WHITE}::${RESET}"
	cd $(MAKE_FUZZY) && $(MAKE)
# Run makefile to build readSTATE	
	@echo "    ${WHITE}:: ${RED}Running readSTATE${RESET} ${WHITE}::${RESET}"
# Run makefile to build smartNavSys	
	@echo "    ${WHITE}:: ${RED}Running smartNavSys${RESET} ${WHITE}::${RESET}"
	cd $(MAKE_SMNAVSYS) && $(MAKE)
# Run makefile to build buttonsControl	
	@echo "    ${WHITE}:: ${RED}Running buttonsControl${RESET} ${WHITE}::${RESET}"
	cd $(MAKE_BUTTCTRL) && $(MAKE)
# Run makefile to build distanceSensors	
	@echo "    ${WHITE}:: ${RED}Running distanceSensors${RESET} ${WHITE}::${RESET}"
	cd $(MAKE_DISTSENS) && $(MAKE)

# Copy PNG server to gen dir
	mkdir -p ./gen/PngServer
	cp $(PNG_SERVER_DIR)/pngserver_ShowCam.py ./gen/PngServer
	cp $(PNG_SERVER_DIR)/pngserver_ShowCNN.py ./gen/PngServer
	cp $(MAKE_DRIVERS_APPS)/state.txt ./gen/
	cp scripts/installDrivers.sh ./gen/
	cp scripts/installDrivers.service ./gen/