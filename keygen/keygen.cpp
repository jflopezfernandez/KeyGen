
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
 *  **************************************************************************/

#define TRUE  1
#define FALSE 0

#ifdef _CRT_SECURE_NO_WARNINGS
#error "For security purposes, do not define '_CRT_SECURE_NO_WARNINGS'"
#endif

#include "include/keygen.h"

#include <boost/optional.hpp>
#include <boost/program_options.hpp>

#ifndef NDEBUG
#include <gtest/gtest.h>
#endif // NDEBUG

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

#ifndef NDEBUG
namespace Dummy {
    int ReturnOne() {
        return 1;
    }

    TEST(GTestConfigDummyTest, ReturnOne)
    {
        EXPECT_EQ(1, Dummy::ReturnOne());
    }

    TEST(GTestConfigDummyTest, ReturnTwo)
    {
        EXPECT_EQ(2, Dummy::ReturnOne() * 2);
    }
}

namespace Tutorial
{
    // @todo Implement Factorial()
    int Factorial(const int n)
    {
        return ((n < 1) ? 1 : n * Factorial(n - 1));
    }

    TEST(FactorialTest, HandlesZeroInput)
    {
        EXPECT_EQ(Factorial(0), 1);
    }

    TEST(FactorialTest, HandlesPositiveNumbers)
    {
        EXPECT_EQ(Factorial(1),     1);
        EXPECT_EQ(Factorial(2),     2);
        EXPECT_EQ(Factorial(3),     6);
        EXPECT_EQ(Factorial(6),   720);
        EXPECT_EQ(Factorial(8), 40320);
    }
}
#endif // NDEBUG

namespace ProgramOptions = boost::program_options;
using OptionsDescription = boost::program_options::options_description;

void LogMsg(const std::string_view& message)
{
    std::cout << "[LOG]: " << message << "\n";
}

// Disabled
// Question: am I supposed to pass these arguments in by value or by reference?
// Idea: template function?
//template <typename T>
//bool AisElementOfB(const T& element, const std::vector<T>& set) noexcept
//{
//    // @todo Implement AisElementOfB()
//    // @disabled:
//    //for (typename std::vector<T>::iterator iterator = set.begin(); iterator != set.end(); ++iterator) {
//    //    if (std::strcmp(element, iterator) == 0) {
//    //        return true;
//    //    }
//    //}
//
//    for (auto c = 0u; c <= set.size(); ++c) {
//        if (std::strcmp(element, set[c]) == 0) {
//            return true;
//        }
//    }
//
//    return false;
//}

namespace StringOperations
{
    // @todo Implement AisASubstringOfB()
    bool AisASubstringOfB(const char *testString, const char *hostString)
    {
        // Test to see if they are the same string
        // If they are, return true; technically a string is a substring of itself
        if (strcmp(testString, hostString) == 0) {
            return true;
        }

        for (auto i = 0u; i < std::strlen(hostString); ++i) {
            for (auto j = i; j < std::strlen(hostString); ++j) {
                const auto substring = std::strstr(testString, hostString);

                if (substring) {
                    return true;
                }
            }
        }

        return false;
    }

#ifndef NDEBUG
    TEST(SubstringTest, NotASubstring)
    {
        EXPECT_FALSE(AisASubstringOfB("A", "BCD"));
        EXPECT_FALSE(AisASubstringOfB("f", "dd"));
    }

    // @todo Last case is failing, probably because of the space; fix it
    TEST(SubstringTest, YesASubstring)
    {
        EXPECT_TRUE(AisASubstringOfB("b", "abc"));
        EXPECT_TRUE(AisASubstringOfB("YE", "YES"));
        EXPECT_TRUE(AisASubstringOfB("Jose", "Jose Fernando"));
    }

    TEST(SubstringTest, SameString)
    {
        EXPECT_TRUE(AisASubstringOfB("aaa", "aaa"));
        EXPECT_TRUE(AisASubstringOfB("", ""));
    }
#endif // NDEBUG
}

namespace Password
{
    /** Disabled for now
    double calculateEntropy(const std::string_view& password, const size_t charSetSize) noexcept
    {
        // @todo Create table/list of characters seen at least once in password
        std::string uniqueCharactersInPassword { };

        // Refactor to iterator for loop
        for (auto c = 0u; c < password.length(); c++) {
            // @todo Check to make sure the character is not already in the table
            // @todo Fix this
            // If not in list:
            if (StringOperations::AisASubstringOfB(&password[c], uniqueCharactersInPassword.c_str())) {
                uniqueCharactersInPassword += password[c];
            } else {
                continue;
            }
        }

        // @todo Using all possible characters in keyboard for now
        


        // @todo Return an actual value
        return -1;
    }*/

    inline double calculateShannonEntropy(const std::string_view& password, const size_t charSetSize) noexcept
    {
        return (password.length() * (log(95) / log(2)));
    }

#ifndef NDEBUG
    ::testing::AssertionResult AssertBothFloatingPointNumbersAreRoughlyEqual(const char *m_expr, const char *n_expr, const double m, const double n)
    {
        if (abs(m - n) < 0.05) {
            return ::testing::AssertionSuccess();
        }

        return ::testing::AssertionFailure()
            << m_expr << " and " << n_expr << " (" << m << " and " << n << ") are not equal, or at least within 0.05 of each other.\n";
    }

