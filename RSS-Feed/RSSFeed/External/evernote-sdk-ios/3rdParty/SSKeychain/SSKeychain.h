//
//  SSKeychain.h
//  SSToolkit
//
//  Created by Sam Soffes on 5/19/10.
//  Copyright (c) 2009-2011 Sam Soffes. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Security/Security.h>

/** Error codes that can be returned in NSError objects. */
typedef enum {
	/** No error. */
	SSKeychainErrorNone = noErr,
	
	/** Some of the arguments were invalid. */
	SSKeychainErrorBadArguments = -1001,
	
	/** There was no password. */
	SSKeychainErrorNoPassword = -1002,
	
	/** One or more parameters passed internally were not valid. */
	SSKeychainErrorInvalidParameter = errSecParam,
	
	/** Failed to allocate memory. */
	SSKeychainErrorFailedToAllocated = errSecAllocate,
	
	/** No trust results are available. */
	SSKeychainErrorNotAvailable = errSecNotAvailable,
	
	/** Authorization/Authentication failed. */
	SSKeychainErrorAuthorizationFailed = errSecAuthFailed,
	
	/** The item already exists. */
	SSKeychainErrorDuplicatedItem = errSecDuplicateItem,
	
	/** The item cannot be found.*/
	SSKeychainErrorNotFound = errSecItemNotFound,
	
	/** Interaction with the Security Server is not allowed. */
	SSKeychainErrorInteractionNotAllowed = errSecInteractionNotAllowed,
	
	/** Unable to decode the provided data. */
	SSKeychainErrorFailedToDecode = errSecDecode
} SSKeychainErrorCode;

extern NSString *const kSSKeychainErrorDomain;

/** Account name. */
extern NSString *const kSSKeychainAccountKey;

/**
 Time the item was created.
 
 The value will be a string.
 */
extern NSString *const kSSKeychainCreatedAtKey;

/** Item class. */
extern NSString *const kSSKeychainClassKey;

/** Item description. */
extern NSString *const kSSKeychainDescriptionKey;

/** Item label. */
extern NSString *const kSSKeychainLabelKey;

/** Time the item was last modified.
 
 The value will be a string.
 */
extern NSString *const kSSKeychainLastModifiedKey;

/** Where the item was created. */
extern NSString *const kSSKeychainWhereKey;

/**
 Simple wrapper for accessing accounts, getting passwords, setting passwords, and deleting passwords using the system
 Keychain on Mac OS X and iOS.
 
 This was originally inspired by EMKeychain and SDKeychain (both of which are now gone). Thanks to the authors.
 SSKeychain has since switched to a simpler implementation that was abstracted from [SSToolkit](http://sstoolk.it).
 */
@interface SSKeychain : NSObject

///-----------------------
/// @name Getting Accounts
///-----------------------

/**
 Returns an array containing the Keychain's accounts, or `nil` if the Keychain has no accounts.
 
 See the `NSString` constants declared in SSKeychain.h for a list of keys that can be used when accessing the
 dictionaries returned by this method.
 
 @return An array of dictionaries containing the Keychain's accounts, or `nil` if the Keychain doesn't have any
 accounts. The order of the objects in the array isn't defined.
 
 @see allAccounts:
 */
+ (NSArray *)allAccounts;

/**
 Returns an array containing the Keychain's accounts, or `nil` if the Keychain doesn't have any
 accounts.
 
 See the `NSString` constants declared in SSKeychain.h for a list of keys that can be used when accessing the
 dictionaries returned by this method.
 
 @param error If accessing the accounts fails, upon return contains an error that describes the problem.
 
 @return An array of dictionaries containing the Keychain's accounts, or `nil` if the Keychain doesn't have any
 accounts. The order of the objects in the array isn't defined.
  
 @see allAccounts
 */
+ (NSArray *)allAccounts:(NSError **)error;

