# Combine the related files for a specific platform and MCU.

# Target ECU board design
BOARDCPPSRC = $(BOARDS_DIR)/hellen/hellen72/board_configuration.cpp
BOARDINC = $(BOARDS_DIR)/hellen/hellen72

# Set this if you want a default engine type other than normal Hellen72
ifeq ($(DEFAULT_ENGINE_TYPE),)
  DEFAULT_ENGINE_TYPE = -DDEFAULT_ENGINE_TYPE=HELLEN_NB2
endif

ifeq ($(LED_CRITICAL_ERROR_BRAIN_PIN),)
  LED_CRITICAL_ERROR_BRAIN_PIN = -DLED_CRITICAL_ERROR_BRAIN_PIN=GPIOH_8
endif

ifeq ($(LED_COMMUNICATION_BRAIN_PIN),)
  LED_COMMUNICATION_BRAIN_PIN = -DEFI_COMMUNICATION_PIN=GPIOH_10
endif

DDEFS += -DEFI_MAIN_RELAY_CONTROL=TRUE

DDEFS += -DLED_ERROR_BRAIN_PIN_MODE=INVERTED_OUTPUT
DDEFS += -DLED_RUNING_BRAIN_PIN_MODE=INVERTED_OUTPUT
DDEFS += -DLED_WARNING_BRAIN_PIN_MODE=INVERTED_OUTPUT
DDEFS += -DLED_COMMUNICATION_BRAIN_PIN_MODE=INVERTED_OUTPUT

# Add them all together
DDEFS += -DEFI_USE_OSC=TRUE -DFIRMWARE_ID=\"hellen72\" $(DEFAULT_ENGINE_TYPE) $(LED_CRITICAL_ERROR_BRAIN_PIN) $(LED_COMMUNICATION_BRAIN_PIN)
# -DEFI_SOFTWARE_KNOCK=TRUE -DSTM32_ADC_USE_ADC3=TRUE
DDEFS += -DEFI_ICU_INPUTS=FALSE -DHAL_TRIGGER_USE_PAL=TRUE -DHAL_VSS_USE_PAL=TRUE 
# todo: is it broken?
DDEFS += -DEFI_LOGIC_ANALYZER=FALSE

# USB mass storage support
DDEFS += -DHAL_USE_COMMUNITY=TRUE -DHAL_USE_USB_MSD=TRUE

# We are running on Hellen-One hardware!
DDEFS += -DHW_HELLEN=1

# Shared variables
ALLCPPSRC += $(BOARDCPPSRC)
ALLINC    += $(BOARDINC)
