CXX=g++
CXXFLAGS=-g -std=c++17 -Wall

.PHONY: build
build: main.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -o build/match_engine main.cpp

.PHONY: clean
clean: ## Cleans the build directory
	rm -rf build/*
