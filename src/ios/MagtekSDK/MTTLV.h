//
//  MTTLV.h
//  MTTLVLibrary
//
//  Created by Thien Vu  on 12/30/12.
//  Copyright (c) 2012 MagTek. All rights reserved.
//

#import <Foundation/Foundation.h>

#define TVL_MAX_COUNT	50

typedef unsigned char TLVBYTE;

typedef struct
{
	int	Tag;			  // Name of the super tag, fixed value
	int	Len;			  // Length of tag data value, is given by the TLV data
	unsigned char *Value; // Ptr to tag data value, given by the TLV data
} TagEntry;


typedef struct
{
	int Len;
	TagEntry TLVList[TVL_MAX_COUNT];
} TLV;

@interface MTTLV : NSObject
{
    TLV m_TLVList;
}

#pragma mark -
#pragma mark NSMutableString Properties
#pragma mark -

@property (strong, nonatomic) NSMutableString *TLVStringList;

+ (MTTLV *)sharedInstance;

- (NSInteger)freeTLVList;
- (NSInteger)printTLVList;
- (NSInteger)getTLVListLength;
- (NSMutableString *)returnTLVList;
- (NSInteger)printTLV:(TagEntry)curTLV;

- (NSInteger)pack:(const char *)in
           hexout:(char *)out
        dataInLen:(int)lod;

- (NSInteger)unpack:(const char *)in
             hexout:(char *)out
          dataInLen:(int)lod;

- (NSInteger)getTagLen:(int)tag
                tagLen:(int *) pTagLen;

- (NSInteger)getTLV:(int)tag
           TagEntry:(TagEntry *)pTagEntry;

- (NSInteger)parseSequence:(unsigned char *)pubTLV
                 TLVLength:(int)iTotalLen
                  ErrorMsg:(char *)pcError;

- (NSInteger)getTagValue:(int)tag
                TagValue:(unsigned char *)pubTagValue
                  TagLen:(int *)pTagLen;

- (NSInteger)convertHexStr2Bytes:(NSString *)nstHexStr
                           bytes:(char *)pbytes
                          length:(NSInteger *)len;

- (NSInteger)parseTLVDataObject:(NSString *)nssTLVHexString
                       ErrorMsg:(NSString **)nssErrorMsg;

@end