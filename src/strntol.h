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
 *      This file defines a "missing" C99 interface for strntol which
 *      adds a length parameter to the standard strtol.
 *
 */

#ifndef STRNTOL_H
#define STRNTOL_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

extern long strntol(const char *aString, size_t aLength, char **aEnd, int aBase);

#ifdef __cplusplus
}
#endif

#endif /* STRNTOL_H */
