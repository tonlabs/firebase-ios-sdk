// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

@class FIRAppDistributionRelease;
@class UIApplication;
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The Firebase App Distribution API provides methods to check for update to
 * the app and returns information that enables updating the app.
 *
 * By default, Firebase App Distribution is initialized with `FirebaseApp.configure()`.
 *
 * Note: The App Distribution class cannot be subclassed. If this makes testing difficult,
 * we suggest using a wrapper class or a protocol extension.
 */

NS_EXTENSION_UNAVAILABLE_IOS("Firebase App Distribution is not supported for iOS extensions.")
NS_SWIFT_NAME(AppDistribution)
@interface FIRAppDistribution : NSObject

/// Returns true if the App Distribution tester is signed in.
@property(nonatomic, readonly) BOOL isTesterSignedIn;

/** :nodoc: */
- (instancetype)init NS_UNAVAILABLE;

/**
 * Sign-in the App Distribution tester
 */
- (void)signInTesterWithCompletion:(void (^)(NSError *_Nullable error))completion
    NS_SWIFT_NAME(signInTester(completion:));

/**
 * Check to see whether a new distribution is available
 */
- (void)checkForUpdateWithCompletion:(void (^)(FIRAppDistributionRelease *_Nullable_result release,
                                               NSError *_Nullable error))completion
    NS_SWIFT_NAME(checkForUpdate(completion:));

/**
 * Sign out App Distribution tester
 */
- (void)signOutTester;

/**
 * Take a screenshot, prompt the tester to sign in if they haven't already, the start a modal view
 * controller to collect and submit feedback from the tester.
 *
 * @param additionalFormText Text to display to the tester before collecting feedback data (eg.
 * Terms and Conditions).
 *
 * Note: The programmatic screenshot may not be able to capture everything on the tester's display.
 *       Consider using `enableFeedbackOnScreenshot`.
 */
- (void)startFeedbackWithAdditionalFormText:(NSString *)additionalFormText
    NS_SWIFT_NAME(startFeedback(additionalFormText:));

/**
 * Start a modal view controller to collect and submit feedback from the tester and attach the
 * image that's provided.
 *
 * @param additionalFormText Text to display to the tester before collecting feedback data (eg.
 * Terms and Conditions).
 * @param image UIImage to attach to the feedback. No image if nil is passed.
 */
- (void)startFeedbackWithAdditionalFormText:(NSString *)additionalFormText
                                      image:(UIImage *)image
    NS_SWIFT_NAME(startFeedback(additionalFormText:image:));

/**
 * After calling the method, whenever a tester takes a screenshot, request access to it if needed,
 * prompt the tester to sign in if they haven't already, and start a modal view controller to
 * collect and submit feedback.
 *
 * @param additionalFormText Text to display to the tester before collecting feedback data (eg.
 * Terms and Conditions).
 * @param showAlertInfo Boolean that indicates whether to show a UIAlert which tells the user that
 * capturing a screenshot will start the feedback process.
 *
 * Note: Using this method requires you to add `NSPhotoLibraryUsageDescription` to your Info.plist,
 * otherwise the app will crash.
 */
- (void)enableFeedbackOnScreenshotWithAdditionalFormText:(NSString *)additionalFormText
                                           showAlertInfo:(BOOL)showAlertInfo
    NS_SWIFT_NAME(startFeedbackOnScreenshot(additionalFormText:showAlertInfo:));

/**
 * Handle an App Distribution URL, for example a link to download a new pre-release version.
 * Call this method in your app delegate's `openURL` implementation if swizzling is disabled.
 */
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
            options:(NSDictionary<NSString *, id> *)options;

/**
 * Accesses the singleton App Distribution instance.
 *
 * @return The singleton App Distribution instance.
 */
+ (instancetype)appDistribution NS_SWIFT_NAME(appDistribution());

@end

/// The error domain for codes in the `FIRAppDistributionError` enum.
// clang-format off
// clang-format12 will merge lines and exceed 100 character limit.
FOUNDATION_EXPORT NSString *const FIRAppDistributionErrorDomain
    NS_SWIFT_NAME(AppDistributionErrorDomain);

/// The key for finding error details in the `NSError`'s `userInfo`.
FOUNDATION_EXPORT NSString *const FIRAppDistributionErrorDetailsKey
    NS_SWIFT_NAME(AppDistributionErrorDetailsKey);
// clang-format on

/**
 * Error codes representing sign in or version check failure reasons.
 */
typedef NS_ERROR_ENUM(FIRAppDistributionErrorDomain, FIRAppDistributionError){
    /// Returned when an unknown error occurred.
    FIRAppDistributionErrorUnknown = 0,

    /// Returned when App Distribution failed to authenticate the user.
    FIRAppDistributionErrorAuthenticationFailure = 1,

    /// Returned when sign-in was cancelled.
    FIRAppDistributionErrorAuthenticationCancelled = 2,

    /// Returned when the network was unavailable to make requests or
    /// the request timed out.
    FIRAppDistributionErrorNetworkFailure = 3,

} NS_SWIFT_NAME(AppDistributionError);

NS_ASSUME_NONNULL_END
