MANAGER_DIR = manager

installer.out: main.o CommandParser.o ComponentManager.o
	g++ main.o CommandParser.o ComponentManager.o -o installer.out

main.o: main.cpp $(MANAGER_DIR)/CommandParser.h $(MANAGER_DIR)/ComponentManager.h
	g++ -c main.cpp -I$(MANAGER_DIR)

ComponentManager.o: $(MANAGER_DIR)/ComponentManager.cpp $(MANAGER_DIR)/ComponentManager.h
	g++ -c $(MANAGER_DIR)/ComponentManager.cpp -I$(MANAGER_DIR)

CommandParser.o: $(MANAGER_DIR)/CommandParser.cpp $(MANAGER_DIR)/CommandParser.h $(MANAGER_DIR)/ComponentManager.h
	g++ -c $(MANAGER_DIR)/CommandParser.cpp -I$(MANAGER_DIR)

clean:
	rm -f *.o installer.out