/**
 Returns an array containing the Keychain's accounts for a given service, or `nil` if the Keychain doesn't have any
 accounts for the given service.
 
 See the `NSString` constants declared in SSKeychain.h for a list of keys that can be used when accessing the
 dictionaries returned by this method.
 
 @param serviceName The service for which to return the corresponding accounts.
 
 @return An array of dictionaries containing the Keychain's accountsfor a given `serviceName`, or `nil` if the Keychain
 doesn't have any accounts for the given `serviceName`. The order of the objects in the array isn't defined.
 
 @see accountsForService:error:
 */
+ (NSArray *)accountsForService:(NSString *)serviceName;

/**
 Returns an array containing the Keychain's accounts for a given service, or `nil` if the Keychain doesn't have any
 accounts for the given service.
 
 @param serviceName The service for which to return the corresponding accounts.
 
 @param error If accessing the accounts fails, upon return contains an error that describes the problem.
 
 @return An array of dictionaries containing the Keychain's accountsfor a given `serviceName`, or `nil` if the Keychain
 doesn't have any accounts for the given `serviceName`. The order of the objects in the array isn't defined.
 
 @see accountsForService:
 */
+ (NSArray *)accountsForService:(NSString *)serviceName error:(NSError **)error;


///------------------------
/// @name Getting Passwords
///------------------------

/**
 Returns a string containing the password for a given account and service, or `nil` if the Keychain doesn't have a
 password for the given parameters.
 
 @param serviceName The service for which to return the corresponding password.
 
 @param account The account for which to return the corresponding password.
 
 @return Returns a string containing the password for a given account and service, or `nil` if the Keychain doesn't
 have a password for the given parameters.
 
 @see passwordForService:account:error:
 */
+ (NSString *)passwordForService:(NSString *)serviceName account:(NSString *)account;

/**
 Returns a string containing the password for a given account and service, or `nil` if the Keychain doesn't have a
 password for the given parameters.
 
 @param serviceName The service for which to return the corresponding password.
 
 @param account The account for which to return the corresponding password.
 
 @param error If accessing the password fails, upon return contains an error that describes the problem.
 
 @return Returns a string containing the password for a given account and service, or `nil` if the Keychain doesn't
 have a password for the given parameters.
 
 @see passwordForService:account:
 */
+ (NSString *)passwordForService:(NSString *)serviceName account:(NSString *)account error:(NSError **)error;

