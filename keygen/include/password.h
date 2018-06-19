
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

#ifndef KEYGEN_PASSWORD_H_
#define KEYGEN_PASSWORD_H_

#include <string>

namespace KeyGen
{
    class PasswordRequirements {
        size_t  m_minimumLength;
        size_t  m_maximumLength;

        double m_minimumEntropy;
        double m_maximumEntropy;

    public:
        auto  minimumLength() const noexcept { return m_minimumLength; }
        auto  maximumLength() const noexcept { return m_maximumLength; }

        auto minimumEntropy() const noexcept { return m_minimumEntropy; }
        auto maximumEntropy() const noexcept { return m_maximumEntropy; }
    };

    class Password {
        size_t m_length;
        std::string text;

        double m_ShannonEntropy;

    public:


        auto length() const noexcept { return m_length; }
    };
}

// @todo Implement password as class
// @todo Design password class
namespace nsPassword
{
    inline double calculateShannonEntropy(const std::string_view& password, const size_t charSetSize) noexcept
    {
        return (password.length() * (log(95) / log(2)));
    }

    // @todo Implement generatePassword()
    // @todo Add the ability to specify legal character set
    /*std::string generatePassword(const std::size_t characters, const double minimumEntropy) noexcept
    {
        return "NULL";
    }*/

    // @todo Test suite for password generation
    // @todo Test suite for entropy calculation
} // End namespace nsPassword

#endif // KEYGEN_PASSWORD_H_
