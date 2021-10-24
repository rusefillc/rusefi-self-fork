/*
 * @file engine_types.h
 *
 * @date Oct 23, 2021
 * @author Andrey Belomutskiy, (c) 2012-2021
 */

#pragma once

#include "rusefi_generated.h"


/**
 * http://rusefi.com/wiki/index.php?title=Manual:Engine_Type
 */
typedef enum {
	DEFAULT_FRANKENSO = ET_DEFAULT_FRANKENSO,

	MIATA_PROTEUS_TCU = 1,

	/**
	 * 1995 Dodge Neon
	 * http://rusefi.com/forum/viewtopic.php?t=360
	 */
	DODGE_NEON_1995 = 2,
	/**
	 * 1996 1.3 Ford Aspire
	 * http://rusefi.com/forum/viewtopic.php?t=375
	 */
	FORD_ASPIRE_1996 = 3,
	UNUSED5 = 4,

	NISSAN_PRIMERA = 5,
	ET_UNUSED_6 = 6,
	FORD_INLINE_6_1995 = 7,
	/**
	 * one cylinder engine
	 * 139qmb 50-90cc
	 * http://rusefi.com/forum/viewtopic.php?f=3&t=332
	 */
	GY6_139QMB = 8,

	MAZDA_MIATA_NB1 = 9,
	UNUSED10 = 10,
	MRE_MIATA_NB2_MAP = ET_MRE_MIATA_NB2_MAP,
	MRE_MIATA_NA6_VAF = ET_MRE_MIATA_NA6_VAF,
	MRE_MIATA_NB2_ETB = 13,
	MRE_MIATA_NA6_MAP = ET_MRE_MIATA_NA6_MAP,
	MRE_MIATA_NB2_MAF = ET_MRE_MIATA_NB2_MAF,

	// Frankenstein board
	MIATA_1990 = 19,
	// Frankenso board
	FRANKENSO_MIATA_NA6_MAP = 41,
	MRE_MIATA_94_MAP = ET_MRE_MIATA_94_MAP,
	MIATA_1996 = 21,

	FORD_ESCORT_GT = ET_FORD_ESCORT_GT,


	MITSU_4G93 = 16,

	/**
	 * a version of HONDA_ACCORD_CD which only uses two of three trigger input sensors
	 */
	HONDA_ACCORD_CD_TWO_WIRES = 17,

	HONDA_ACCORD_CD_DIP = 18,


	SUBARU_2003_WRX = 22,

	/**
	 * microRusEFI used as Body Control Module BCM BCU
	 */
	MRE_BODY_CONTROL = ET_MRE_BODY_CONTROL,
	BMW_M73_M = 24,

UNUSED25 = 25,
	TEST_ENGINE = 26,

	// used by unit test
	// see https://github.com/rusefi/rusefi/issues/898
	// see TriggerWaveform::bothFrontsRequired
	TEST_ISSUE_898 = 27,

	MAZDA_626 = 28,

	SACHS = ET_SACHS,

	// LED physical order set for older test fixtures
	MRE_BOARD_OLD_TEST = 30,

	MRE_BOARD_NEW_TEST = 31,

	VW_ABA = 32,

	HELLEN72_ETB = 33,

	HELLEN_NA6 = ET_HELLEN_NA6,

	CAMARO_4 = 35,

	HELLEN_128_MERCEDES_4_CYL = ET_HELLEN_128_MERCEDES_4_CYL,

	MRE_SUBARU_EJ18 = ET_MRE_SUBARU_EJ18,

	TOYOTA_JZS147 = 38, // 2JZ-GTE NON VVTi

	LADA_KALINA = 39,

	FRANKENSO_BMW_M73_F = ET_BMW_M73_F,

	PROTEUS_QC_TEST_BOARD = ET_PROTEUS_QC_TEST_BOARD,

	HONDA_600 = 43,

	TOYOTA_2JZ_GTE_VVTi = 44,

	TEST_ENGINE_VVT = 45,

	DODGE_NEON_2003_CRANK = 46,

	/**
	 * proper NB2 setup, 2003 red test mule car
	 */
	FRANKENSO_MAZDA_MIATA_2003 = ET_FRANKENSO_MIATA_NB2,

	UNUSED_48 = 48,

	FRANKENSO_QA_ENGINE = 49,

	UNUSED_50 = 50,

	UNUSED_51 = 51,


	TEST_ISSUE_366_BOTH = 52,
	TEST_ISSUE_366_RISE = 53,

	/**
	 * green Hunchback race car - VVT engine on a NA body with NA return fuel lines which
	 * means different fuel pressure situation
	 */
	MAZDA_MIATA_2003_NA_RAIL = 54,

	MAZDA_MIATA_2003_BOARD_TEST = 55,

	FRANKENSO_MAZDA_MIATA_NA8 = 56,

	FRANKENSO_MIATA_NA6_VAF = ET_FRANKENSO_MIATA_NA6_VAF,

	ETB_BENCH_ENGINE = 58,

	TLE8888_BENCH_ENGINE = 59,

	MICRO_RUS_EFI = ET_MRE_DEFAULTS,

	PROTEUS_DEFAULTS = 61,

	PROTEUS_ANALOG_PWM_TEST = ET_PROTEUS_ANALOG_PWM_TEST,

	VW_B6 = ET_VW_B6,

	PROTEUS_BMW_M73 = 63,

	DODGE_RAM = 64,
	CITROEN_TU3JP = ET_CITROEN_TU3JP,

	PROTEUS_MIATA_NB2 = 67,
	MRE_M111 = 68,

	HELLEN_NB2 = 69,

	SUBARUEG33_DEFAULTS = 70,

	HELLEN_121_VAG = ET_HELLEN_121_VAG,
	HELLEN_121_NISSAN_6_CYL = ET_HELLEN_121_NISSAN_6_CYL,
	HELLEN_55_BMW = ET_HELLEN_55_BMW,
	HELLEN_88_BMW = ET_HELLEN_88_BMW,
	HELLEN_134_BMW = ET_HELLEN_134_BMW,
	HELLEN_154_VAG = ET_HELLEN_154_VAG,

	HELLEN_121_VAG_5_CYL = ET_HELLEN_121_VAG_5_CYL,
	HELLEN_121_VAG_V6_CYL = ET_HELLEN_121_VAG_V6_CYL,
	HELLEN_121_VAG_VR6_CYL = ET_HELLEN_121_VAG_VR6_CYL,
	HELLEN_121_VAG_8_CYL = ET_HELLEN_121_VAG_8_CYL,

	HELLEN_NA94 = ET_HELLEN_NA94,

    // 82
	HELLEN_154_HYUNDAI_COUPE_BK1 = ET_HELLEN_154_HYUNDAI_COUPE_BK1,
	HELLEN_NB1 = ET_HELLEN_NB1,
	// 84
	HELLEN_121_NISSAN_4_CYL = ET_HELLEN_121_NISSAN_4_CYL,

    HELLEN_121_NISSAN_8_CYL = 85,

	HELLEN_NB2_36 = 86,

	HELLEN_121_NISSAN_ALMERA_N16  = 87,

	HELLEN_128_MERCEDES_6_CYL = ET_HELLEN_128_MERCEDES_6_CYL,

	HELLEN_128_MERCEDES_8_CYL = ET_HELLEN_128_MERCEDES_8_CYL,

	PROTEUS_HONDA_ELEMENT_2003 = 90,

	PROTEUS_HONDA_OBD2A = 91,

	PROTEUS_VAG_80_18T = ET_PROTEUS_VAG_80_18T,

	PROTEUS_N73 = ET_PROTEUS_N73,

    HELLEN_NB1_36 = 94,

	HELLEN_154_HYUNDAI_COUPE_BK2 = ET_HELLEN_154_HYUNDAI_COUPE_BK2,

    ET_UNUSED96 = 96,
    ET_UNUSED97 = 97,
    ET_UNUSED98 = 98,

	/**
	 * this configuration has as few pins configured as possible
	 */
	MINIMAL_PINS = 99,
	PROMETHEUS_DEFAULTS = 100,
	SUBARUEJ20G_DEFAULTS = 101,
	VAG_18_TURBO = 102,

	TEST_33816 = 103,

	BMW_M73_MRE = 104,
	BMW_M73_MRE_SLAVE = 105,

	TEST_ROTARY = ET_TEST_ROTARY,

	TEST_108 = 108,
	TEST_109 = 109,
	TEST_110 = 110,

	Force_4_bytes_size_engine_type = ENUM_32_BITS,
} engine_type_e;

