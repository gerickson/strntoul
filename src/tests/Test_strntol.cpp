/*
 *    Copyright (c) 2021-2024 Grant Erickson
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
 *      This file implements a unit test for strntol.
 *
 */

#include <utility>

#include <errno.h>
#include <limits.h>
#include <string.h>

#include <nlunit-test.h>

#include <strntol.h>


static void TestInvalidBases(nlTestSuite *inSuite __attribute__((unused)),
                             void *inContext __attribute__((unused)))
{
    signed long lResult;

    // A base of 1, just under the valid range, should fail

    errno = 0;

    lResult = strntol("10", 2, nullptr, 1);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, errno == EINVAL);

    // A base of 37, just above the valid range, should fail

    errno = 0;

    lResult = strntol("10", 2, nullptr, 37);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, errno == EINVAL);

    // An arbitrarily-large base should fail

    errno = 0;

    lResult = strntol("10", 2, nullptr, 2147483629);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, errno == EINVAL);

    // A negative base should fail

    errno = 0;

    lResult = strntol("10", 2, nullptr, -3);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, errno == EINVAL);
}

static void TestZeroLength(nlTestSuite *inSuite __attribute__((unused)),
                           void *inContext __attribute__((unused)))
{
    signed long   lResult;
    const char *  lString;
    char *        lEnd;

    errno   = 0;
    lString = "0101";

    lResult = strntol(lString, 0, &lEnd, 2);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno   = 0;
    lString = "007";

    lResult = strntol(lString, 0, &lEnd, 8);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno   = 0;
    lString = "13";

    lResult = strntol(lString, 0, &lEnd, 10);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno   = 0;
    lString = "11";

    lResult = strntol(lString, 0, &lEnd, 10);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno   = 0;
    lString = "0xaf";

    lResult = strntol(lString, 0, &lEnd, 16);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno   = 0;
    lString = "0Xc3";

    lResult = strntol(lString, 0, &lEnd, 16);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno   = 0;
    lString = "d5";

    lResult = strntol(lString, 0, &lEnd, 16);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString);
    NL_TEST_ASSERT(inSuite, errno == 0);
}

static void TestImplicitBase(nlTestSuite *inSuite __attribute__((unused)),
                             void *inContext __attribute__((unused)))
{
    const int     kBase = 0;
    signed long   lResult;
    const char *  lString;
    size_t        lLength;
    char *        lEnd;


    // 1: Test octal (8)

    errno   = 0;
    lString = "007";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, kBase);
    NL_TEST_ASSERT(inSuite, lResult == 7);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    // 2: Test decimal (10)

    errno   = 0;
    lString = "13";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, kBase);
    NL_TEST_ASSERT(inSuite, lResult == 13);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno   = 0;
    lString = "11";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, kBase);
    NL_TEST_ASSERT(inSuite, lResult == 11);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    // 3: Test hexadecimal (16)

    errno   = 0;
    lString = "0xaf";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, kBase);
    NL_TEST_ASSERT(inSuite, lResult == 175);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno   = 0;
    lString = "0Xc3";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, kBase);
    NL_TEST_ASSERT(inSuite, lResult == 195);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno   = 0;
    lString = "0x3B";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, kBase);
    NL_TEST_ASSERT(inSuite, lResult == 59);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);
}

static void TestSignedness(nlTestSuite *inSuite __attribute__((unused)),
                           void *inContext __attribute__((unused)))
{
    signed long   lResult;
    const char *  lString;
    size_t        lLength;
    char *        lEnd;

    // 1: Test explicit negative sign.

    errno   = 0;
    lString = "-17";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 10);
    NL_TEST_ASSERT(inSuite, lResult == -17);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    // 2: Test explicit positive sign.

    errno   = 0;
    lString = "+17";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 10);
    NL_TEST_ASSERT(inSuite, lResult == 17);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    // 3: Test implicit positive sign.

    errno   = 0;
    lString = "17";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 10);
    NL_TEST_ASSERT(inSuite, lResult == 17);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);
}

