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
 *      This file implements a "missing" C99 interface for strntoul
 *      which adds a length parameter to the standard strtoul.
 *
 */

#include "strntoul.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>


static int
HandleBase(const char *&aString, const size_t &aLength, const int &aBase)
{
    int lRetval = 0;

    if (aLength > 0)
    {
        if (aBase == 0)
        {
            // If the caller indicated a base of zero (0), then we
            // automatically deduce the base from the content.

            if (*aString == '0')
            {
                // There is a leading zero (0). The content might be octal
                // or hexadecimal.

                aString++;

                // Determine if it is hexadecimal or should be assumed
                // octal.

                if ((aLength > 1) && ((*aString == 'x') || (*aString == 'X')))
                {
                    aString++;
                    lRetval = 16;
                }
                else
                {
                    lRetval = 8;
                }
            }
            else
            {
                lRetval = 10;
            }
        }
        else if (aBase == 16)
        {
            lRetval = aBase;

            // If the caller indicated the content is hexadecimal, then
            // skip any leading '0[xX]', if present.

            if (((aLength > 0) && (aString[0] == '0')) &&
                ((aLength > 1) && ((aString[1] == 'x') || aString[1] == 'X')))
            {
                aString += 2;
            }
        }
        else if ((aBase >=2) && (aBase <= 36))
        {
            lRetval = aBase;
        }
        else
        {
            lRetval = -EINVAL;
        }
    }

    return (lRetval);
}

static unsigned int
GetDigit(const char &aCharacter)
{
    unsigned int lRetval;

    if (isdigit(aCharacter))
    {
        lRetval = static_cast<unsigned int>(aCharacter - '0');
    }
    else if (isalpha(aCharacter))
    {
        if (isupper(aCharacter))
            lRetval = static_cast<unsigned int>((aCharacter - 'A') + 10);
        else if (islower(aCharacter))
            lRetval = static_cast<unsigned int>((aCharacter - 'a') + 10);
        else
            lRetval = INT_MAX;
    }
    else
    {
        lRetval = INT_MAX;
    }

    return (lRetval);
}

static unsigned long
_strntoul(const char *aString, const size_t &aLength, char **aEnd, const int &aBase)
{
    const char *  p               = aString;
    bool          isNegative      = false;
    bool          wouldOverflow   = false;
    bool          convertedDigits = false;
    int           lBase;
    unsigned long lRetval = 0;

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
        if (*p == '-')
        {
            isNegative = true;
            p++;
        }
        else if (*p == '+')
        {
            p++;
        }
    }

    // Handle computing and sanity-checking the base.

    lBase = HandleBase(p, aLength - static_cast<size_t>(p - aString), aBase);
    if (lBase < 0)
    {
        errno   = -lBase;
        lRetval = 0;

        goto done;
    }

    // Begin the conversion, based on the base and the available
    // characters to convert.
    //
    // Special case a few, common power-of-two cases in which the
    // shifts are substantially more efficient than the divides and
    // multiplies required for the shift-and-accumulate conversion
    // algorithm.

    if ((lBase == 2) || (lBase == 8) || (lBase == 16))
    {
        const unsigned      kShift        = ((lBase == 2) ? 1 :
                                             ((lBase == 8) ? 3 : 4));
        const unsigned long lOverflowSentinel = ULONG_MAX >> kShift;

        while (p < (aString + aLength))
        {
            const unsigned int lDigit = GetDigit(*p);

            if (lDigit >= static_cast<unsigned int>(lBase))
                break;

            // Check-and-shift, checking first if the shift would
            // cause an overflow.

            if (lRetval > lOverflowSentinel)
            {
                wouldOverflow = true;
            }

            lRetval <<= kShift;

            // Check-and-accumulate, checking first if the accumulate
            // would cause an overflow.

            if (lDigit > (ULONG_MAX - lRetval))
            {
                wouldOverflow = true;
            }

            lRetval += lDigit;

            convertedDigits = true;

            p++;
        }
    }
    else if ((lBase >= 2) && (lBase <= 36))
    {
        const unsigned long lOverflowSentinel = ULONG_MAX / static_cast<unsigned int>(lBase);

        while (p < (aString + aLength))
        {
            const unsigned int lDigit = GetDigit(*p);

            if (lDigit >= static_cast<unsigned int>(lBase))
                break;

            // Check-and-shift, checking first if the shift would
            // cause an overflow.

            if (lRetval > lOverflowSentinel)
            {
                wouldOverflow = true;
            }

            lRetval *= static_cast<unsigned int>(lBase);

            // Check-and-accumulate, checking first if the accumulate
            // would cause an overflow.

            if (lDigit > (ULONG_MAX - lRetval))
            {
                wouldOverflow = true;
            }

            lRetval += lDigit;

            convertedDigits = true;

            p++;
        }
    }

 done:
    // If no digits were converted, then the standard says that aEnd,
    // if non-null, must be equal to aString.

    if (!convertedDigits)
    {
        p = aString;
    }

    if (aEnd != nullptr)
    {
        *aEnd = const_cast<char *>(p);
    }

    if (wouldOverflow) {
        errno   = ERANGE;
        lRetval = ULONG_MAX;
    }

    if (isNegative) {
        lRetval = -lRetval;
    }

    return (lRetval);
}

/**
 *  @brief
 *    Convert a string to an unsigned long integer.
 *
 *  This function is similar to the C99 standard strtoul, except that
 *  it will use at most @a aLength bytes from @a aString; and @a
 *  aString does @b not need to be null-terminated if it contains @a
 *  aLength or more bytes.
 *
 *  This attempts to convert the initial part of the string in @a
 *  aString to an unsigned long integer value according to @a aBase,
 *  which must be between 2 and 36 inclusive, or be the special value
 *  0 which implies that the base should be automatically-detected
 *  based on the content of @a aString.
 *
 *  @a aString may begin with an arbitrary amount of white space (as
 *  determined by isspace(3)) followed by a single optional '+' or '-'
 *  sign. If base is zero (0) or 16, the string may then include a
 *  "0x" or a "0X" prefix, and the number will be read in base 16
 *  (hexadecimal); otherwise, a zero (0) base is taken as ten (10)
 *  (decimal) unless the next character is '0', in which case it is
 *  taken as eight (8) (octal).
 *
 *  The conversion continues up to @a aLength, a terminating null, or
 *  until an invalid character is encountered for the base, whichever
 *  is less.
 *
 *  If @a aEnd is not null, this stores the address of the first
 *  invalid character in *@a aEnd. If there were no digits at all,
 *  this stores the original value of @a aString in *@a aEnd (and
 *  returns 0). In particular, if *@a aEnd is not null but **@a aEnd
 *  is '\0' or if @a aEnd - @a aString is equal to @a aLength on return,
 *  the entire string is valid and was fully converted.
 *
 *  On error, @a errno may be set as follows:
 *
 *    - EINVAL   @a aBase was an unsupported value.
 *    - ERANGE   The resulting conversion was out of range.
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
 *    Either the result of the conversion or, if there was a leading
 *    minus sign, the negation of the result of the conversion
 *    represented as an unsigned value, unless the original
 *    (nonnegated) value would overflow; in the latter case, this
 *    returns ULONG_MAX and sets @a errno to ERANGE.
 *
 *  @sa strtoul
 *  @sa strntol
 *
 */
unsigned long
strntoul(const char *aString, size_t aLength, char **aEnd, int aBase)
{
    return (_strntoul(aString, aLength, aEnd, aBase));
}
