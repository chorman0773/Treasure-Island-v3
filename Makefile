LIBS = -lssl
CURRENT := ./
SOURCE_FILES :=Main.cpp Menu.cpp JTime.cpp ShadowRandom.cpp 
SOURCE_FILES +=Random.cpp Hash.cpp UUID.cpp StringHelper.cpp SHA256.cpp
SOURCE_FILES +=Terminal.cpp TextComponent.cpp
SOURCE_FILES +=Version.cpp Game.cpp
FLAGS := -O3 -fpermissive -Wno-narrowing -I$(CURRENT) 


main: $(SOURCE_FILES)
	g++ $(FLAGS) -o main $(SOURCE_FILES) $(LIBS)

run: main
	./main

debug: main
	gdb main

clean: 
	rm -f main

rebuild:
	make clean
	make main

push:
	