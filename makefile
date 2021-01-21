TARGET_EXEC ?= GraphVisualizer				# nazwa programu

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src/*

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CC = g++

LDFLAGS ?= -lsfml-graphics -lsfml-window -lsfml-system	# -lpthread <- dołączenie bibliotek 
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++17 	# -O3	<- dowolne flagi kompilacji

$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
