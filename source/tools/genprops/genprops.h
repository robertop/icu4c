/*
*******************************************************************************
*
*   Copyright (C) 1999, International Business Machines
*   Corporation and others.  All Rights Reserved.
*
*******************************************************************************
*   file name:  genprops.h
*   encoding:   US-ASCII
*   tab size:   8 (not used)
*   indentation:4
*
*   created on: 1999dec13
*   created by: Markus W. Scherer
*/

#ifndef __GENPROPS_H__
#define __GENPROPS_H__

#include "utypes.h"

/* file definitions */
#define DATA_NAME "uprops"
#define DATA_TYPE "dat"

/* character properties */
typedef struct {
    uint32_t code, lowerCase, upperCase, titleCase;
    uint32_t decomp[16];
    uint32_t numericValue, denominator;
    uint8_t generalCategory, canonicalCombining, bidi, isMirrored;
} Props;

/* global flags */
extern bool_t beVerbose, haveCopyright;

/* name tables */
extern const char *const
bidiNames[];

extern const char *const
genCategoryNames[];

/* prototypes */
extern void
initStore();

extern void
addProps(Props *p);

extern void
compactStage3();

extern void
compactProps();

extern void
generateData();

#endif
