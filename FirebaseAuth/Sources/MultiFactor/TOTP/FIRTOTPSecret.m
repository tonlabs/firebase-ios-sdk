/*
 * Copyright 2023 Google LLC
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
#import <TargetConditionals.h>
#if TARGET_OS_IOS

#import <UIKit/UIKit.h>
#import "FirebaseAuth/Sources/MultiFactor/TOTP/FIRTOTPSecret+Internal.h"
#import "FirebaseAuth/Sources/Public/FirebaseAuth/FIRTOTPSecret.h"
NS_ASSUME_NONNULL_BEGIN

@implementation FIRTOTPSecret

// explicity synthesize
@synthesize secretKey = _secretKey;
@synthesize hashingAlgorithm = _hashingAlgorithm;
@synthesize enrollmentCompletionDeadline = _enrollmentCompletionDeadline;
@synthesize codeLength = _codeLength;
@synthesize codeIntervalSeconds = _codeIntervalSeconds;
@synthesize sessionInfo = _sessionInfo;

- (instancetype)initWithSecretKey:(NSString *)secretKey
                 hashingAlgorithm:(NSString *)hashingAlgorithm
                       codeLength:(NSInteger)codeLength
              codeIntervalSeconds:(NSInteger)codeIntervalSeconds
     enrollmentCompletionDeadline:(NSDate *)enrollmentCompletionDeadline
                      sessionInfo:(NSString *)sessionInfo {
  self = [super init];
  if (self) {
    _secretKey = secretKey;
    _hashingAlgorithm = hashingAlgorithm;
    _codeLength = codeLength;
    _codeIntervalSeconds = codeIntervalSeconds;
    _enrollmentCompletionDeadline = [enrollmentCompletionDeadline copy];
    _sessionInfo = sessionInfo;
  }
  return self;
}

- (NSString *)sharedSecretKey {
  return _secretKey;
}

- (NSString *)hashAlgorithm {
  return _hashingAlgorithm;
}

- (NSInteger)codeLength {
  return _codeLength;
}

- (NSInteger)codeIntervalSeconds {
  return _codeIntervalSeconds;
}

- (NSDate *)enrollmentCompletionDeadline {
  return _enrollmentCompletionDeadline;
}

- (NSString *)generateQRCodeURLWithAccountName:(NSString *)accountName issuer:(NSString *)issuer {
  NSString *urlString = [NSString
      stringWithFormat:@"otpauth://totp/%@:%@?secret=%@&issuer=%@&algorithm=%@&digits=%ld", issuer,
                       accountName, self.secretKey, issuer, self.hashingAlgorithm, self.codeLength];
  printf(@"%s", [NSString stringWithFormat:@"urlstring look s like = %@", urlString]);
  return urlString;
}

- (void)openInOTPAppWithQRCodeURL:(NSString *)QRCodeURL {
  NSURL *url = [NSURL URLWithString:QRCodeURL];
  if ([[UIApplication sharedApplication] canOpenURL:url]) {
    [[UIApplication sharedApplication] openURL:url options:@{} completionHandler:nil];
  } else {
    NSLog(@"Cannot open URL");
  }
}
@end

NS_ASSUME_NONNULL_END
#endif