/*
*******************************************************************************
* Copyright (C) 1997-1999, International Business Machines Corporation and    *
* others. All Rights Reserved.                                                *
*******************************************************************************
*/
//===============================================================================
//
// File colcache.cpp
//
// CollationCache implements a persistent in-memory cache for
// TableCollationData objects.  The goal of CollationCache is to improve
// the memory footprint of a process which may have multiple threads
// loading up the same TableCollation object.  Performance improvement is
// strictly a secondary goal.
//
// Created by: Alan Liu
//
// Modification History:
//
//  Date        Name        Description
//  2/11/97     aliu        Creation.
//  2/12/97     aliu        Modified to work with TableCollationData.
//
//===============================================================================

#include "colcache.h"
#include "tcoldata.h"
#include "uhash.h"

#ifdef COLLDEBUG
#include <iostream.h>
#endif

//--------------------------------------------------------------------------------
// CollationCache implementation
//--------------------------------------------------------------------------------

static void U_CALLCONV deleteTCD(void* TCD)
{
  delete (TableCollationData*)TCD;
}

CollationCache::CollationCache()
{
  UErrorCode err = U_ZERO_ERROR;
  fHashtable = uhash_open((UHashFunction) uhash_hashUString, &err);
  uhash_setValueDeleter(fHashtable, deleteTCD);
}


CollationCache::~CollationCache()
{
  uhash_close(fHashtable);
}

void CollationCache::Add(const UnicodeString& key, TableCollationData* value)
{
  UErrorCode err = U_ZERO_ERROR;
  TableCollationData* previous = (TableCollationData*)uhash_putKey(fHashtable, key.hashCode() & 0x7FFFFFFF , value, &err);
}

TableCollationData* CollationCache::Find(const UnicodeString& keyString)
{
  return (TableCollationData*)uhash_get(fHashtable,keyString.hashCode() & 0x7FFFFFFF);
}

//eof
