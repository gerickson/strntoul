/*
 *    Copyright (c) 2021 Grant Erickson
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing,
 *    software distributed under the License is distributed on an "AS
 *    IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 *    express or implied.  See the License for the specific language
 *    governing permissions and limitations under the License.
 *
 */

/**
 *    @file
 *      This file implements a "missing" C99 interface for strntol which
 *      adds a length parameter to the standard strtol.
 *
 */

#include "strntol.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>

#include "strntoul.h"

static long
_strntol(const char *aString, const size_t &aLength, char **aEnd, const int &aBase)
{
    const char *  p             = aString;
    bool          calledStrtoul = false;
    bool          isNegative    = false;
    signed long   lRetval       = 0;


    if (aLength == 0)
    {
        goto done;
    }

    // Skip any leading space and determine the sign, if any.

    while ((p < (aString + aLength)) && isspace(*p))
    {
        p++;
    }

    if (p < (aString + aLength))
    {
        unsigned long lResult;

        if (*p == '-')
        {
            isNegative = true;

            p++;

            lResult = strntoul(p,
                               aLength - static_cast<size_t>(p - aString),
                               aEnd,
                               aBase);
            lRetval = static_cast<long>(-lResult);
        }
        else
        {
            if (*p == '+')
            {
                p++;
            }

            lResult = strntoul(p,
                               aLength - static_cast<size_t>(p - aString),
                               aEnd,
                               aBase);
            lRetval = static_cast<long>(lResult);
        }

        calledStrtoul = true;
    }

 done:
    // If no digits were converted, then the standard says that aEnd,
    // if non-null, must be equal to aString.

    if ((lRetval == 0) && ((aEnd != nullptr) && (!calledStrtoul || (p == *aEnd))))
    {
        *aEnd = const_cast<char *>(aString);
    }

    // If the correct value is outside the range of representable
    // values, the standards says LONG_MIN or LONG_MAX shall be
    // returned (according to the sign of the value), and errno set to
    // ERANGE (which was set from strtoul).

    if (errno == ERANGE)
    {
        lRetval = (isNegative) ? LONG_MIN : LONG_MAX;
    }

    return (lRetval);
}

/**
 *  @brief
 *    Convert a string to an long integer.
 *
 *  This function is similar to the C99 standard strtol, except that
 *  it will use at most @a aLength bytes from @a aString; and @a
 *  aString does @b not need to be null-terminated if it contains @a
 *  aLength or more bytes.
 *
 *  This attempts to convert the initial part of the string in @a
 *  aString to a long integer value according to @a aBase, which must
 *  be between 2 and 36 inclusive, or be the special value 0 which
 *  implies that the base should be automatically-detected based on
 *  the content of @a aString.
 *
 *  The conversion continues up to @a aLength, a terminating null, or
 *  until an invalid character is encountered, whichever is less.
 *
 *  @param[in]   aString  A pointer to the string to convert.
 *  @param[in]   aLength  The maximum number of characters, in bytes,
 *                        of @a aString to process.
 *  @param[out]  aEnd     A pointer to storage for the first invalid
 *                        or the last valid character in @a aString.
 *  @param[in]   aBase    The base to use to interpret @a aString for
 *                        the conversion in the range 2 to 36,
 *                        inclusive.
 *
 *  @returns
 *    The result of the conversion, unless the value would underflow
 *    or overflow. If an underflow occurs, this returns LONG_MIN. If
 *    an overflow occurs, this returns LONG_MAX. In both cases, errno
 *    is set to ERANGE.
 *
 *  @sa strtol
 *  @sa strntoul
 *
 */
long
strntol(const char *aString, size_t aLength, char **aEnd, int aBase)
{
    return (_strntol(aString, aLength, aEnd, aBase));
}
