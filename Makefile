MAKE_DRIVERS 		= ./Drivers/
MAKE_DRIVERS_APPS 	= ./Apps/
MAKE_FUZZY			= ./modules/FuzzyControl/
PNG_SERVER_DIR		= ./modules/PngServer/
MAKE_READSTATE 		= ./modules/readSTATE/

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
	cd $(MAKE_READSTATE) && $(MAKE)
# Copy PNG server to gen dir
	mkdir -p ./gen/PngServer
	cp $(PNG_SERVER_DIR)/pngserver_ShowCam.py ./gen/PngServer
	cp $(PNG_SERVER_DIR)/pngserver_ShowCNN.py ./gen/PngServer
	cp $(MAKE_DRIVERS_APPS)/state.txt ./gen/