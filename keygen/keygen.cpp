
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
 *  @file       keygen.cpp
 *  @author     Jose Fernando Lopez Fernandez
 *  @date       15-June-2018
 *  @version    1.0.0
 *  
 *  @brief      This is the main keygen driver file
 *
 *  Requirements:
 *      1. Calculate password entropy
 *      2. Generate a password
 *      3. Add program options
 *         a. Specify number of passwords to generate
 *      4. Set minimum tolerable entropy for generated passwords
 *
 *  ***************************************************************************
 *
 *   @todo Main program functionality
 *   1. @todo Calculate password entropy
 *   2. @todo Generate a password
 *   3. @todo Add program options
 *      a. @todo Specify number of passwords to generate
 *   4. @todo Set minimum tolerable entropy for generated passwords
 *   5. @todo Initialize pseudo-random number generator
 * 
 *  Password entropy = log(2)(pool of unique characters^number of characters in
 *  password)
 *
 *  **************************************************************************/

#include "keygen.h"

#pragma region PROGRAM_CONFIG
/** @struct GlobalConstants 
 *  @brief This struct declares constants without polluting the global
 *  namespace.
 *
 */

struct GlobalConstants {
    static constexpr auto NUMBER_OF_PRINTABLE_CHARACTERS = 95;
};

struct PasswordsProperties {
    // Hard coded limits
    static constexpr auto DEFAULT_PASSWORDS_LENGTH_MIN =    4;
    static constexpr auto DEFAULT_PASSWORDS_LENGTH_MAX = 4096;
};

struct DefaultConfiguration {
    // User default configuration
    static constexpr auto DEFAULT_PASSWORDS_AMOUNT = 10u;
    static constexpr auto DEFAULT_PASSWORDS_LENGTH = 12u;
};

class Version {
    using Number = unsigned int;

    const Number _major = 0;
    const Number _minor = 1;
    const Number _build = 0;

public:
    auto major() const noexcept -> decltype (auto) { return _major; }
    auto minor() const noexcept -> decltype (auto) { return _minor; }
    auto build() const noexcept -> decltype (auto) { return _build; }

    friend std::ostream& operator<<(std::ostream& outputStream, const Version& version) noexcept
    {
        return outputStream << version.major() << "." << version.minor() << "." << version.build();
    }
};

const Version ProgramVersion;

namespace ProgramOptions = boost::program_options;
using OptionsDescription = boost::program_options::options_description;

#pragma endregion

#pragma region ERROR

void LogMsg(const std::string_view& message)
{
    std::clog << "[LOG]: " << message << "\n";
}

#pragma endregion 

#pragma region COMMAND_LINE_OPTS

void PrintHelp() noexcept
{
    // @todo Implement PrintHelp() function
    std::cout << "<Print Help>\n";

    exit(EXIT_FAILURE);
}

void PrintVersion() noexcept
{
    // @todo Implement PrintVersion()
    std::cout << "\n\n\t\t\t";
    std::cout << "KeyGen - Version " << ProgramVersion << "\n\t\t";
    std::cout << "Jose Fernando Lopez Fernandez" << "\n";

    exit(EXIT_FAILURE);
}

#pragma endregion

namespace Dummy
{
    TEST(TestingGTestConfiguration, ReturnsOne)
    {
        EXPECT_EQ(1, 1);
    }

    TEST(TestingGTestConfiguration, ReturnsTwo)
    {
        EXPECT_EQ(2, 2);
    }
}

int main(int argc, char *argv[])
{
#pragma region PROGRAM_OPTIONS
    std::size_t numberOfPasswordsToGenerate = DefaultConfiguration::DEFAULT_PASSWORDS_AMOUNT;
    std::size_t passwordLength              = DefaultConfiguration::DEFAULT_PASSWORDS_LENGTH;

    OptionsDescription options("Generic options");
    options.add_options()
        // @todo Reenable this option once GTest bugs have been ironed out
        //("help,h", "Display this help dialog")
        ("version", "Display program version and exit")
        ("verbose,v", "Set program output verbosity to 'verbose'")
        ("number-to-generate,N", ProgramOptions::value<std::size_t>(&numberOfPasswordsToGenerate)->default_value(10), "Number of cryptographically strong passwords for the application to generate")
        ("password-length,l", ProgramOptions::value<std::size_t>(&passwordLength)->default_value(12), "Length of the passwords to generate")
    ; // End of genericOptions.add_options()

    ProgramOptions::variables_map map;
    ProgramOptions::store(ProgramOptions::parse_command_line(argc, argv, options), map);
    ProgramOptions::notify(map);

    if (map.count("help")) {
        PrintHelp();
    }

    if (map.count("version")) {
        PrintVersion();
    }

    if (map.count("verbose")) {
        std::stringstream stream;

        stream << "Number of passwords to generate: " << numberOfPasswordsToGenerate << "\n";

        LogMsg(stream.str());
    }

    // @todo Validate number of passwords to generate
    if (map.count("number-to-generate")) {
        if (numberOfPasswordsToGenerate < 1) {
            std::cerr << "Number of passwords to generate was too low (" << numberOfPasswordsToGenerate << ").\n";
            std::cerr << "Reverting back to default configuration: \n";

            // @todo Actually reset numberOfPasswordsToGenerate
            numberOfPasswordsToGenerate = DefaultConfiguration::DEFAULT_PASSWORDS_AMOUNT;

            std::cerr << "\t - Number of passwords to generate: " << numberOfPasswordsToGenerate << "\n\n";
        }

        // @todo Handle too high an amount
    }

    // @todo Validate password length
    if (map.count("length")) {
        if (passwordLength < PasswordsProperties::DEFAULT_PASSWORDS_LENGTH_MIN) {
            // Handle passwords too short
            std::cerr << "The specified password length is shorter than the lowest allowable length (" << PasswordsProperties::DEFAULT_PASSWORDS_LENGTH_MIN << "); \n";
            std::cerr << "reverting back to the default password length: " << DefaultConfiguration::DEFAULT_PASSWORDS_LENGTH << "\n\n";
            
            passwordLength = DefaultConfiguration::DEFAULT_PASSWORDS_LENGTH;
        } else if (passwordLength > PasswordsProperties::DEFAULT_PASSWORDS_LENGTH_MAX) {
            // Handle passwords too long
            std::cerr << "The specified password length is higher than the allowable maximum (" << PasswordsProperties::DEFAULT_PASSWORDS_LENGTH_MAX << "); \n";
            std::cerr << "reverting back to the default password length: " << DefaultConfiguration::DEFAULT_PASSWORDS_LENGTH << "\n\n";

            passwordLength = DefaultConfiguration::DEFAULT_PASSWORDS_LENGTH;
        }
    }
#pragma endregion

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
