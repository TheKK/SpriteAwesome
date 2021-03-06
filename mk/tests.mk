TEST_LIBS := -lgtest -pthread

TEST_SRC_DIR := test

CXXFLAGS += -I $(PWD)/FakeIt/include -I $(PWD)/FakeIt/config/gtest

TEST_SRCS := $(wildcard $(TEST_SRC_DIR)/*.cpp)
TEST_OBJS := $(addprefix $(BUILD_DIR)/, $(TEST_SRCS:.cpp=.o))
TEST_DEPS := $(OBJS:.o=.d)

TEST_RUNNER := $(BUILD_DIR)/$(BIN_DIR)/testRunner

ALL += $(TEST_RUNNER);

testRunner: $(TEST_RUNNER)

$(TEST_RUNNER): $(TEST_OBJS) $(filter-out %main.o, $(OBJS))
	@mkdir -p $(dir $@)
	@$(CXX) $^ $(LIBS) $(TEST_LIBS) -o $@
	@echo "     LD     " $(notdir $@)

.PHONY: runTest cppcheck
runTest: $(TEST_RUNNER)
	@$<

cppcheck:
	@cppcheck --enable=all -q --error-exitcode=123 -I$(INC_DIR) $(SRC_DIR)
