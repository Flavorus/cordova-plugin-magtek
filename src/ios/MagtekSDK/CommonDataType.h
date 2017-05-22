//
//  CommonDataType.h
//  MTPPSCRA
//
//  Created by Kevin E. Rafferty II on 1/23/13.
//  Copyright (c) 2013 magtek. All rights reserved.

#import <Foundation/Foundation.h>

#ifndef _COMMONDATATYPE_H
#define _COMMONDATATYPE_H

@interface CommonDataType : NSObject

@end

typedef unsigned char TLVBYTELib;

typedef struct
{
	int	Tag;			  // Name of the super tag, fixed value
	int	Len;			  // Length of tag data value, is given by the TLV data
	unsigned char *Value; // Ptr to tag data value, given by the TLV data
} TagEntryLibrary;


typedef struct
{
	int Len;
	TagEntryLibrary TLVList[50];
} TLVLibrary;

@interface CARD_DATA_INFO : NSObject
{
    NSString *KSN;
	NSString *MPSTS;
    NSString *EncMP;
	NSString *Track1;
	NSString *Track2;
	NSString *Track3;
    NSString *cardIIN;
    NSString *cardName;
    NSString *lastName;
    NSString *cardLast4;
    NSString *maskedPAN;
	NSString *EncTrack1;
	NSString *EncTrack2;
	NSString *EncTrack3;
    NSString *firstName;
    NSString *middleName;
    NSString *cardExpDate;
    NSString *SREDRawData;
    NSString *cardTypeString;
    NSString *EncTrack1Status;
	NSString *EncTrack2Status;
	NSString *EncTrack3Status;
    NSString *cardServiceCode;
    NSString *globalBlobString;
    NSString *transactionStatus;
    NSString *track1DecodeStatus;
    NSString *track2DecodeStatus;
    NSString *track3DecodeStatus;
    NSString *additionalInfoTrack1;
    NSString *additionalInfoTrack2;
    
    NSMutableString *TLVStringList;
    
    unsigned char encryptedTrack2Length;
    
	unsigned char DataType;
	unsigned char CardOperationStatus;
	unsigned char CardStatus;
	unsigned char CardType;
    
	unsigned char Track1Length;
	unsigned char Track2Length;
	unsigned char Track3Length;
	unsigned char EncTrack1Length;
	unsigned char EncTrack2Length;
	unsigned char EncTrack3Length;
	unsigned char EncMPLength;
    
	unsigned char Track1Status;
	unsigned char Track2Status;
	unsigned char Track3Status;
	unsigned char EncMPStatus;
	unsigned char MSStatus;
    
    TLVLibrary m_TLVList;
}

#pragma mark -
#pragma mark CARD_DATA_INFO Primitive Type Properties
#pragma mark -

@property BOOL isFirmwareSRED;
@property BOOL doesICCCardRequireSignature;;

#pragma mark -
#pragma mark CARD_DATA_INFO NSString Properties
#pragma mark -

@property (nonatomic, strong) NSString *KSN;
@property (nonatomic, strong) NSString *MPSTS;
@property (nonatomic, strong) NSString *EncMP;
@property (nonatomic, strong) NSString *Track1;
@property (nonatomic, strong) NSString *Track2;
@property (nonatomic, strong) NSString *Track3;
@property (nonatomic, strong) NSString *cardIIN;
@property (nonatomic, strong) NSString *lastName;
@property (nonatomic, strong) NSString *cardName;
@property (nonatomic, strong) NSString *cardLast4;
@property (nonatomic, strong) NSString *maskedPAN;
@property (nonatomic, strong) NSString *EncTrack1;
@property (nonatomic, strong) NSString *EncTrack2;
@property (nonatomic, strong) NSString *EncTrack3;
@property (nonatomic, strong) NSString *firstName;
@property (nonatomic, strong) NSString *middleName;
@property (nonatomic, strong) NSString *encodeType;
@property (nonatomic, strong) NSString *cardExpDate;
@property (nonatomic, strong) NSString *SREDRawData;
@property (nonatomic, strong) NSString *cardTypeString;
@property (nonatomic, strong) NSString *cardServiceCode;
@property (nonatomic, strong) NSString *globalBlobString;
@property (nonatomic, strong) NSString *transactionStatus;
@property (nonatomic, strong) NSString *track1DecodeStatus;
@property (nonatomic, strong) NSString *track2DecodeStatus;
@property (nonatomic, strong) NSString *track3DecodeStatus;
@property (nonatomic, strong) NSString *additionalInfoTrack1;
@property (nonatomic, strong) NSString *additionalInfoTrack2;