/**
 * https://rusefi.com//wiki/index.php?title=Manual:Debug_fields
 */
typedef enum {
	DBG_ALTERNATOR_PID = 0,
	DBG_TPS_ACCEL = 1,
	DBG_GPPWM = 2,
	DBG_IDLE_CONTROL = 3,
	DBG_EL_ACCEL = 4,
	DBG_TRIGGER_COUNTERS = 5,
	DBG_UNUSED_6 = 6,
	DBG_VVT_1_PID = 7,
	/**
	 * VVT position debugging - not VVT valve control. See AUX pid #1 debug for valve position.
	 */
	DBG_VVT = 8,
	DBG_CRANKING_DETAILS = 9,
	DBG_IGNITION_TIMING = 10,
	DBG_FUEL_PID_CORRECTION = 11,
	DBG_UNUSED12 = 12,
	DBG_SD_CARD = 13,
	DBG_SR5_PROTOCOL = 14,
	DBG_KNOCK = 15,
	DBG_WALL_WETTING = 16,
	/**
	 * See also DBG_ELECTRONIC_THROTTLE_EXTRA
	 */
	DBG_ELECTRONIC_THROTTLE_PID = 17,
	DBG_EXECUTOR = 18,
	/**
	 * See tunerstudio.cpp
	 */
	DBG_BENCH_TEST = 19,
	DBG_AUX_VALVES = 20,
	/**
	 * ADC
	 * See also DBG_ANALOG_INPUTS2
	 */
	DBG_ANALOG_INPUTS = 21,

	DBG_INSTANT_RPM = 22,
	UNUSED23 = 23,
	DBG_STATUS = 24,
	DBG_CJ125 = 25,
	DBG_CAN = 26,
	DBG_MAP = 27,
	DBG_METRICS = 28,
	DBG_ELECTRONIC_THROTTLE_EXTRA = 29,
	DBG_ION = 30,
	DBG_TLE8888 = 31,
	/**
	 * See also DBG_ANALOG_INPUTS
	 */
	DBG_ANALOG_INPUTS2 = 32,
	DBG_DWELL_METRIC = 33,
	DBG_34 = 34,
	DBG_ETB_LOGIC = 35,
	DBG_BOOST = 36,
	DBG_START_STOP = 37,
	DBG_LAUNCH = 38,
	DBG_ETB_AUTOTUNE = 39,
	DBG_COMPOSITE_LOG = 40,
	DBG_UNUSED41 = 41,
	DBG_UNUSED_42 = 42,
	DBG_INJECTOR_COMPENSATION = 43,
	DBG_DYNO_VIEW = 44,
	DBG_LOGIC_ANALYZER = 45,
	DBG_RUSEFI_WIDEBAND = 46,
	DBG_TCU = 47,
	DBG_LUA = 48,
	DBG_VVT_2_PID = 49,
	DBG_VVT_3_PID = 50,
	DBG_VVT_4_PID = 51,
	MODE_52 = 52,
	MODE_53 = 53,

	Force_4_bytes_size_debug_mode_e = ENUM_32_BITS,
} debug_mode_e;