static void TestLeadingSpace(nlTestSuite *inSuite __attribute__((unused)),
                             void *inContext __attribute__((unused)))
{
    signed long   lResult;
    const char *  lString;
    size_t        lLength;
    char *        lEnd;

    errno   = 0;
    lString = " 0101";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 2);
    NL_TEST_ASSERT(inSuite, lResult == 5);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno   = 0;
    lString = "  007";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 8);
    NL_TEST_ASSERT(inSuite, lResult == 7);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno   = 0;
    lString = "\t13";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 10);
    NL_TEST_ASSERT(inSuite, lResult == 13);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno   = 0;
    lString = "\t\t-13";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 10);
    NL_TEST_ASSERT(inSuite, lResult == -13);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno   = 0;
    lString = "\t\t\t+13";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 10);
    NL_TEST_ASSERT(inSuite, lResult == 13);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);


    errno   = 0;
    lString = "\t \t11";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 10);
    NL_TEST_ASSERT(inSuite, lResult == 11);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno   = 0;
    lString = " \t 0xaf";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 16);
    NL_TEST_ASSERT(inSuite, lResult == 175);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno   = 0;
    lString = "\t\t  0Xc3";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 16);
    NL_TEST_ASSERT(inSuite, lResult == 195);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno   = 0;
    lString = "  \t\td5";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 16);
    NL_TEST_ASSERT(inSuite, lResult == 213);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno   = 0;
    lString = "   \t\t\t0x3B";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 16);
    NL_TEST_ASSERT(inSuite, lResult == 59);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);
}

static void TestOverflow(nlTestSuite *inSuite __attribute__((unused)),
                         void *inContext __attribute__((unused)))
{
    signed long   lResult;
    const char *  lString;
    size_t        lLength;
    char *        lEnd;

    // 1: Test hexadecimal overflow

    errno   = 0;
    lString = "0x7FFFFFFFFFFFFFFFF";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 16);
    fprintf(stderr, "%s: %d: lResult %ld lString %p lEnd %p\n",
            __FILE__, __LINE__, lResult, lString, lEnd);
    NL_TEST_ASSERT(inSuite, lResult == LONG_MAX);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == ERANGE);

    errno   = 0;
    lString = "0xFFFFFFFFFFFFFFFFF";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 16);
    fprintf(stderr, "%s: %d: lResult %ld lString %p lEnd %p\n",
            __FILE__, __LINE__, lResult, lString, lEnd);
    NL_TEST_ASSERT(inSuite, lResult == LONG_MAX);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == ERANGE);

    // 2: Test decimal overflow

    // 2.1 Test positive decimal overflow

    errno   = 0;
    lString = "147573952589676412927";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 10);
    fprintf(stderr, "%s: %d: lResult %ld lString %p lEnd %p\n",
            __FILE__, __LINE__, lResult, lString, lEnd);
    NL_TEST_ASSERT(inSuite, lResult == LONG_MAX);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == ERANGE);

    errno   = 0;
    lString = "18446744073709551616";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 10);
    fprintf(stderr, "%s: %d: lResult %ld lString %p lEnd %p\n",
            __FILE__, __LINE__, lResult, lString, lEnd);
    NL_TEST_ASSERT(inSuite, lResult == LONG_MAX);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == ERANGE);

    // 2.2 Test negative decimal overflow

    errno   = 0;
    lString = "-147573952589676412927";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 10);
    fprintf(stderr, "%s: %d: lResult %ld lString %p lEnd %p\n",
            __FILE__, __LINE__, lResult, lString, lEnd);
    NL_TEST_ASSERT(inSuite, lResult == LONG_MIN);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == ERANGE);

    errno   = 0;
    lString = "-18446744073709551616";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 10);
    fprintf(stderr, "%s: %d: lResult %ld lString %p lEnd %p\n",
            __FILE__, __LINE__, lResult, lString, lEnd);
    NL_TEST_ASSERT(inSuite, lResult == LONG_MIN);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == ERANGE);
}

