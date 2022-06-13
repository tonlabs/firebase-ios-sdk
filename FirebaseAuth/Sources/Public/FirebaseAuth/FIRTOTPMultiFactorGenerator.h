/*
 * Copyright 2022 Google
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <Foundation/Foundation.h>

#import "FIRMultiFactorSession.h"
#import "FIRTOTPMultiFactorAssertion.h"
#import "FIRTOTPSecret.h"

NS_ASSUME_NONNULL_BEGIN

/** @class FIRTOTPMultiFactorGenerator
    @brief The data structure used to help initialize an assertion for a second factor entity to the
        Firebase Auth/GCIP server. Depending on the type of second factor, this will help generate
        the assertion.
*/
NS_SWIFT_NAME(TOTPMultiFactorGenerator)
@interface FIRTOTPMultiFactorGenerator : NSObject

+ (FIRTOTPSecret *) generateSecretWithMultiFactorSession: (FIRMultiFactorSession *)session;

/** @fn assertionForEnrollmentWithSecret:
    @brief Initializes the MFA assertion to confirm ownership of the totp second factor. This assertion is used to complete enrollment with TOTP as a second factor.
    @param secret The totp secret.
    @param oneTimePassword one time password string.
*/
+ (FIRTOTPMultiFactorAssertion *)assertionForEnrollmentWithSecret: (FIRTOTPSecret *)secret
                                                  oneTimePassword: (NSString *)oneTimePassword;

/** @fn assertionForSignInWithenrollmentId:
    @brief Initializes the MFA assertion to confirm ownership of the totp second factor. This assertion is used to complete signIn with TOTP as a second factor.
    @param erollmentId The id that identifies the enrolled TOTP second factor.
    @param oneTimePassword one time password string.
*/
+ (FIRTOTPMultiFactorAssertion *)assertionForSignInWithenrollmentId: (NSString *)erollmentId
                                                    oneTimePassword: (NSString *)oneTimePassword;

@end

NS_ASSUME_NONNULL_END
