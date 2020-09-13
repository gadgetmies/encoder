#pragma once

#include "avr/io.h"

#define NO_FEATURES (0)
#define BOARD_FEATURE_ENCODER _BV(0)
#define BOARD_FEATURE_BUTTON _BV(1)
#define BOARD_FEATURE_POT _BV(2)
#define BOARD_FEATURE_TOUCH _BV(3)
#define BOARD_FEATURE_PADS _BV(4)
#define BOARD_FEATURE_LED _BV(5)
#define BOARD_FEATURE_MATRIX _BV(6)

#define HAS_FEATURE(BOARD, feature) (BOARD_FEATURES_##BOARD & feature)
#define HAS_PADS(BOARD) (HAS_FEATURE(BOARD, BOARD_FEATURE_PADS))
#define HAS_POT(BOARD) (HAS_FEATURE(BOARD, BOARD_FEATURE_POT))
#define HAS_BUTTON(BOARD) (HAS_FEATURE(BOARD, BOARD_FEATURE_BUTTON))
#define HAS_TOUCH(BOARD) (HAS_FEATURE(BOARD, BOARD_FEATURE_TOUCH))
#define HAS_LED(BOARD) (HAS_FEATURE(BOARD, BOARD_FEATURE_LED))
#define HAS_MATRIX(BOARD) (HAS_FEATURE(BOARD, BOARD_FEATURE_MATRIX))

#if PCB_VERSION == 3
#define ANY_BOARD_HAS_FEATURE(FEATURE) (HAS_FEATURE(L2, FEATURE) || HAS_FEATURE(L1, FEATURE) || HAS_FEATURE(M1, FEATURE) || HAS_FEATURE(M2, FEATURE) || HAS_FEATURE(R1, FEATURE) || HAS_FEATURE(R2, FEATURE))
#else
#define ANY_BOARD_HAS_FEATURE(FEATURE) (HAS_FEATURE(L2, FEATURE) || HAS_FEATURE(L1, FEATURE) || HAS_FEATURE(M, FEATURE) || HAS_FEATURE(R1, FEATURE) || HAS_FEATURE(R2, FEATURE))
#endif
