/*
* Copyright (C) 2001, International Business Machines Corporation and others. All Rights Reserved.
**********************************************************************
*   Date        Name        Description
*   07/18/01    aliu        Creation.
**********************************************************************
*/

#include "unicode/unifilt.h"
#include "unicode/rep.h"
#include "rbt_rule.h"

/**
 * Default implementation of UnicodeMatcher::matches() for Unicode
 * filters.  Matches a single 16-bit code unit at offset.
 */
UMatchDegree UnicodeFilter::matches(const Replaceable& text,
                                    int32_t& offset,
                                    int32_t limit,
                                    UBool incremental) const {
    UChar32 c;
    if (offset < limit &&
        contains(c = text.char32At(offset))) {
        offset += UTF_CHAR_LENGTH(c);
        return U_MATCH;
    }
    if (offset > limit &&
        contains(c = text.char32At(offset))) {
        // Backup offset by 1, unless the preceding character is a
        // surrogate pair -- then backup by 2 (keep offset pointing at
        // the lead surrogate).
        --offset;
        if (offset >= 0) {
            offset -= UTF_CHAR_LENGTH(text.char32At(offset)) - 1;
        }
        return U_MATCH;
    }
    if (incremental && offset == limit) {
        return U_PARTIAL_MATCH;
    }
    return U_MISMATCH;
}
