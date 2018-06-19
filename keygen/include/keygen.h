
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

#include "config.h"

/** @struct GlobalConstants 
*  @brief This struct declares constants without polluting the global
*  namespace.
*
*/

namespace Global
{
    struct Constants {
        static constexpr auto NUMBER_OF_PRINTABLE_CHARACTERS = 95;
    };
}

namespace KeyGen
{
    namespace Program
    {
        const auto Title  = "KeyGen";
        const auto Author = "Jose Fernando Lopez Fernandez";

        // @todo Use CMake to automatically keep track of the program version
        class Version {
            using Number = unsigned int;

            Number m_major;
            Number m_minor;
            Number m_build;

        public:
            Version()
                : m_major { Application::Version::Major },
                  m_minor { Application::Version::Minor },
                  m_build { Application::Version::Build }
            {
                // Default constructor
            }

            Version(const Version& version)
                : m_major { version.m_major },
                  m_minor { version.m_minor },
                  m_build { version.m_build }
            {
                // Copy constructor
            }

            Version(Version&& version) noexcept
                : m_major { version.m_major },
                  m_minor { version.m_minor },
                  m_build { version.m_build }
            {
                // Move constructor
            }

            ~Version() = default;
            
            auto major() const noexcept -> decltype (auto) { return m_major; }
            auto minor() const noexcept -> decltype (auto) { return m_minor; }
            auto build() const noexcept -> decltype (auto) { return m_build; }

            // Copy assignment operator
            Version& operator=(const Version& other) = default;

            // Move assignment operator
            Version& operator=(Version&& other) = default;

            std::string operator()() const noexcept
            {
                return (std::to_string(major()) + "." + std::to_string(minor()) + "." + std::to_string(build()));
            }

            friend std::ostream& operator<<(std::ostream& outputStream, const Version& version) noexcept
            {
                return outputStream << version();
            }
        };

        namespace ExitCodes
        {
            const auto DO_NOT_EXIT_PROG = 0;
            const auto EXIT_APPLICATION = 1;
        }

        const auto InstanceVersion = Version();
    } // Namespace Program

    // @todo Center text (title)
    inline void PrintTitle(const std::string_view& title) noexcept
    {
        std::cout << title << "\n";
    }

    // @todo Center text (author)
    inline void PrintAuthor(const std::string_view& author) noexcept
    {
        std::cout << author << "\n";
    }

    // @todo Center text (version)
    inline void PrintVersion(const std::string_view& version) noexcept
    {
        std::cout << version << "\n";
    }

    /** @fn inline void PrintHelp(const int exitCode) noexcept
     *  @brief Print help dialog and exit application
     *
     *  KeyGen::PrintHelp(KeyGen::Program::ExitCodes::EXIT_APPLICATION);
     *
     */

    inline void PrintHelp(const int exitCode) noexcept
    {
        KeyGen::PrintTitle(KeyGen::Program::Title);
        KeyGen::PrintAuthor(KeyGen::Program::Author);
        KeyGen::PrintVersion(KeyGen::Program::InstanceVersion());

        // @todo Add usage details to help dialog

        if (exitCode) {
            // @todo Create more graceful way of exiting application
            exit(EXIT_SUCCESS);
        }
    }
} // Namespace KeyGen

#include "password.h"

#endif // KEYGEN_KEYGEN_H_

