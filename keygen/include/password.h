
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
*  @date 18-June-2018
*  @brief This file contains the password structure and configuration.
*
*  Tasks:
*      1. @todo Add file details
*      2. @todo Add file details
*
*  **************************************************************************/

#ifndef KEYGEN_INCLUDE_PASSWORD_H_
#define KEYGEN_INCLUDE_PASSWORD_H_

#include <cmath>
#include <string>

namespace KeyGen
{
    namespace Passwords
    {
        struct Properties {
            static constexpr auto DEFAULT_MIN_LENGTH =  8;
            static constexpr auto DEFAULT_MAX_LENGTH = 16;
        };

        struct DefaultConfiguration {
            static constexpr auto DEFAULT_QUANTITY   = 10;
        };

        class Requirements {
            size_t  m_minimumLength;
            size_t  m_maximumLength;

            double m_minimumEntropy;
            double m_maximumEntropy;

        public:
            // @todo Add function doc
            Requirements()
                :    m_minimumLength { Properties::DEFAULT_MIN_LENGTH }, 
                     m_maximumLength { Properties::DEFAULT_MAX_LENGTH },
                    m_minimumEntropy { 40 },
                    m_maximumEntropy { 80 }
            {
                // Default constructor
            }

            auto  minimumLength() const noexcept { return  m_minimumLength; }
            auto  maximumLength() const noexcept { return  m_maximumLength; }

            auto minimumEntropy() const noexcept { return m_minimumEntropy; }
            auto maximumEntropy() const noexcept { return m_maximumEntropy; }
        };

        class Password {
            size_t m_length;
            
            std::string m_text;

            double m_ShannonEntropy;

            // Note: This could be a static function
            double calculateShannonEntropy() const noexcept
            {
                return (m_text.length() * (std::log(95) / std::log(2)));
            }

            void setShannonEntropy() noexcept
            {
                m_ShannonEntropy = calculateShannonEntropy();
            }

        public:
            // @todo Actually implement default constructor
            // @todo Fix this constructor; it currently initializes with magic
            // numbers, and only one parameter
            Password()
                : m_length(12)
            {
                m_text = "abcdefghijkl";

                // @todo Fix this setup; Visual Studio gives warning saying
                // m_ShannonEntropy is not initialized when I use the setShann.
                // Entropy() function, so I'm currently doing it like this

                // @todo Fix entropy calculation; gives value of 78.8383 when in reality
                // it would be much lower for a password as basic as 'abcdefghijkl'
                m_ShannonEntropy = calculateShannonEntropy();
            }

            // @todo Create constructor that can specify length, entropy, etc.
            //Password(const size_t length, const double entropy) { ... }

            auto length() const noexcept { return m_length; }

            auto text() const noexcept { return m_text; }

            auto ShannonEntropy() const noexcept { return m_ShannonEntropy; }

            std::string operator()() const noexcept { return m_text; }

            friend std::ostream& operator<<(std::ostream& outputStream, const Password& password)
            {
                return outputStream << password();
            }
        };
    } // Namespace Passwords
} // Namespace KeyGen

#endif // KEYGEN_INCLUDE_PASSWORD_H_
