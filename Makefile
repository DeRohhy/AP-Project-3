MANAGER_DIR = manager
OBSERVER_DIR = observer
CORE_DIR = core

installer.out: main.o CommandParser.o ComponentManager.o Observer.o Component.o Package.o Module.o
	g++ main.o CommandParser.o ComponentManager.o Observer.o Component.o Package.o Module.o -o installer.out

main.o: main.cpp $(MANAGER_DIR)/CommandParser.h $(MANAGER_DIR)/ComponentManager.h
	g++ -c main.cpp -I$(MANAGER_DIR)

ComponentManager.o: $(MANAGER_DIR)/ComponentManager.cpp $(MANAGER_DIR)/ComponentManager.h
	g++ -c $(MANAGER_DIR)/ComponentManager.cpp -I$(MANAGER_DIR)

CommandParser.o: $(MANAGER_DIR)/CommandParser.cpp $(MANAGER_DIR)/CommandParser.h $(MANAGER_DIR)/ComponentManager.h
	g++ -c $(MANAGER_DIR)/CommandParser.cpp -I$(MANAGER_DIR)

Observer.o: ${OBSERVER_DIR}/Observer.cpp ${OBSERVER_DIR}/Observer.h
	g++ -c ${OBSERVER_DIR}/Observer.cpp -I${OBSERVER_DIR}

Component.o: ${CORE_DIR}/Component.cpp ${CORE_DIR}/Component.h
	g++ -c ${CORE_DIR}/Component.cpp -I${CORE_DIR}

Package.o: ${CORE_DIR}/Package.cpp ${CORE_DIR}/Package.h ${CORE_DIR}/Component.h
	g++ -c ${CORE_DIR}/Package.cpp -I${CORE_DIR}

Module.o: ${CORE_DIR}/Module.cpp ${CORE_DIR}/Module.h ${CORE_DIR}/Component.h
	g++ -c ${CORE_DIR}/Module.cpp -I${CORE_DIR}

clean:
	rm -f *.o installer.out
