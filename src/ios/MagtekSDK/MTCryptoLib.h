//
//  MTCryptoLib.h
//  MTCryptographicLibrary
//
//  Created by Thien Vu on 12/16/12.
//  Copyright (c) 2012 MagTek. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonCryptor.h>

#define  BLOCK_BYTES 8

#define KSN_LEN  10
#define PINB_LEN 8

#define KSID_BUF_SIZE   8
#define KSNR_BUF_SIZE   8
#define SINGLE_LEN_KEY  8
#define DOUBLE_LEN_KEY  16
#define TRIPPLE_LEN_KEY 24
#define ERR_BUF_SIZE    128

typedef uint8_t CryptorByte;

union le_long_long_array_u
{
    uint8_t byte[8];
    uint64_t longlong;
} le_long_long_array;

enum
{
    DES1_BUF_SIZE = 8,
    DES2_BUF_SIZE = 16,
    DES3_BUF_SIZE = 24,
    KSN_BUF_SIZE  = 10,
    IV_BUF_SIZE   = 8
};

enum  CRYPTO_STATUS
{
    RR_EXCEPTION                     = -1,
    RET_OK                           = 0,
    ERR_UNSUPPORT_DES_OP             = 1,
    ERR_INVALID_LEN                  = 2,
    ERR_INVALID_KEY_LEN              = 3,
    ERR_INVALID_KEY_REFERENCE        = 4,
    ERR_UNSUPPORT_DES_TYPE           = 5,
    ERR_UNSUPPORT_DUKPT_VARIANT_TYPE = 6
};

enum DUKPT_KeyVariantType
{
    PIN_ENCRYPTION                      = 0,
    MAC_REQUEST_OR_BOTHWAYS             = 1,
    MAC_RESPONSE                        = 2,
    DATA_ENCRYPTION_REQUEST_OR_BOTHWAYS = 3,
    DATA_ENCRYPTION_RESPONSE            = 4
};

@interface MTCryptoLib : NSObject
{
    NSString *someData;
}

@property (nonatomic, retain) NSString *someData;

+ (MTCryptoLib*)sharedInstance;

+ (void)testConvert2UInt64;
+ (NSString *)getSomeData;
+ (void) setSomeData:(NSString *)someData;
- (NSData *)nsdataFromHexString:(NSString *)string;

+ (NSString *)getCurrentKeyFromBDKWithBDK:(const unsigned char *)pBDK
                                  withKSN:(const unsigned char *)pKSN
                            withKeyLength:(int)keyLength;

+ (NSInteger)DeriveInitialKey:(CryptorByte *)bdk
                      pksn_in:(CryptorByte *)pksn_in
                         pIEK:(CryptorByte *)pIEK;

+ (NSInteger)DeriveCurrentKey:(enum DUKPT_KeyVariantType)eKeyType
                        pIKSN:(CryptorByte *)pIKSN
                    pLeftILPK:(CryptorByte *)pLeftILPK
                   pRightILPK:(CryptorByte *)pRightILPK
               pResultKeyLeft:(CryptorByte *)pResultKeyLeft
              pResultKeyRight:(CryptorByte *)pResultKeyRight
                       errstr:(char *) errstr;

+ (NSInteger)DeriveCurrentKeyFromBDK:(enum DUKPT_KeyVariantType)eKeyType
                                 BDK:(const CryptorByte *)pBDK
                           keyLength:(int)keyLen
                                 KSN:(const CryptorByte *)pKSN
                      pResultKeyLeft:(CryptorByte *)pResultKeyLeft
                     pResultKeyRight:(CryptorByte * )pResultKeyRight
                              errstr:(char *) errstr;


+ (NSInteger)CalculateCBC_MAC:(const CryptorByte *)pubKeyLeft
                  pubKeyRight:(const CryptorByte *)pubKeyRight
                   pubKeyLast:(const CryptorByte *)pubKeyLast
                           IV:(const CryptorByte *)IV
               pubData2bMACed:(const CryptorByte *)pubData2bMACed
                  iMACDataLen:(int)iMACDataLen
              pubPaddedMACMsg:(CryptorByte *)pubPaddedMACMsg
                iPaddingBytes:(int *)iPaddingBytes
                       pubMAC:(CryptorByte *)pubMAC;

