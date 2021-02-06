#include "../stm32f4ems/efifeatures.h"

#pragma once

#undef EFI_MEMS
#define EFI_MEMS FALSE

#undef EFI_USB_SERIAL
#define EFI_USB_SERIAL FALSE

#undef EFI_INTERNAL_FLASH
#define EFI_INTERNAL_FLASH FALSE

#undef BOARD_TLE6240_COUNT
#undef BOARD_MC33972_COUNT
#undef BOARD_TLE8888_COUNT
#define BOARD_TLE6240_COUNT	0
#define BOARD_MC33972_COUNT	0
#define BOARD_TLE8888_COUNT 	0

#undef BOARD_EXT_GPIOCHIPS
 #define BOARD_EXT_GPIOCHIPS			(BOARD_TLE6240_COUNT + BOARD_MC33972_COUNT + BOARD_TLE8888_COUNT + BOARD_DRV8860_COUNT + BOARD_MC33810_COUNT)

#undef ENABLE_PERF_TRACE
#define ENABLE_PERF_TRACE FALSE