#pragma mark -
#pragma mark CARD_DATA_INFO NSMutableString Properties
#pragma mark -

@property (strong, nonatomic) NSMutableString *TLVStringList;

#pragma mark -
#pragma mark CARD_DATA_INFO Methods
#pragma mark -

/*
 METHOD         - ClearCardData
 
 PARAMETERS     - N/A
 
 RETURN         - N/A
 
 DESCRIPTION    - This method simply sets all of the unsigned char instance variables to 0 and NSString property variables to @""
 */
- (void)clearCardData;

- (NSInteger)parseTLVData:(NSString *)cardData;

/*
 METHOD         - parseCardData:(NSString *)cardData
 
 PARAMETERS     - cardData: of type NSString - NSString containing the specific string to parse from the card data
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method takes as a parameter cardData and parses the specific string from the full card data
 */
- (NSInteger)parseCardData:(NSString *)cardData;

@end

@interface PINDATA : NSObject
{
	NSString *KSN;
	NSString *EPB;
    NSString *statusCode;
    
    unsigned char OpStatus;
}

#pragma mark -
#pragma mark PINDATA NSString Properties
#pragma mark -

@property (nonatomic, retain) NSString *KSN;
@property (nonatomic, retain) NSString *EPB;
@property (nonatomic, retain) NSString *statusCode;

#pragma mark -
#pragma mark PINDATA Unsigned Char Properties
#pragma mark -

@property (nonatomic, readwrite) unsigned char OpStatus;

#pragma mark -
#pragma mark PINDATA Methods
#pragma mark -

/*
 METHOD         - clearPINDataBuffer
 
 PARAMETERS     - N/A
 
 RETURN         - N/A
 
 DESCRIPTION    - This method simply sets all of the unsigned char instance variables to 0 and NSString property variables to @""
 */
- (void)clearPINData;

/*
 METHOD         - parsePINData:(NSString *)data
 
 PARAMETERS     - pinData: of type NSString - NSString containing the specific string to parse from the PIN data
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method takes as a parameter pinData and parses the specific string from the full PIN data
 */
- (NSInteger)parsePINData:(NSString *)pinData;

@end

@interface USER_ENTRY_DATA : NSObject
{
    NSString *EDB;
    NSString *MSRKSN;
    
    unsigned char OpStatus;
}

#pragma mark -
#pragma mark USER_ENTRY_DATA NSString Properties
#pragma mark -

@property (nonatomic, retain) NSString *EDB;
@property (nonatomic, retain) NSString *MSRKSN;

#pragma mark -
#pragma mark USER_ENTRY_DATA Unsigned Char Properties
#pragma mark -

@property (nonatomic, readwrite) unsigned char OpStatus;

#pragma mark -
#pragma mark USER_ENTRY_DATA Methods
#pragma mark -

/*
 METHOD         - clearUserDataBuffer
 
 PARAMETERS     - N/A
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method simply sets all of the unsigned char instance variables to 0 and NSString property variables to @""
 */
- (NSInteger)clearUserDataBuffer;

/*
 METHOD         - parseUserEntryData:(NSString *)userEntryData;
 
 PARAMETERS     - userEntryData: of type NSString - NSString containing the specific string to parse from the user entry data
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method takes as a parameter userEntryData and parses the specific string from the full user entry data
 */
- (NSInteger)parseUserEntryData:(NSString *)userEntryData;

@end

@interface DEV_STATE_STAT : NSObject
{
    unsigned char nHWStatus;
    unsigned char nDeviceState;
    unsigned char nSessionState;
    unsigned char nDeviceStatus;
    unsigned char nDevCertStatus;
    unsigned char nSessionKeyStatus;
}

#pragma mark -
#pragma mark DEV_STATE_STAT Unsigned Char Properties
#pragma mark -

@property (nonatomic, readwrite) unsigned char nHWStatus;
@property (nonatomic, readwrite) unsigned char nDeviceState;
@property (nonatomic, readwrite) unsigned char nSessionState;
@property (nonatomic, readwrite) unsigned char nDeviceStatus;
@property (nonatomic, readwrite) unsigned char nDevCertStatus;
@property (nonatomic, readwrite) unsigned char nSessionKeyStatus;

#pragma mark -
#pragma mark DEV_STATE_STAT Methods
#pragma mark -

/*
 METHOD         - clearDeviceStateBuffer
 
 PARAMETERS     - N/A
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method simply sets all of the unsigned char instance variables to 0
 */
- (NSInteger)clearDeviceStateBuffer;

@end

#endif