
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
 *      1. @todo Calculate password entropy
 *      2. @todo Generate a password
 *      3. @todo Add program options
 *         a. @todo Specify number of passwords to generate
 *      4. @todo Set minimum tolerable entropy for generated passwords
 *
 *  **************************************************************************/

#include <keygen.h>

#include <boost/optional.hpp>
#include <boost/program_options.hpp>

#ifndef NDEBUG
#include <gtest/gtest.h>
#endif // NDEBUG

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

    int Factorial(int n)
    {
        return 1;
    }

    TEST(GTestConfigDummyTest, Factorial)
    {
        EXPECT_EQ(1, Factorial(0));
    }
}
#endif // NDEBUG

namespace ProgramOptions = boost::program_options;
using OptionsDescription = boost::program_options::options_description;

void LogMsg(const std::string_view& message)
{
    std::cout << "[LOG]: " << message << "\n";
}

void PrintHelp() noexcept
{
    // @todo Implement PrintHelp()
    std::cout << "<Print Help>\n";

    exit(EXIT_FAILURE);
}

void PrintVersion() noexcept
{
    // @todo Implement PrintVersion()
    std::cout << "<Print Version>\n";

    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    std::size_t numberOfPasswordsToGenerate = 10u;

    OptionsDescription options("Generic options");
    options.add_options()
        ("help,h", "Display this help dialog")
        ("version", "Display program version and exit")
        ("verbose,v", "Set program output verbosity to 'verbose'")
        ("number-to-generate,N", ProgramOptions::value<std::size_t>(&numberOfPasswordsToGenerate)->default_value(10), "Number of cryptographically strong passwords for the application to generate")
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

#ifndef NDEBUG
    testing::InitGoogleTest(&argc, argv);
#endif

    // @todo Main program functionality goes here

#ifndef NDEBUG
    return RUN_ALL_TESTS();
#else
    return EXIT_SUCCESS;
#endif
}