static void TestShortLengths(nlTestSuite *inSuite __attribute__((unused)),
                           void *inContext __attribute__((unused)))
{
    signed long   lResult;
    const char *  lString;
    size_t        lLength;
    char *        lEnd;

    // 1: Test short signedness

    // 1.1: Test short signedness with no leading space

    errno = 0;
    lString = "+23";
    lLength = 1;

    lResult = strntol(lString, lLength, &lEnd, 10);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno = 0;
    lString = "-23";
    lLength = 1;

    lResult = strntol(lString, lLength, &lEnd, 10);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString);
    NL_TEST_ASSERT(inSuite, errno == 0);

    // 1.2: Test short signedness with a leading space

    // 1.2.1: Test short signedness with a leading space and one
    //        character of length.

    errno = 0;
    lString = " +23";
    lLength = 1;

    lResult = strntol(lString, lLength, &lEnd, 10);
    fprintf(stderr, "%s: %d: lResult %ld lString %p lEnd %p\n",
            __FILE__, __LINE__, lResult, lString, lEnd);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno = 0;
    lString = " -23";
    lLength = 1;

    lResult = strntol(lString, lLength, &lEnd, 10);
    fprintf(stderr, "%s: %d: lResult %ld lString %p lEnd %p\n",
            __FILE__, __LINE__, lResult, lString, lEnd);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString);
    NL_TEST_ASSERT(inSuite, errno == 0);

    // 1.2.2: Test short signedness with a leading space and two
    //        characters of length.

    errno = 0;
    lString = " +23";
    lLength = 2;

    lResult = strntol(lString, lLength, &lEnd, 10);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno = 0;
    lString = " -23";
    lLength = 2;

    lResult = strntol(lString, lLength, &lEnd, 10);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString);
    NL_TEST_ASSERT(inSuite, errno == 0);

    // 1.2.3: Test short signedness with a leading space and three
    //        characters of length.

    errno = 0;
    lString = " +23";
    lLength = 3;

    lResult = strntol(lString, lLength, &lEnd, 10);
    NL_TEST_ASSERT(inSuite, lResult == 2);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno = 0;
    lString = " -23";
    lLength = 3;

    lResult = strntol(lString, lLength, &lEnd, 10);
    fprintf(stderr, "%s: %d: lResult %ld lString %p lEnd %p\n",
            __FILE__, __LINE__, lResult, lString, lEnd);
    NL_TEST_ASSERT(inSuite, lResult == -2);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    // 2: Test short hexadecimal leading "0x" and "0X".

    // 2.1: Test short hexadecimal leading "0x" and "0X" with no
    //      leading space.

    // 2.1.1: Test short hexadecimal leading "0x" and "0X" with no
    //        leading space and one character of length.
    //
    // For these tests, with a length of one (1), strntol will be
    // unable to adequately test for and strip the leading "0x" or "0X".
    // So, all it can look at is the leading zero ('0'), which should
    // and will get correctly converted.

    errno = 0;
    lString = "0xfe";
    lLength = 1;

    lResult = strntol(lString, lLength, &lEnd, 16);
    fprintf(stderr, "%s: %d: lResult %ld lString %p lEnd %p\n",
            __FILE__, __LINE__, lResult, lString, lEnd);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno = 0;
    lString = "0XCD";
    lLength = 1;

    lResult = strntol(lString, lLength, &lEnd, 16);
    fprintf(stderr, "%s: %d: lResult %ld lString %p lEnd %p\n",
            __FILE__, __LINE__, lResult, lString, lEnd);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    // 2.1.2: Test short hexadecimal leading "0x" and "0X" with no
    //        leading space and two characters of length.

    errno = 0;
    lString = "0xfe";
    lLength = 2;

    lResult = strntol(lString, lLength, &lEnd, 16);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno = 0;
    lString = "0XCD";
    lLength = 2;

    lResult = strntol(lString, lLength, &lEnd, 16);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString);
    NL_TEST_ASSERT(inSuite, errno == 0);

    // 2.1.3: Test short hexadecimal leading "0x" and "0X" with no
    //        leading space and three characters of length.

    errno = 0;
    lString = "0xfe";
    lLength = 3;

    lResult = strntol(lString, lLength, &lEnd, 16);
    NL_TEST_ASSERT(inSuite, lResult == 15);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno = 0;
    lString = "0XCD";
    lLength = 3;

    lResult = strntol(lString, lLength, &lEnd, 16);
    NL_TEST_ASSERT(inSuite, lResult == 12);
    NL_TEST_ASSERT(inSuite, lEnd == lString + lLength);
    NL_TEST_ASSERT(inSuite, errno == 0);
}