+ (NSInteger)CalculateCBCMAC:(const CryptorByte *)BDK
                   keyLength:(int)keyLen
                         KSN:(const CryptorByte[KSN_BUF_SIZE])pKSN
                          IV:(const CryptorByte[IV_BUF_SIZE])IV
              pubData2bMACed:(const CryptorByte *)pubData2bMACed
                 iMACDataLen:(int)iMACDataLen
             pubPaddedMACMsg:(CryptorByte *)pubPaddedMACMsg
               iPaddingBytes:(int *)iPaddingBytes
                      pubMAC:(CryptorByte *)pubMAC;

+ (NSInteger)Calculate_CBCMAC:(const CryptorByte *)BDK
                    keyLength:(int)keyLen
                          KSN:(const CryptorByte[KSN_BUF_SIZE])pKSN
                           IV:(const CryptorByte[IV_BUF_SIZE])IV
                   MACmessage:(const CryptorByte *)pubData2bMACed   //must be multiple of 8
             MACmessageLength:(int)iMACDataLen               //must be multiple of 8
                       pubMAC:(CryptorByte *)pubMAC;

+ (NSInteger)constructEMVTagMessageWithAMK1:(const unsigned char *)AMK
                         deviceSerialNumber:(const unsigned char *)deviceSerialNumber
                                       tags:(unsigned char *)tags
                                  tagLength:(int)tagLength
                            commandToDevice:(unsigned char *)commandToDevice
                      commandToDeviceLength:(int *)commandToDeviceLength;

+ (NSInteger)constructEMVTagMessageWithAMK:(const unsigned char *)AMK
                        deviceSerialNumber:(const unsigned char *)deviceSerialNumber
                     deviceSerialNumberLen:(unsigned char)deviceSerialNumberLen
                                   tlvBlob:(unsigned char *)tlvBlob
                                tlvBlobLen:(int)tlvBlobLen
                          isSettingEMVTags:(BOOL)isSettingEMVTags
                           commandToDevice:(unsigned char *)commandToDevice
                     commandToDeviceLength:(int *)commandToDeviceLength;

+ (NSInteger)constructBINMessageWithAMK:(const unsigned char *)AMK
                     deviceSerialNumber:(const unsigned char *)deviceSerialNumber
               deviceSerialNumberLength:(int)deviceSerialNumberLength
                                tlvData:(unsigned char *)tlvData
                          tlvDataLength:(int)tlvDataLength
                        commandToDevice:(unsigned char *)commandToDevice
                  commandToDeviceLength:(int *)commandToDeviceLength;

+ (NSInteger)ConstructAcqMsg:(const unsigned char *)BDK
                   keyLength:(int)keyLen
                         ksn:(const unsigned char *)ksn
                          IV:(const unsigned char *)iv
                    deviceSN:(const unsigned char *)serial
                      acqMsg:(unsigned char *)data
                   acqMsgLen:(int)dataLen
                  cmd2device:(unsigned char *)pubCommand2Device
               cmd2DeviceLen:(int *)pCmdLen;

+ (NSInteger)constructMACMsg:(const unsigned char *)AMK
          deviceSerialNumber:(const unsigned char *)deviceSerialNumber
                        data:(unsigned char *)data
                  dataLength:(int)dataLength
             commandToDevice:(unsigned char *)commandToDevice
       commandToDeviceLength:(int *)commandToDeviceLength;

- (NSInteger)EncryptECB:(NSString *)desKey
                 dataIn:(NSString *)hexIn
               edataOut:(NSString **)encHexOut;

- (NSInteger)Encrypt3ECB:(NSString *)desKey
                  dataIn:(NSString *)hexIn
                edataOut:(NSString **)encHexOut;

