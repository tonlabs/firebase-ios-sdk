// Copyright 2023 Google LLC
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

import Foundation

@objc(FIRAuthStoredUserManager2) public class AuthStoredUserManager: NSObject {
    /// Key of user access group stored in user defaults. Used for retrieve the
    /// user access group at launch.
    private static let storedUserAccessGroupKey = "firebase_auth_stored_user_access_group"

    /// Default value for kSecAttrAccount of shared keychain items.
    private static let sharedKeychainAccountValue = "firebase_auth_firebase_user"

    /// The key to encode and decode the stored user.
    private static let storedUserCoderKey = "firebase_auth_stored_user_coder_key"

    /// Mediator object used to access the keychain.
    @objc public let keychainServices: AuthSharedKeychainServices
    /// Mediator object used to access user defaults.
    @objc public let userDefaults: AuthUserDefaults

    /// The default initializer is disabled.
    @available(*, unavailable)
    @objc public override init() {
      fatalError("init() has not been implemented")
    }

    /// Designated initializer.
    /// - Parameter serviceName: The service name to initialize with.
    @objc public init(serviceName: String) {
        self.keychainServices = AuthSharedKeychainServices()
        self.userDefaults = AuthUserDefaults(service: serviceName)
    }

    /**
    - (NSString *_Nullable)getStoredUserAccessGroupWithError:(NSError *_Nullable *_Nullable)outError {
      NSData *data = [[self.userDefaults dataForKey:kStoredUserAccessGroupKey error:outError] data];
      if (data) {
        NSString *userAccessGroup = [NSString stringWithUTF8String:data.bytes];
        return userAccessGroup;
      } else {
        return nil;
      }
    }
     */

    /// Get the user access group stored locally.
    /// - Returns: Return value for any error which occurs.
    @objc public func getStoredUserAccessGroup() throws -> String {
        if let data = try userDefaults.data(forKey:Self.storedUserAccessGroupKey).data {
            let userAccessGroup = String(data: data, encoding: .utf8)
            return userAccessGroup
        } else {

        }
    }

    /// The setter of the user access group stored locally.
    /// - Parameter accessGroup: The access group to be set.
    /// - Throws: An error if the operation was not successful.
    @objc(setStoredUserAccessGroup:error:)
    public func setStoredUserAccessGroup(accessGroup: String?) throws {
        return
    }

    // TODO(ncooke3): In the below doc comment, what does "Currently, we use
    // the API key" mean?

    /// The getter of the user stored locally.
    /// - Parameters:
    ///   - accessGroup: The access group to retrieve the user from.
    ///   - shareAuthStateAcrossDevices: If `true`, the keychain will be synced
    ///    across the end-user's iCloud.
    ///   - projectIdentifier: An identifier of the project that the user
    ///   associates with. Currently, we use the API key.
    /// - Returns: The stored user for the given attributes.
    /// - Throws: An error if the operation failed.
    @objc(getStoredUserForAccessGroup:shareAuthStateAcrossDevices:projectIdentifier:error:)
    public func getStoredUser(
        accessGroup: String,
        shareAuthStateAcrossDevices: Bool,
        projectIdentifier: String
    ) throws -> User {
        return Auth.auth().currentUser!
    }

    // TODO(ncooke3): In the below doc comment, what does "Currently, we use
    // the API key" mean?

    /// The setter of the user stored locally.
    /// - Parameters:
    ///   - user: The user to be stored.
    ///   - accessGroup: The access group to store the user in.
    ///   - shareAuthStateAcrossDevices: If `true`, the keychain will be
    ///   synced across the end-user's iCloud.
    ///   - projectIdentifier: An identifier of the project that the user
    ///   associates with. Currently, we use the API key.
    /// - Throws: An error if the operation failed.
    @objc(setStoredUser:forAccessGroup:shareAuthStateAcrossDevices:projectIdentifier:error:)
    public func setStoredUser(
        user: User,
        accessGroup: String,
        shareAuthStateAcrossDevices: Bool,
        projectIdentifier: String
    ) throws {
        return
    }

    // TODO(ncooke3): In the below doc comment, what does "Currently, we use
    // the API key" mean?

    /// Remove the user that stored locally.
    /// - Parameters:
    ///   - accessGroup: The access group to remove the user from.
    ///   - shareAuthStateAcrossDevices: If `true`, the keychain will be
    ///   synced across the end-user's iCloud.
    ///   - projectIdentifier: An identifier of the project that the user
    ///   associates with. Currently, we use the API key.
    /// - Throws: An error if the operation failed.
    @objc(removeStoredUserForAccessGroup:shareAuthStateAcrossDevices:projectIdentifier:error:)
    public func removeStoredUser(
        accessGroup: String,
        shareAuthStateAcrossDevices: Bool,
        projectIdentifier: String
    ) throws {
        return
    }
}
