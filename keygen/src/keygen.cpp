
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
 *   Application Task List:
 *   1. @todo Calculate password entropy
 *   2. @todo Generate a password
 *   3. @todo Add program options
 *      a. @todo Specify number of passwords to generate
 *   4. @todo Set minimum tolerable entropy for generated passwords
 *   5. @todo Initialize pseudo-random number generator
 *   6. @todo Implement main
 *   7. @todo Validate cmd line args
 *   8. @todo Enumerate possible cmd line args
 *   
 *  Password entropy = log(2)(pool of unique characters^number of characters in
 *  password)
 *
 *  **************************************************************************/

#include "keygen.h"
#include "version.h"

int main()
{
    const KeyGen::Passwords::Requirements passwordRequirements;
    const KeyGen::Passwords::Password     defaultPassword;

    std::cout << "\n";
    std::cout << "Default Password: " << defaultPassword << "\n";
    std::cout << "\tEntropy: "        << defaultPassword.ShannonEntropy() 
              << "\n\n";

    // Testing generating configuration file:
    std::cout << "Version 2: " << getVersion() << "\n\n";

    return EXIT_SUCCESS;
}
