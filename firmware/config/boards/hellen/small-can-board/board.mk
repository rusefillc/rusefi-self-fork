BOARDCPPSRC = $(BOARD_DIR)/board_configuration.cpp

DDEFS += -DFIRMWARE_ID=\"small-can-board\"
DDEFS += -DSHORT_BOARD_NAME=small-can-board -DSTATIC_BOARD_ID=STATIC_BOARD_ID_SMALL_CAN_BOARD

#DDEFS += -DEFI_SENT_SUPPORT=TRUE

DDEFS += -DPERSISTENT_LOCATION_VALUE=\"__attribute__\(\(section\(\\\".ram1\\\"\)\)\)\"
DDEFS += -DPERSISTENT_LOCATION_TODO
DDEFS += -DEFI_SENSOR_CHART=FALSE
DDEFS += -DLUA_USER_HEAP=50000
DDEFS += -DEFI_MC33816=FALSE
DDEFS += -DEFI_IDLE_CONTROL=FALSE
DDEFS += -DDL_OUTPUT_BUFFER=1000
DDEFS += -DEFI_LOGIC_ANALYZER=FALSE
DDEFS += -DEFI_MALFUNCTION_INDICATOR=FALSE
DDEFS += -DEFI_ENGINE_SNIFFER=FALSE
DDEFS += -DEFI_TCU=FALSE
DDEFS += -DEFI_ENGINE_EMULATOR=FALSE
DDEFS += -DEFI_SHAFT_POSITION_INPUT=FALSE
DDEFS += -DEFI_ALTERNATOR_CONTROL=FALSE
DDEFS += -DEFI_VVT_PID=FALSE
DDEFS += -DEFI_EMULATE_POSITION_SENSORS=FALSE
DDEFS += -DEFI_MAP_AVERAGING=FALSE
DDEFS += -DEFI_HPFP=FALSE
DDEFS += -DEFI_TOOTH_LOGGER=FALSE
DDEFS += -DRAM_UNUSED_SIZE=100

DDEFS += -DHW_SMALL_CAN_BOARD=1
DDEFS += -DHELLEN_BOARD_ID_DEBUG

#Mass Storage
DDEFS += -DEFI_EMBED_INI_MSD=FALSE

#DDEFS += $(PRIMARY_COMMUNICATION_PORT_USART3)

#DDEFS += -DEFI_KLINE=TRUE
DDEFS += -DKLINE_SERIAL_DEVICE_RX=Gpio::С7 -DKLINE_SERIAL_DEVICE_TX=Gpio::С6
DDEFS += -DKLINE_SERIAL_DEVICE=SD6
DDEFS += -DSTM32_SERIAL_USE_USART6=TRUE

include $(BOARDS_DIR)/hellen/hellen-common64.mk