    // Question: Handle a password of invalid length, maybe? If it's possible

    TEST(EntropyCalculation, HandlesNormalLengthPasswords)
    {
        AssertBothFloatingPointNumbersAreRoughlyEqual("calculateShannonEntropy(\"abcde\",    GlobalConstants::NUMBER_OF_PRINTABLE_CHARACTERS)", "32.85", calculateShannonEntropy("abcde",    GlobalConstants::NUMBER_OF_PRINTABLE_CHARACTERS), 32.85);
        AssertBothFloatingPointNumbersAreRoughlyEqual("calculateShannonEntropy(\"abcdef\",   GlobalConstants::NUMBER_OF_PRINTABLE_CHARACTERS)", "39.42", calculateShannonEntropy("abcdef",   GlobalConstants::NUMBER_OF_PRINTABLE_CHARACTERS), 39.42);
        AssertBothFloatingPointNumbersAreRoughlyEqual("calculateShannonEntropy(\"abcdefg\",  GlobalConstants::NUMBER_OF_PRINTABLE_CHARACTERS)", "45.99", calculateShannonEntropy("abcdefg",  GlobalConstants::NUMBER_OF_PRINTABLE_CHARACTERS), 45.99);
        AssertBothFloatingPointNumbersAreRoughlyEqual("calculateShannonEntropy(\"abcdefgh\", GlobalConstants::NUMBER_OF_PRINTABLE_CHARACTERS)", "52.56", calculateShannonEntropy("abcdefgh", GlobalConstants::NUMBER_OF_PRINTABLE_CHARACTERS), 52.56);

        //EXPECT_DOUBLE_EQ(calculateShannonEntropy("abcde"   , GlobalConstants::NUMBER_OF_PRINTABLE_CHARACTERS), 32.85);
        //EXPECT_DOUBLE_EQ(calculateShannonEntropy("abcdef"  , GlobalConstants::NUMBER_OF_PRINTABLE_CHARACTERS), 39.42);
        //EXPECT_DOUBLE_EQ(calculateShannonEntropy("abcdefg" , GlobalConstants::NUMBER_OF_PRINTABLE_CHARACTERS), 45.99);
        //EXPECT_DOUBLE_EQ(calculateShannonEntropy("abcdefgh", GlobalConstants::NUMBER_OF_PRINTABLE_CHARACTERS), 52.56);
    }
#endif // NDEBUG

    // @todo Implement generatePassword()
    // @todo Pass in parameters, such as length, minimum entropy, legal chars, etc.
    std::string generatePassword() noexcept
    {
        return "NULL";
    }

    // @todo Test suite for password generation
    // @todo Test suite for entropy calculation
}

void PrintHelp() noexcept
{
    // @todo Implement PrintHelp()
    std::cout << "<Print Help>\n";

    exit(EXIT_FAILURE);
}

struct Version {
    using Number = unsigned int;

    static constexpr Number Major = 0;
    static constexpr Number Minor = 1;
    static constexpr Number Build = 0;

    friend std::ostream& operator<<(std::ostream& outputStream, const Version& version) noexcept
    {
        return outputStream << Version::Major << "." << Version::Minor << "." << Version::Build;
    }
};

void PrintVersion() noexcept
{
    // @todo Implement PrintVersion()
    std::cout << "<Print Version>\n";

    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    std::size_t numberOfPasswordsToGenerate = DefaultConfiguration::DEFAULT_PASSWORDS_AMOUNT;
    std::size_t passwordLength              = DefaultConfiguration::DEFAULT_PASSWORDS_LENGTH;

    OptionsDescription options("Generic options");
    options.add_options()
        ("help,h", "Display this help dialog")
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

#ifndef NDEBUG
    testing::InitGoogleTest(&argc, argv);
#endif

    ///////////////////////////////////////////////////////////////////////////
    //
    //  @todo Main program functionality goes here
    //
    //  1. @todo Calculate password entropy
    //  2. @todo Generate a password
    //  3. @todo Add program options
    //     a. @todo Specify number of passwords to generate
    //  4. @todo Set minimum tolerable entropy for generated passwords
    //
    // Password entropy = log(2)(pool of unique characters^number of characters in password)
    //
    ///////////////////////////////////////////////////////////////////////////

    // Always print current time so I can see if the build actually went through
    // or not.

    // @todo Modularize this into a separate time module
    struct tm newtime;
    char am_pm[] = "AM";
    __time64_t long_time;
    char timebuf[26];
    _time64(&long_time);
    errno_t err = _localtime64_s(&newtime, &long_time);

    if (err) {
        fprintf(stderr, "OOps\n");

        exit(EXIT_FAILURE);
    }

    // Convert from 24 to 12 hour clock
    if (newtime.tm_hour > 12) {
        strcpy_s(am_pm, sizeof am_pm, "PM");
    }

    if (newtime.tm_hour > 12) {
        newtime.tm_hour -= 12;
    }

    if (newtime.tm_hour == 0) {
        newtime.tm_hour = 12;
    }

    // Convert to an ASCII representation
    err = asctime_s(timebuf, 26, &newtime);

    if (err) {
        fprintf(stderr, "oops2\n");

        exit(EXIT_FAILURE);
    }

    printf("%.19s %s\n", timebuf, am_pm);

#ifndef NDEBUG
    return RUN_ALL_TESTS();
#else
    return EXIT_SUCCESS;
#endif
}
