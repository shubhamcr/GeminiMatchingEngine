CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -Wextra -pthread

SRC_DIR = .
SRC_HEADERS = $(SRC_DIR)/*.h
BUILD_DIR = ./build

create_build_dir :
	mkdir -p $(BUILD_DIR)

.PHONY: build
build : create_build_dir main.cpp $(SRC_HEADERS)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/match_engine main.cpp

.PHONY: clean
clean : ## Cleans the build directory
	rm -rf $(BUILD_DIR)/*


# Points to the root of Google Test, relative to where this file is.
GTEST_DIR = ../googletest/googletest

USER_TEST_DIR = $(SRC_DIR)/test

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# All Google Test headers.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc -o $(BUILD_DIR)/gtest-all.o

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc -o $(BUILD_DIR)/gtest_main.o

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $(BUILD_DIR)/gtest.a $(BUILD_DIR)/gtest-all.o

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $(BUILD_DIR)/gtest_main.a $(BUILD_DIR)/gtest-all.o $(BUILD_DIR)/gtest_main.o


matchine_engine_test.o : $(USER_TEST_DIR)/MatchingEngine.t.cpp $(SRC_HEADERS) $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(SRC_DIR) -c $(USER_TEST_DIR)/MatchingEngine.t.cpp \
			-o $(BUILD_DIR)/matchine_engine_test.o

price_bucket_test.o : $(USER_TEST_DIR)/PriceBucket.t.cpp $(SRC_HEADERS) $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(SRC_DIR) -c $(USER_TEST_DIR)/PriceBucket.t.cpp \
			-o $(BUILD_DIR)/price_bucket_test.o

order_book_test.o : $(USER_TEST_DIR)/OrderBook.t.cpp $(SRC_HEADERS) $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(SRC_DIR) -c $(USER_TEST_DIR)/OrderBook.t.cpp \
			-o $(BUILD_DIR)/order_book_test.o

test : create_build_dir gtest_main.a matchine_engine_test.o price_bucket_test.o order_book_test.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $(BUILD_DIR)/gtest_main.a \
			$(BUILD_DIR)/matchine_engine_test.o \
			$(BUILD_DIR)/price_bucket_test.o \
			$(BUILD_DIR)/order_book_test.o \
			-o $(BUILD_DIR)/match_engine_test