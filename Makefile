# Check if pkg-config is installed, we need it for building CFLAGS/LIBS
ifeq ($(shell which pkg-config 2>/dev/null 1>/dev/null || echo 1), 1)
$(error "pkg-config was not found")
endif

PROJECT_NAME := spriteAwesome

CXX := g++
CXXFLAGS += -std=c++11 -g
CXXFLAGS += -Wall -Wextra
CXXFLAGS += -MMD -MP
CXXFLAGS += -DPROJECT_NAME='"$(PROJECT_NAME)"'
CXXFLAGS += $(shell pkg-config --cflags sdl2 SDL2_image)
LIBS += $(shell pkg-config --libs sdl2 SDL2_image)

SRC_DIR := src
INC_DIR := inc
BUILD_DIR := build
BIN_DIR := bin

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
INCS := $(wildcard $(INC_DIR)/*.h)
OBJS := $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))
DEPS := $(OBJS:.o=.d)

OUT_EXE := $(BUILD_DIR)/$(BIN_DIR)/$(PROJECT_NAME)

ALL += $(OUT_EXE)

# XXX Must have more elegant way to add l10n as default
default: $(OUT_EXE) l10n

include $(wildcard mk/*.mk)

$(OUT_EXE): $(OBJS)
	@mkdir -p $(dir $@)
	@$(CXX) $^ $(LIBS) -o $@
	@echo "     LD     " $(notdir $@)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -I $(INC_DIR) -c $< -o $@
	@echo "     CXX    " $(notdir $@)

.PHONY: all clean
all: $(ALL)

clean:
	@rm -frv $(BUILD_DIR)

-include $(DEPS)
