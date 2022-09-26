/*
 * Copyright 2021 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <Foundation/Foundation.h>

#import "FIRAppCheckProvider.h"

#import "FIRAppCheckAvailability.h"

@class FIRApp;

NS_ASSUME_NONNULL_BEGIN

/// Firebase App Check provider that verifies app integrity using the
/// [AppAttest](https://developer.apple.com/documentation/devicecheck/dcappattestservice) service.
///
/// This class is available on all platforms for select OS versions:
/// |  Platform   | Versions |
/// |:-----------:| :-------:|
/// | iOS         |  14.0+   |
/// | tvOS        |  15.0+   |
/// | watchOS     |  9.0+    |
/// | macOS       |  11.0+   |
/// | macCatalyst |  14.5+   |
///
FIR_APP_ATTEST_PROVIDER_AVAILABILITY
NS_SWIFT_NAME(AppAttestProvider)
@interface FIRAppAttestProvider : NSObject <FIRAppCheckProvider>

- (instancetype)init NS_UNAVAILABLE;

/// The default initializer.
/// @param app A `FirebaseApp` instance.
/// @return An instance of `AppAttestProvider` if the provided `FirebaseApp`
///  instance contains all required parameters.
- (nullable instancetype)initWithApp:(FIRApp *)app;

@end

NS_ASSUME_NONNULL_END
