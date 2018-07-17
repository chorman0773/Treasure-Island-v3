CURRENT := ./
SOURCE_FILES :=Main.cpp Menu.cpp JTime.cpp ShadowRandom.cpp 
SOURCE_FILES +=Random.cpp Hash.cpp UUID.cpp StringHelper.cpp SHA256.cpp
SOURCE_FILES +=Terminal.cpp TextComponent.cpp
FLAGS := -O0 -fpermissive -Wno-narrowing -I$(CURRENT) 


main: $(SOURCE_FILES)
	g++ $(FLAGS) $(SOURCE_FILES) -o main

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
	