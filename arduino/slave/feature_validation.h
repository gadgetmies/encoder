#pragma once

#ifndef SKIP_FEATURE_VALIDATION

#include "slave.h"

#define ASSERT_BOARD_FEATURE(BOARD, FEATURE) static_assert(!HAS_##FEATURE(BOARD), #FEATURE " not allowed on " #BOARD);

ASSERT_BOARD_FEATURE(L2, PADS);
ASSERT_BOARD_FEATURE(R2, PADS);
#if PCB_VERSION != 3
ASSERT_BOARD_FEATURE(L2, BUTTON);
ASSERT_BOARD_FEATURE(R2, BUTTON);
#endif
ASSERT_BOARD_FEATURE(L2, TOUCH);
ASSERT_BOARD_FEATURE(R2, TOUCH);

// Button matrix only possible on R1 and L1
#if PCB_VERSION == 3
ASSERT_BOARD_FEATURE(M1, MATRIX);
ASSERT_BOARD_FEATURE(M2, MATRIX);
#else
ASSERT_BOARD_FEATURE(M, MATRIX);
#endif
ASSERT_BOARD_FEATURE(R2, MATRIX);
ASSERT_BOARD_FEATURE(L2, MATRIX);

#define ASSERT_MATRIX(BOARD) \
static_assert(!HAS_MATRIX(BOARD) || (BOARD_FEATURES_##BOARD == BOARD_FEATURE_MATRIX), "Button matrix board cannot have any other features!");
ASSERT_MATRIX(L1);
ASSERT_MATRIX(R1);

#define BOTH_FEATURES(FEATURE1, FEATURE2) (BOARD_FEATURE_##FEATURE1 | BOARD_FEATURE_##FEATURE2)
// TODO: how is this different from HAS_FEATURE in slave.h?
#define HAS_FEATURES(BOARD, FEATURES) ((BOARD_FEATURES_##BOARD & FEATURES) == FEATURES)

#define ASSERT_FEATURE_COMBINATION(BOARD, FEATURE1, FEATURE2) \
static_assert(!HAS_FEATURES(BOARD, BOTH_FEATURES(FEATURE1, FEATURE2)), #BOARD " cannot have features " #FEATURE1 " and " #FEATURE2 " at the same time!");

#define SHARED_INVALID_COMBINATION_ASSERTS(BOARD) \
ASSERT_FEATURE_COMBINATION(BOARD, POT, PADS)\
ASSERT_FEATURE_COMBINATION(BOARD, POT, ENCODER)\
ASSERT_FEATURE_COMBINATION(BOARD, POT, BUTTON)\
ASSERT_FEATURE_COMBINATION(BOARD, PADS, ENCODER)\
ASSERT_FEATURE_COMBINATION(BOARD, PADS, TOUCH)\
ASSERT_FEATURE_COMBINATION(BOARD, PADS, BUTTON)

//SHARED_INVALID_COMBINATION_ASSERTS(M)
//SHARED_INVALID_COMBINATION_ASSERTS(L1)
//SHARED_INVALID_COMBINATION_ASSERTS(R1)
//
//ASSERT_FEATURE_COMBINATION(L1, TOUCH, BUTTON)
//ASSERT_FEATURE_COMBINATION(R1, TOUCH, BUTTON)

// TODO: should these fail the build or just disable the features?
#ifdef USART_DEBUG_ENABLED
#if PCB_VERSION == 1
static_assert(!HAS_FEATURE(M, BOARD_FEATURE_PADS), "Cannot use PADS on M when USART_DEBUG_ENABLED");
static_assert(!HAS_FEATURE(M, BOARD_FEATURE_ENCODER), "Cannot use ENCODER on M when USART_DEBUG_ENABLED");
#elif PCB_VERSION == 2
static_assert(!HAS_FEATURE(M, BOARD_FEATURE_PADS), "Cannot use PADS on M when USART_DEBUG_ENABLED");
static_assert(!HAS_FEATURE(L2, BOARD_FEATURE_TOUCH), "Cannot use TOUCH on L2 when USART_DEBUG_ENABLED");
#endif
#if PCB_VERSION == 2 || PCB_VERSION == 3
static_assert(!HAS_FEATURE(L2, BOARD_FEATURE_ENCODER), "Cannot use ENCODER on L2 when USART_DEBUG_ENABLED");
#endif
#endif

#ifdef USE_DEBUG_LED
#if PCB_VERSION == 3
static_assert(!HAS_FEATURE(R2, BOARD_FEATURE_ENCODER), "Cannot use ENCODER on R2 when USE_DEBUG_LED");
static_assert(!HAS_FEATURE(R1, BOARD_FEATURE_MATRIX), "Cannot use MATRIX on R1 when USE_DEBUG_LED");
// TODO: add TOUCH when implemented
#else
static_assert(false, "USE_DEBUG_LED only available on PCB_VERSION 3");
#endif
#endif

#endif
