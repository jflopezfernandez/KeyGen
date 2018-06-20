
/** ***************************************************************************
*
*  Copyright 2018 Jose Fernando Lopez Fernandez - All Rights Reserved
*  See the file AUTHORS included with the application distribution for
*  specific information.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following
*  conditions are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*
*     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
*     CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*     INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
*     MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
*     CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*     SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
*     NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
*     HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
*     OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
*     EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*  ***************************************************************************
*
*  @author Jose Fernando Lopez Fernandez
*  @date 15-June-2018
*  @brief This is the main keygen driver file
*
*  Tasks:
*      1. @todo Add file details
*      2. @todo Add file details
*
*  **************************************************************************/

#ifndef KEYGEN_INCLUDE_KEYGEN_H_
#define KEYGEN_INCLUDE_KEYGEN_H_

#define TRUE  1
#define FALSE 0

/** @def _CRT_SECURE_NO_WARNINGS
*  @brief This preprocessor definition disables Visual Studio's warnings
*  when not using the safe string functions provided by the MSVC runtime.
*
*  Disable the safe string library due to its lack of compatibility with
*  *nix systems.
*
*/

#define _CRT_SECURE_NO_WARNINGS

#ifndef _CRT_SECURE_NO_WARNINGS
#error "The safe string library is not compatible with *nix systems"
#endif

/** Include Microsoft's Guideline Support Library (GSL). 
*
*  The Guideline Support Library (GSL) contains functions and types that are
*  suggested for use by the C++ Core Guidelines maintained by the Standard C++
*  Foundation. This repo contains Microsoft's implementation of GSL.
*
*  The library includes types like span<T>, string_span, owner<> and others.
*
*  The entire implementation is provided inline in the headers under the gsl
*  directory. The implementation generally assumes a platform that implements
*  C++14 support. There are specific workarounds to support MSVC 2015.
*
*  While some types have been broken out into their own headers
*  (e.g. gsl/span), it is simplest to just include gsl/gsl and gain access to
*  the entire library.
*
*/

#include <gsl/gsl>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <cstdint>
#include <cerrno>
#include <csignal>
#include <cmath>
#include <ctime>

/** C++ Standard Library Headers
*
*/

#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <ratio>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <utility>

/** @file config.h
 *  @brief This file contains customization settings and project metadata such
 *  as the current release version, compilation settings, etc.
 *  
 */

#include "config.h"
#include "password.h"

#endif // KEYGEN_KEYGEN_H_

