#My general makefile template
CXX=gcc
CFLAGS = -Wall -Werror -pedantic -I.

#application-related macros
TARGET = Projet
SOURCEFILE = Projet

#Generating the executable
$(TARGET): $(SOURCEFILE).o
	@echo "Generating the executable" $@
	$(CXX) $(CFLAGS) $(SOURCEFILE).o -o $@

$(SOURCEFILE).o: clean
	@echo "Generating" $@
	$(CXX) $(CFLAGS) -c $(SOURCEFILE).c -o $@

clean:
	@echo "Cleaning temporary files"
	rm -rf $(TARGET) $(SOURCEFILE).o

run:	
	./$(TARGET)

