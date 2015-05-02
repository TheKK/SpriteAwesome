ifeq ($(shell which xgettext 2>/dev/null 1>/dev/null || echo 1), 1)
$(error "xgettext was not found")
endif

ifeq ($(shell which msgfmt 2>/dev/null 1>/dev/null || echo 1), 1)
$(error "msgfmt was not found")
endif

PO_DIR = po

POT = $(PO_DIR)/$(PROJECT_NAME).pot
POS = $(wildcard $(PO_DIR)/*.po)
MOS = $(addsuffix /LC_MESSAGES/$(PROJECT_NAME).mo, \
      $(addprefix $(BUILD_DIR)/$(PO_DIR)/, $(notdir $(POS:.po=))))

CXXFLAGS += -DPO_DIR='"$(PWD)/$(BUILD_DIR)/$(PO_DIR)"'

ALL += l10n

l10n: $(POT) $(MOS)

$(PO_DIR)/$(PROJECT_NAME).pot: $(SRCS) $(INCS)
	@echo "     POT    " $(notdir $@)
	@mkdir -p $(PO_DIR)
	@xgettext $(SRC_DIR)/* $(INC_DIR)/* -k_ -o $(PO_DIR)/$(PROJECT_NAME).pot

$(BUILD_DIR)/$(PO_DIR)/%/LC_MESSAGES/$(PROJECT_NAME).mo: $(PO_DIR)/%.po
	@echo "     MO     " $@
	@mkdir -p $(dir $@)
	@msgfmt $< -o $@