#pragma mark -
#pragma mark CMAC Methods
#pragma mark -

+(NSInteger)CMAC_xor_64:(CryptorByte *)a
                      b:(CryptorByte *)b
                    out:(CryptorByte *)Out;

+(NSInteger) CMAC_xor_64:(CryptorByte *)a
                       b:(CryptorByte *)b
                     out:(CryptorByte *)Out
                    size:(int)size;

+(NSInteger) XOR_bytes:(CryptorByte *)a
                     b:(CryptorByte *)b
                   out:(CryptorByte *)Out
                  size:(int)size;


+(NSInteger)CMAC_generate_subkey:(CryptorByte *)key
                              K1:(CryptorByte *)K1
                              K2:(CryptorByte *)K2;

+(NSInteger)CMAC_padding:(CryptorByte *)lastb
                  length:(NSInteger)length
                  padOut:(CryptorByte *)pad;

+(NSInteger)CMAC_leftshift_onebit:(CryptorByte *)input
                         inputLen:(NSInteger)inLen
                           output:(CryptorByte *)output;

+(NSInteger)CMAC_Generate:(CryptorByte *)key
                    input:(CryptorByte *)input
                 inputLen:(int)inputLen
                   output:(CryptorByte *)mac;

+(bool)CMAC_Verify:(CryptorByte *)key
             input:(CryptorByte *)input
            length:(int)length
      expectedCMAC:(CryptorByte *)expectedCMAC
   expectedCMACLen:(int)expectedCMACLen;

+(NSInteger)Encrypt3ECB:(CryptorByte *)key
                 dataIn:(CryptorByte *)pDataIn
                dataLen:(NSInteger)dataLen
                dataout:(CryptorByte *)pdataout
             dataOutLen:(size_t *)pdataOutLen;

+ (NSInteger)Decrypt3CBC:(CryptorByte *)key
                      IV:(CryptorByte *)IV
                  dataIn:(CryptorByte *)pDataIn
                 dataLen:(NSInteger)dataLen
                 dataout:(CryptorByte *)pdataout
              dataOutLen:(size_t *)pdataOutLen;

+ (NSInteger)Encrypt3CBC:(CryptorByte *)key
                      IV:(CryptorByte *)IV
                  dataIn:(CryptorByte *)pDataIn
                 dataLen:(NSInteger)dataLen
                 dataout:(CryptorByte *)pdataout
              dataOutLen:(size_t *)pdataOutLen;


+ (NSInteger)CMAC_CreateL1Session:(CryptorByte *)Amk
                        challenge:(CryptorByte *)challenge
                     expectedCMAC:(CryptorByte *)expectedCMAC
                  expectedCMACLen:(NSInteger)expectedCMACLen
                 encTransRndSerNo:(CryptorByte *)encTransRndSerNumber
                             CMAC:(CryptorByte *)CMAC
                       SessionKey:(CryptorByte *)SessionKey
                   SessionCMACKey:(CryptorByte *)SessionCMACKey;

+ (NSInteger)Encrypt3CBCandCalculateCMAC:(CryptorByte *)sessionKey
                          sessionCMACKey:(CryptorByte *)sessionCMACKey
                           fAddHeaderLen:(BOOL)fAddHeaderLen
                                  dataIn:(CryptorByte *)dataIn
                               dataInLen:(int)dataInLen
                                edataOut:(CryptorByte *)edataOut
                              dataOutLen:(int *)dataOutLen
                                 CMACout:(CryptorByte *)CMACout
                              CMACoutLen:(int)CMACoutLen;

+ (NSInteger)EncryptandCMAC:(CryptorByte *)sessionKey
             sessionCMACKey:(CryptorByte *)sessionCMACKey
                     dataIn:(CryptorByte *)dataIn
                  dataInLen:(int)dataInLen
                data2Device:(CryptorByte *)data2Device
             data2DeviceLen:(int *)data2DeviceLen;

@end