static void TestBadHexLeading(nlTestSuite *inSuite __attribute__((unused)),
                              void *inContext __attribute__((unused)))
{
    signed long   lResult;
    const char *  lString;
    size_t        lLength;
    char *        lEnd;

    // 1: Test valid leading "0" but bad following characters.
    //
    // Both of these tests should result in interpreting the '0' as a
    // zero and with one character of valid conversion since the
    // leading "0x" and "0X" test will fail and thus will not be
    // skipped.

    errno = 0;
    lString = "0zCD";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 16);
    fprintf(stderr, "%s: %d: lResult %ld lString %p lEnd %p\n",
            __FILE__, __LINE__, lResult, lString, lEnd);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString + 1);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno = 0;
    lString = "0%CD";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 16);
    fprintf(stderr, "%s: %d: lResult %ld lString %p lEnd %p\n",
            __FILE__, __LINE__, lResult, lString, lEnd);
    NL_TEST_ASSERT(inSuite, lResult == 0);
    NL_TEST_ASSERT(inSuite, lEnd == lString + 1);
    NL_TEST_ASSERT(inSuite, errno == 0);

    // 2: Test invalid leading "1" but valid following characters.
    //
    // Both of these tests should result in interpreting the '1' as a
    // one (1) and with one character of valid conversion since the
    // leading "0x" and "0X" test will fail and thus will not be
    // skipped.

    errno = 0;
    lString = "1xCD";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 16);
    NL_TEST_ASSERT(inSuite, lResult == 1);
    NL_TEST_ASSERT(inSuite, lEnd == lString + 1);
    NL_TEST_ASSERT(inSuite, errno == 0);

    errno = 0;
    lString = "1XCD";
    lLength = strlen(lString);

    lResult = strntol(lString, lLength, &lEnd, 16);
    NL_TEST_ASSERT(inSuite, lResult == 1);
    NL_TEST_ASSERT(inSuite, lEnd == lString + 1);
    NL_TEST_ASSERT(inSuite, errno == 0);
}

/**
 *   Test Suite. It lists all the test functions.
 */
static const nlTest sTests[] = {
    NL_TEST_DEF("Invalid Bases",   TestInvalidBases),
    NL_TEST_DEF("Zero Length",     TestZeroLength),
    NL_TEST_DEF("Leading Space",   TestLeadingSpace),
    NL_TEST_DEF("Implicit Base",   TestImplicitBase),
    NL_TEST_DEF("Signedness",      TestSignedness),
    NL_TEST_DEF("Overflow",        TestOverflow),
    NL_TEST_DEF("Short Lengths",   TestShortLengths),
    NL_TEST_DEF("Bad Hex Leading", TestBadHexLeading),

    NL_TEST_SENTINEL()
};

int main(void)
{
    nlTestSuite theSuite = {
        "strntol",
        &sTests[0],
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        0,
        0,
        0,
        0
    };

    // Generate human-readable output.
    nlTestSetOutputStyle(OUTPUT_DEF);

    // Run test suit againt one context.
    nlTestRunner(&theSuite, nullptr);

    return nlTestRunnerStats(&theSuite);
}