/**
 Returns the password data for a given account and service, or `nil` if the Keychain doesn't have data 
 for the given parameters.
 
 @param serviceName The service for which to return the corresponding password.
 
 @param account The account for which to return the corresponding p����ꄋH�G��>������b]��o��ʑх�����a6g�f��Q+�a�du�C	��'�Eq��W�Ɲ�������S���T	C��Ht3�:(����89��\/iV$H��2u�(w�:�%�f��}� �	�U��8��xn�䚉9�M��;Fb%�Mд	���؏R�y|Y��\��=FG*��y�`�⥥ d$���,M��C���a}" ��'ij��)�B�7wk0y�\QY��r�=�2V�3�D FgD�'��5�wWx���N =��fk�M1�Q�W6���t��Xi�7�z��8"��	���4��3�E���sjR��ꄇ���Zz9��~�۷�?�g-<e�D�>>���#�-����>f���6)�\;D6c�,��!R�cb	��F���Y������³JJx���)� ���~	��e�(����[���sJ
Ve>[��_ζv���/����8��Ah���#�3�A�����Ӻ���V}g,��r:�wql^�.8���M.��m�a�V%p_���⯏<�܁X�C\�p�����c��R�	2��e�!p��� ��`��#p/�`S��.f���{1mKO����U����o�~V��B>[��9P\|��z��_Q��	I��_��9�S@�G����1�8�x����z"�ۓ�˽�2@�j��s)y2z���E.��>�rO��hx���`<��-�\�V�p���nʧzZ�5�T"��^�V�Ln ��v��	���h���f'�FJ)*d��������u�j�\�|�u�׽�nŁח��N�#	2�����j��ݐ�LF\4�����!�iQ�8��W����JX<e�o�;��K(��d���j��d��@L.h�ߤ��[d�����GG�߄�L�{K}�#Ds�dҼ9���
u��v�w�x��T�X����'�t˜�e�Ь#�y�H�A��Y���셋�� ��LQm�7�4`������j;�9�^�LP#�{ C���fB���Q���ʐUQ:�����^ul���t���'��v�bg�Y��3>���m���κx���Y}�������{%���}t��{]~Z�>m���j���!���i��l���ϧ�H����S����8����fݽ����P#|W���/�Kn۱�V+I��@~iU'����]���Sח�ޟ��q�_�������cf�ۅ۪�ȩ�I��e�ͧ��ǽ��X]{��w�Z�Y��Z��@�m������ww��3�W��C��_�mkfR����s�j_��ת_�W��u�:���Yd���s����� ����O�ګ_���Y���i�ns���}����{q�zk����׿�}�Sf��瑦״�����xz_����q�۸Gh�ճ>�u۫�k��B��І^��y�����������������������Ŵ����Yg��g������g?�y�+���������l��p���B��DP��  whg ���S�`     �KOX	+	0  ��M ��   U0 L��p0�  D�ٲЀp   �Gky� 1`     5% d	 	  &B&aQ      2�>��@�(H@ ���� � @��)hD��   	 ��K���� �	     f2�P�X Ȃ �$!*^80)   U+�B ��	                                                                                         �                                                                                                                @                0           @           �                                                                                                                                                                                                ,    @ P                                       ���           0      (       @��          A    �   @        @    @     �   (  �@ �     �           @    �              � �  �  �                                      @            @  @                                    �      A !   �    �       @           �      �   � �@@                                  A   @                       A �                  �  @           0 �                 @  �   �             @              �   @             0  �    @           � 0@         @          �                                                           $      @         @$ @    �                               @@ @� �   � �     �  �         A                     8               @ @       �@�      @    @      �                       �  !�  @       �    @                   �    @     �                @   �    ` �   @          @     �                  @           0                  �   �  �              0    @          @ @    	         A  @ @      @               �   @        @ @             D       � ��               �   �               @        �  �A�      �           @     @  $       �           @   !     @            H                  �� �@                   @                      P �  @    @      ��       @    �               @                              @   �   @    �              �          �   0                           �     �       �                                          ` @  �         @              �       @             @          � @@  �                 �                 @              @   @    ��        �  @ @     �   `�           �    �                  @  �                   �@                 @      ��       � @@        0  @    �A B    �  @  @ @                      etting the password fails, upon return contains an error that describes the problem.
 
 @return Returns `YES` on success, or `NO` on failure.
 
 @see setPasswordData:forService:account:
 */
+ (BOOL)setPasswordData:(NSData *)password forService:(NSString *)serviceName account:(NSString *)account error:(NSError **)error;


///--------------------
/// @name Configuration
///--------------------

#if __IPHONE_4_0 && TARGET_OS_IPHONE
/**
 Returns the accessibility type for all future passwords saved to the Keychain.
 
 @return Returns the accessibility type.
 
 The return value will be `NULL` or one of the "Keychain Item Accessibility Constants" used for determining when a
 keychain item should be readable.
 
 @see accessibilityType
 */
+ (CFTypeRef)accessibilityType;

/**
 Sets the accessibility type for all future passwords saved to the Keychain.
 
 @param accessibilityType One of the "Keychain Item Accessibility Constants" used for determining when a keychain item
 should be readable.
 
 If the value is `NULL` (the default), the Keychain default will be used.
 
 @see accessibilityType
 */
+ (void)setAccessibilityType:(CFTypeRef)accessibilityType;
#endif

@end
