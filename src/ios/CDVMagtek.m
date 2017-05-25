#import "CDVMagtek.h"

@interface CDVMagtek()

// @property (strong, nonatomic) MTPPSCRA* magtek;
// @property bool deviceConnected;
// @property bool deviceOpenned;

@end

@implementation CDVMagtek

static unsigned char m_sessionKey[24];
static NSString *dataCallbackId = nil;
static NSString *bdk = nil;


#pragma mark -
#pragma mark Device Connection
#pragma mark -

- (void)pluginInitialize
{
    MTPPSCRA* magtek = [MTPPSCRA shareInstance];
    magtek.delegate2 = self;
    [magtek setMTPPSCRALibrary];
    [self openDevice];
    NSLog(@"MagTek Plugin initialized");
}

- (void)init: (CDVInvokedUrlCommand *) command {
    // // self.magtek = [[MTPPSCRA alloc] init];
    [self.commandDelegate runInBackground:^{
        //		MTPPSCRA* magtek = [MTPPSCRA shareInstance];
        //		magtek.delegate2 = self;
        //		[magtek setMTPPSCRALibrary];
        //
        //		 [self openDevice];
        if (command.arguments.count > 0) {
            bdk = [command.arguments objectAtIndex:0];
        }
        
        dataCallbackId = command.callbackId;
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        [result setKeepCallbackAsBool:YES];
        [self.commandDelegate sendPluginResult:result callbackId:dataCallbackId];
    }];
}

- (void)getDiscoveredPeripherals: (CDVInvokedUrlCommand*) command {
    [self.commandDelegate runInBackground:^{
        MTPPSCRA* magtek = [MTPPSCRA shareInstance];
        NSMutableArray *peripherals = [[NSMutableArray alloc] init];
        for (CBPeripheral *peripheral in [magtek getDiscoveredPeripherals]){
            [peripherals addObject:[self peripheralToDictionary:peripheral]];
        }
        NSLog(@"Peripherals: %@", peripherals);
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsMultipart:[peripherals copy]];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

- (void)startScanningForPeripherals: (CDVInvokedUrlCommand *) command {
    [self.commandDelegate runInBackground:^{
        MTPPSCRA* magtek = [MTPPSCRA shareInstance];
        NSLog(@"startScanningForPeripherals");
        [magtek startScanningForPeripherals];
    }];
}

- (void)stopScanningForPeripherals: (CDVInvokedUrlCommand *) command {
    [self.commandDelegate runInBackground:^{
        MTPPSCRA* magtek = [MTPPSCRA shareInstance];
        NSLog(@"stopScanningForPeripherals");
        [magtek stopScanningForPeripherals];
    }];
}

- (void)connectToBLEReader: (CDVInvokedUrlCommand *) command {
    [self.commandDelegate runInBackground:^{
        MTPPSCRA* magtek = [MTPPSCRA shareInstance];
        NSString* identifier = nil;
        if (command.arguments.count > 0) {
            identifier = [command.arguments objectAtIndex:0];
        }
        if([[magtek getConnectedPeripheral] state] == CBPeripheralStateConnected) {
            [self closeDevice];
        }
        NSLog(@"Connecting to %@", identifier);
        [magtek setDeviceUUIDString:identifier];
        [self openDevice];
    }];
}

- (void)disconnectFromBLEReader: (CDVInvokedUrlCommand *) command {
    [self.commandDelegate runInBackground:^{
        [self closeDevice];
    }];
}

- (void)isDeviceConnected: (CDVInvokedUrlCommand*) command {
    [self.commandDelegate runInBackground:^{
        MTPPSCRA* magtek = [MTPPSCRA shareInstance];
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:[magtek isDeviceConnected]];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}
- (void)isDeviceOpened: (CDVInvokedUrlCommand*) command {
    [self.commandDelegate runInBackground:^{
        MTPPSCRA* magtek = [MTPPSCRA shareInstance];
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:[magtek isDeviceOpened]];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

- (void)getConnectedPeripheral: (CDVInvokedUrlCommand*) command {
    [self.commandDelegate runInBackground:^{
        MTPPSCRA* magtek = [MTPPSCRA shareInstance];
        CBPeripheral* peripheral = [magtek getConnectedPeripheral];
        NSLog(@"%@", peripheral);
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:[self peripheralToDictionary:peripheral]];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

#pragma mark -
#pragma mark Device Operations
#pragma mark -

- (void)cancelOperation: (CDVInvokedUrlCommand*) command {
    [self.commandDelegate runInBackground:^{
        [[MTPPSCRA shareInstance] cancelOperation];
    }];
}

- (void)deviceReset: (CDVInvokedUrlCommand*) command {
    [self.commandDelegate runInBackground:^{
        NSInteger response = [[MTPPSCRA shareInstance] deviceReset];
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsNSInteger:response];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

#pragma mark Device Connection Helpers

- (void)openDevice {
    MTPPSCRA* magtek = [MTPPSCRA shareInstance];
    
    switch([magtek getDeviceType])
    {
        case MAGTEKDYNAPROMINIUART:
            // if the EASession is not already open then we open the EASession
            [magtek setDeviceType:(MAGTEKDYNAPROMINIUART)];
            // NSString* identifier = [self loadPeripheral];
            // if (identifier)
            // 	[magtek setDeviceUUIDString:identifier];
            
            if([magtek isDeviceOpened] == NO)
            {
                [magtek openDevice];
            }
            
            break;
            
        case MAGTEKDYNAPROMINIBLE:
        {
            [magtek setDeviceType:(MAGTEKDYNAPROMINIBLE)];
            // NSString* identifier = [self loadPeripheral];
            // if (identifier)
            // 	[magtek setDeviceUUIDString:identifier];
            [magtek openDevice];
            break;
            
        }
            
        default:
            break;
    }
    // [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:[magtek isDeviceOpened]] callbackId:command.callbackId];
}

- (void)closeDevice {
    MTPPSCRA* magtek = [MTPPSCRA shareInstance];
    if([magtek isDeviceConnected])
    {
        [magtek closeDevice];
    }
}

- (BOOL)checkIfDeviceIsSRED
{
    MTPPSCRA *mtPPSCRA = [MTPPSCRA shareInstance];
    
    NSString *errorString = @"";
    
    BOOL isSRED = [mtPPSCRA isDeviceSRED:&errorString];
    
    // If the errorString is not empty then we received an error
    if(![errorString isEqualToString:@""])
    {
        NSLog(@"isDeviceSRED Error - %@", errorString);
    }
    
    return isSRED;
}

// - (NSString *)loadPeripheral
// {
//     // retrieve the stored Peripheral if any
//     NSUserDefaults *userDefaults     = [NSUserDefaults standardUserDefaults];
//     NSArray        *peripheralArray  = [userDefaults   objectForKey:@"storedPeripheral"];

//     if([peripheralArray isKindOfClass:[NSArray class]])
//     {
//         if([peripheralArray count] > 0)
//         {
//             for(id deviceUUIDString in peripheralArray)
//             {
//                 if(![deviceUUIDString isKindOfClass:[NSString class]])
//                 {
//                     continue;
//                 }

//                 return deviceUUIDString;
//             }
//         }
//     }

//     return @"";
// }

// - (void)savePeripheral
// {
//     MTPPSCRA *mtPPSCRA = [MTPPSCRA shareInstance];

//     // retrieve the currently connected Peripheral information
//     CBPeripheral *peripheral = [mtPPSCRA getConnectedPeripheral];

//     // store the Peripheral information for automatic connection later
//     NSUserDefaults *userDefaults           = [NSUserDefaults standardUserDefaults];
//     NSMutableArray *newDevicesMutableArray = [[NSMutableArray alloc] init];

//     NSString *uuidString = [NSString stringWithFormat:@"%@", [[peripheral identifier] UUIDString]];

//     if(![uuidString isEqualToString:@""])
//     {
//         [newDevicesMutableArray addObject:uuidString];

//         [userDefaults setObject:newDevicesMutableArray
//                          forKey:@"storedPeripheral"];

//         [userDefaults synchronize];
//     }
//     else
//     {
//     }
// }

#pragma mark -
#pragma mark Transaction Methods
#pragma mark -


- (void)setAmount: (CDVInvokedUrlCommand*) command {
    [self.commandDelegate runInBackground:^{
        MTPPSCRA* magtek = [MTPPSCRA shareInstance];
        [magtek endSession:0];
        
        NSString *amount = nil;
        
        if (command.arguments.count > 0) {
            amount = [NSString stringWithFormat:@"%@", [command.arguments objectAtIndex:0]];
        }
        
        [self requestSetAmount:amount];
        
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

- (void)requestSetAmount: (NSString *)amount {
    MTPPSCRA *mtPPSCRA = [MTPPSCRA shareInstance];
    
    unsigned char status       = 0;
    
    [mtPPSCRA setAmount:(AMT_TYPE_CREDIT)
                 amount:amount
               opStatus:&status];
}

- (void)requestCard: (CDVInvokedUrlCommand*) command {
    [self.commandDelegate runInBackground:^{
        MTPPSCRA* magtek = [MTPPSCRA shareInstance];
        NSInteger returnCode = 0;
        
        returnCode = [magtek requestCard:0x20
                               messageID:0x01
                                    tone:0x01];
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsNSInteger:returnCode];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

- (void)requestSmartCardTransaction: (CDVInvokedUrlCommand*) command {
    [self.commandDelegate runInBackground:^{
        MTPPSCRA *magtek = [MTPPSCRA shareInstance];
        
        NSInteger returnCode = 0;
        
        NSString *deviceInformation = @"";
        
        returnCode = [magtek requestDeviceInformation:5
                                          information:&deviceInformation];
        
        NSString *amountString = nil;
        
        if (command.arguments.count > 0) {
            amountString = [command.arguments objectAtIndex:0];
        }
        
        
        self.deviceSerialNumber = deviceInformation;
        
        /* START Example conversion from NSString to Byte Array */
        //NSString *amountString  = @"1,000.50";
        NSLog(@"%@", amountString);
        amountString = [amountString stringByReplacingOccurrencesOfString:@","
                                                               withString:@""];
        
        NSString *amountStringFinal = [amountString stringByReplacingOccurrencesOfString:@"."
                                                                              withString:@""];
        
        const char *chars = [amountStringFinal UTF8String];
        
        unsigned char amountArrayExample[6] = {};
        
        unsigned long wholeByte;
        
        int i      = 0;
        int j      = 0;
        int length = [amountStringFinal length] / 2;
        
        char byteChars[6] = {'\0','\0','\0','\0','\0','\0'};
        
        while(i < length)
        {
            byteChars[0] = chars[i++];
            byteChars[1] = chars[i++];
            
            wholeByte = strtoul(byteChars, NULL, 16);
            
            amountArrayExample[length - j] = wholeByte;
            
            j++;
        }
        /* END Example conversion from NSString to Byte Array */
        
        unsigned char cardType             = 3;  // Card Type 3 will arm both the MSR reader and the ICC reader
        unsigned char confirmationWaitTime = 30;
        unsigned char PINWaitTime          = 30;
        unsigned char tone                 = 0;
        unsigned char option               = 0;
        unsigned char amount[]             = {0x00, 0x00, 0x00, 0x10, 0x00, 0x00};
        unsigned char transactionType      = 0x08;
        unsigned char cashBack[]           = {0x00, 0x00, 0x00, 0x00, 0x10, 0x00};
        unsigned char reservedBytes[28]    = {0};

        returnCode = [magtek requestSmartCard:cardType
                         confirmationWaitTime:confirmationWaitTime
                                  PINWaitTime:PINWaitTime
                                         tone:tone
                                       option:option
                                       amount:amountArrayExample
                              transactionType:transactionType
                                     cashBack:cashBack
                                reservedBytes:reservedBytes];
        
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            NSLog(@"Request Smart Card has been sent to the device.");
        });
    }];
}


- (void)requestConfirmAmount {
        MTPPSCRA *magtek = [MTPPSCRA shareInstance];
        
        NSInteger returnCode     = 0;
        unsigned char retCode    = 0;
        unsigned char keyPressed = 0;
        
        returnCode = [magtek requestResponse:30
                           selectMessageType:0
                                        mask:(5)
                                       tones:1
                                  keyPressed:&keyPressed
                                    opStatus:&retCode];
        
    
}

- (void)requestPINSelected
{
    MTPPSCRA *mtPPSCRA = [MTPPSCRA shareInstance];
    
    // if(self.isCardSwipeSelected == YES)
    // {
    //     self.isCardSwipeSelected = NO;
    // }
    // else
    // {
    //     [mtPPSCRA endSession:0];
    // }
    
    NSInteger returnCode = 0;
    
    returnCode = [mtPPSCRA requestPIN:30
                          messageType:0
                         PINLengthMin:4
                         PINLengthMax:6
                                tones:1
                              options:0];
    NSLog(@"requestPINSelected: %ld", (long) returnCode);
}

- (void)getLastTransactionInfo: (CDVInvokedUrlCommand*) command {
    [self.commandDelegate runInBackground:^{
        MTPPSCRA *magtek = [MTPPSCRA shareInstance];
        NSMutableDictionary* info = [[NSMutableDictionary alloc] init];
        
        @try {
            [info setObject:[magtek getLastName] forKey:@"lastName"];
            [info setObject:[magtek getFirstName] forKey:@"firstName"];
            [info setObject:[magtek getMiddleName] forKey:@"middleName"];
            [info setObject:[magtek getExpDate] forKey:@"expDate"];
            [info setObject:[magtek getCardType] forKey:@"cardType"];
            [info setObject:[magtek getCardLast4] forKey:@"cardLast4"];
            [info setObject:[magtek getCardServiceCode] forKey:@"cardServiceCode"];
            
        } @catch (NSException *e) {
            [info setObject:@"" forKey:@"lastName"];
            [info setObject:@"" forKey:@"firstName"];
            [info setObject:@"" forKey:@"middleName"];
            [info setObject:@"" forKey:@"expDate"];
            [info setObject:@"" forKey:@"cardType"];
            [info setObject:@"" forKey:@"cardLast4"];
            [info setObject:@"" forKey:@"cardServiceCode"];
            
        }
        
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:info];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

#pragma mark -
#pragma mark MTPPSCRA Delegate Methods
#pragma mark -

- (void)cardDataAvailable {
    //    NSLog(@"cardDataAvailable");
    MTPPSCRA *magtek = [MTPPSCRA shareInstance];
    
    [magtek requestMSR];
    [self sendEvent:@"Card" withData:@"cardDataAvailable"];
}

- (void)onError:(NSString *)errorCode {
    //    NSLog(@"onError");
    MTPPSCRA *magtek = [MTPPSCRA shareInstance];
    
    [magtek endSession:0];
    
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, 1 * NSEC_PER_SEC);
    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
        [self sendEvent:@"Error" withData:errorCode];
    });
}

- (void)onBINDataReceived:(NSString *)data {
    //    NSLog(@"onBINDataReceived");
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self sendEvent:@"BINDataReceived" withData:data];
    });
}

- (void)onDataArriveComplete:(NSString *)data {
    //    NSLog(@"onDataArriveComplete");
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self sendEvent:@"DataArriveComplete" withData:data];
    });
}

- (void)currentACKStatusReceived:(NSString *)ACKStatus {
    if (![ACKStatus isEqual:@"00"]){
        //        NSLog(@"currentACKStatusReceived");
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            [self sendEvent:@"ACKStatusReceived" withData:ACKStatus];
        });
    }
}

- (void)onATRRequestComplete:(NSString *)data {
    //    NSLog(@"onATRRequestComplete");
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self sendEvent:@"ATRRequestComplete" withData:data];
    });
}

- (void)onSendICCAPDUComplete:(NSString *)data {
    //    NSLog(@"onSendICCAPDUComplete");
    MTPPSCRA *magtek = [MTPPSCRA shareInstance];
    
    unsigned char iv[8] = {0};
    
    unsigned char dataOut[16] = {0};
    NSInteger dataOutLength   = 24;
    
    unsigned char R_APDU[16] = {0};
    size_t R_APDUlength      = 16;
    
    NSUInteger decryptedRAPDULen = 0;
    
    NSString *parsedRAPDUString = @"";
    
    [magtek hexToBytesWithString:data
                        outBytes:dataOut
                  outBytesLength:&dataOutLength];
    
    [MTCryptoLib Decrypt3CBC:m_sessionKey
                          IV:iv
                      dataIn:dataOut
                     dataLen:dataOutLength
                     dataout:R_APDU
                  dataOutLen:&R_APDUlength];
    
    if(R_APDUlength > 2)
    {
        decryptedRAPDULen = (R_APDU[1] << 8) + R_APDU[0];
    }
    
    NSString *RAPDUString = [magtek bytesToHexStringWithData:R_APDU
                                              withDataLength:R_APDUlength];
    
    NSMutableString *RAPDUMutableString = [[NSMutableString alloc] initWithString:[NSString stringWithFormat:@"RAPDU Decrypted Data - \n %@ \n", RAPDUString]];
    if([RAPDUString length] >= decryptedRAPDULen*2 + 4)
    {
        parsedRAPDUString = [RAPDUString substringWithRange:NSMakeRange(4, decryptedRAPDULen*2)];
    }
    NSLog(@"RAPDUMutableString: %@", RAPDUMutableString);
    NSLog(@"parsedRAPDUString: %@", parsedRAPDUString);
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self sendEvent:@"SendICCAPDUComplete" withData:RAPDUMutableString];
    });
}

- (void)onSetCAPublicKeyComplete:(NSString *)data {
    //    NSLog(@"onSetCAPublicKeyComplete");
    [[MTPPSCRA shareInstance] endSession:0];
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self sendEvent:@"SetCAPublicKeyComplete" withData:data];
    });
}

- (void)onPINRequestComplete:(PINDATA *)retData {
    //    NSLog(@"onPINRequestComplete");
    MTPPSCRA *magtek = [MTPPSCRA shareInstance];
    
    /*
     *
     *  NOTE: PIN data can be retrieved either from the PINDATA instance that is returned within this delegate
     *        or through the MTPPSCRA Library.
     *
     */
    
    // PIN data retrieved from the PINDATA instance returned within this delegate method
    NSMutableDictionary* pinData = [[NSMutableDictionary init] alloc];
    [pinData setObject:[retData KSN] forKey:@"KSN"];
    [pinData setObject:[retData EPB] forKey:@"EPB"];
    [pinData setObject:[retData statusCode] forKey:@"statusCode"];
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self sendEvent:@"PINRequestComplete" withData:pinData];
    });
    
    // With the UART connection the response from the DynaPro Mini is very quick, thus
    // sending a command immediately afterwards can cause interference with the DynaPro Mini.
    sleep(1.0);
    
    [magtek endSession:0];
}

- (void)onKeyRequestComplete:(unsigned char)keyPressed {
    //    NSLog(@"onKeyRequestComplete");
    MTPPSCRA *magtek = [MTPPSCRA shareInstance];
    
    switch(keyPressed)
    {
        case FuncKeyLeft:
        {
            dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
                [self sendEvent:@"KeyRequestComplete" withData:@"Key 1 Pressed"];
            });
            
//             [self requestSetAmount];
            
             [self requestConfirmAmount];
            
            self.isConfirmAmountSelected = YES;
            
            break;
        }
            
        case FuncKeyMiddle:
        {
            dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
                [self sendEvent:@"KeyRequestComplete" withData:@"Key 2 Pressed"];
            });
            
            // self.nextMessageID = 6;
            
            self.displayApproved = YES;
            
            [magtek setDisplayMessage:2
                            messageId:APPROVED_MSG];
            
            self.isConfirmAmountSelected = NO;
            
            break;
        }
            
        case FuncKeyRight:
        {
            dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
                [self sendEvent:@"KeyRequestComplete" withData:@"Key 3 Pressed"];
            });
            
            if(self.isConfirmAmountSelected == YES)
            {
                // the user selected NO
                [magtek endSession:0];
                
                self.isConfirmAmountSelected = NO;
            }
            else
            {
                [self requestPINSelected];
            }
            
            break;
        }
            
        case FuncKeyEnter:
        {
            dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
                [self sendEvent:@"KeyRequestComplete" withData:@"Enter Key Pressed"];
            });
        }
            
            break;
            
        default:
            
            [magtek endSession:0];
            
            break;
    }
}

- (void)onDisplayRequestComplete:(unsigned char)statusCode {
    //    NSLog(@"onDisplayRequestComplete");
    MTPPSCRA *magtek = [MTPPSCRA shareInstance];
    
    if(self.displayApproved == YES) {
        // sleep(0.5);
        
        [magtek setDisplayMessage:2
                        messageId:APPROVED_MSG];
        
        self.displayApproved = NO;
    }
    else {
        [magtek endSession:0];
    }
}

- (void)onBypassPINCommandComplete:(NSString *)data {
    //    NSLog(@"onBypassPINCommandComplete");
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self sendEvent:@"BypassPinCommandComplete" withData:data];
    });
}

- (void)onSendCommandTimeOutComplete:(NSString *)data {
    //    NSLog(@"onSendCommandTimeOutComplete");
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self sendEvent:@"SendCommandTimeOutComplete" withData:data];
    });
}

- (void)onRequestPowerUpResetICCComplete:(NSString *)data {
    //    NSLog(@"onRequestPowerUpResetICCComplete");
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self sendEvent:@"RequestPowerUpResetICCComplete" withData:data];
    });
}

- (void)onOperationStatusReceieved:(NSString *)operationStatus {
    //    NSLog(@"onOperationStatusReceieved");
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self sendEvent:@"OperationStatusReceived" withData:operationStatus];
    });
}

- (void)onCardRequestComplete:(unsigned char *)statusCode
                   andCarData:(CARD_DATA_INFO *)pCardData {
    
    //    NSLog(@"onCardRequestComplete with code %c", *statusCode);
    
    MTPPSCRA *magtek = [MTPPSCRA shareInstance];
    NSMutableDictionary* cardDataAsDictionary = [[NSMutableDictionary alloc] init];
    [cardDataAsDictionary setObject:[magtek getSDKVersion] forKey:@"SDKVersion"];
    [cardDataAsDictionary setObject:[magtek getEncodeType] forKey:@"EncodeType"];
    [cardDataAsDictionary setObject:[pCardData track1DecodeStatus] forKey:@"Track1DecodeStatus"];
    [cardDataAsDictionary setObject:[pCardData track2DecodeStatus] forKey:@"Track2DecodeStatus"];
    [cardDataAsDictionary setObject:[pCardData Track1] forKey:@"Track1Masked"];
    [cardDataAsDictionary setObject:[pCardData Track2] forKey:@"Track2Masked"];
    [cardDataAsDictionary setObject:[pCardData Track3] forKey:@"Track3Masked"];
    [cardDataAsDictionary setObject:[pCardData EncTrack1] forKey:@"Track1Encrypted"];
    [cardDataAsDictionary setObject:[pCardData EncTrack2] forKey:@"Track2Encrypted"];
    [cardDataAsDictionary setObject:[pCardData EncTrack3] forKey:@"Track3Encrypted"];
    [cardDataAsDictionary setObject:[pCardData maskedPAN] forKey:@"PAN"];
    [cardDataAsDictionary setObject:[pCardData EncMP] forKey:@"MagnePrint"];
    [cardDataAsDictionary setObject:[pCardData MPSTS] forKey:@"MagnePrintStatus"];
    [cardDataAsDictionary setObject:[pCardData KSN] forKey:@"KSN"];
    [cardDataAsDictionary setObject:[magtek getDeviceSerial] forKey:@"DeviceSerial"];
    [cardDataAsDictionary setObject:[pCardData lastName] forKey:@"LastName"];
    [cardDataAsDictionary setObject:[pCardData middleName] forKey:@"MiddleName"];
    [cardDataAsDictionary setObject:[pCardData firstName] forKey:@"FirstName"];
    [cardDataAsDictionary setObject:[pCardData cardLast4] forKey:@"CardLast4"];
    [cardDataAsDictionary setObject:[pCardData cardExpDate] forKey:@"CardExpDate"];
    [cardDataAsDictionary setObject:[pCardData cardServiceCode] forKey:@"CardServiceCode"];
    
    DUKPT* d = [[DUKPT alloc]initWithBDK:bdk KSN:[pCardData KSN]];
    
    [cardDataAsDictionary setObject:[d decrypt:[pCardData EncTrack1]] forKey:@"Track1Unmasked"];
    [cardDataAsDictionary setObject:[d decrypt:[pCardData EncTrack2]] forKey:@"Track2Unmasked"];
    [cardDataAsDictionary setObject:[d decrypt:[pCardData EncTrack3]] forKey:@"Track3Unmasked"];

    NSLog(@"%@", cardDataAsDictionary);
    
    if(*statusCode == 0)
    {
        [magtek endSession:0];
        
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            [self sendEvent:@"CardRequestComplete" withData:cardDataAsDictionary];
        });
    }
}

- (void)onRequestICCAPDUComplete:(NSString *)operationStatus
                  withCardstatus:(NSString *)cardStatus {
    //    NSLog(@"onRequestICCAPDUComplete");
    NSInteger returnCode = 0;
    
    NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
    [dict setObject:operationStatus forKey:@"OperationStatus"];
    [dict setObject:cardStatus forKey:@"CardStatus"];
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self sendEvent:@"RequestICCAPDUComplete" withData:dict];
    });
    
    returnCode = [[MTPPSCRA shareInstance] requestTransactionData];
}

- (void)onRequestSmartCardComplete:(unsigned char)statusCode
                          withData:(NSString *)data
{
    //    NSLog(@"onRequestSmartCardComplete");
    MTPPSCRA *magtek = [MTPPSCRA shareInstance];
    
    NSMutableDictionary *cardDataAsDictionary = [[NSMutableDictionary alloc] init];
    
    // If the Card Type is an Other Card
    if([[magtek getCardType] isEqualToString:@"OTHERCARD"]) {
        
    }
    // Else the Card Type is a Financial Card
    else if([[magtek getCardType] isEqualToString:@"FINANCIALCARD"]) {
        if([self checkIfDeviceIsSRED] == YES) {
            // TODO: This data will need to be parsed with a TLV Parser. The MSR Data is encrypted within the DFDF59 tag.
            NSLog(@"FINANCIALCARD need to decrypt with TLV Parser");
            dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
                [self sendEvent:@"RequestSmartCardComplete" withData:[magtek getSREDResponseData]];
            });
            
        } else if([self checkIfDeviceIsSRED] == NO) {
            // Card data retrieved through the MTPPSCRA Library
            NSLog(@"Card data retrieved through the MTPPSCRA Library");
            [cardDataAsDictionary setObject:[magtek getSDKVersion] forKey:@"SDKVersion"];
            [cardDataAsDictionary setObject:[magtek getEncodeType] forKey:@"EncodeType"];
            [cardDataAsDictionary setObject:[magtek getTrack1DecodeStatus] forKey:@"Track1DecodeStatus"];
            [cardDataAsDictionary setObject:[magtek getTrack2DecodeStatus] forKey:@"Track2DecodeStatus"];
            [cardDataAsDictionary setObject:[magtek getTrack1Masked] forKey:@"Track1Masked"];
            [cardDataAsDictionary setObject:[magtek getTrack2Masked] forKey:@"Track2Masked"];
            [cardDataAsDictionary setObject:[magtek getTrack3Masked] forKey:@"Track3Masked"];
            [cardDataAsDictionary setObject:[magtek getTrack1] forKey:@"Track1"];
            [cardDataAsDictionary setObject:[magtek getTrack2] forKey:@"Track2"];
            [cardDataAsDictionary setObject:[magtek getTrack3] forKey:@"Track3"];
            [cardDataAsDictionary setObject:[magtek getPAN] forKey:@"PAN"];
            [cardDataAsDictionary setObject:[magtek getMagnePrint] forKey:@"MagnePrint"];
            [cardDataAsDictionary setObject:[magtek getMagnePrintStatus] forKey:@"MagnePrintStatus"];
            [cardDataAsDictionary setObject:[magtek getKSN] forKey:@"KSN"];
            [cardDataAsDictionary setObject:[magtek getDeviceSerial] forKey:@"DeviceSerial"];
            [cardDataAsDictionary setObject:[magtek getLastName] forKey:@"LastName"];
            [cardDataAsDictionary setObject:[magtek getMiddleName] forKey:@"MiddleName"];
            [cardDataAsDictionary setObject:[magtek getFirstName] forKey:@"FirstName"];
            [cardDataAsDictionary setObject:[magtek getCardLast4] forKey:@"CardLast4"];
            [cardDataAsDictionary setObject:[magtek getExpDate] forKey:@"CardExpDate"];
            [cardDataAsDictionary setObject:[magtek getCardServiceCode] forKey:@"CardServiceCode"];
            
        }
    }
    // Else the Card Type is an AAMVA Card
    else if([[magtek getCardType] isEqualToString:@"AAMVACARD"])
    {
        NSLog(@"AAMVACARD");
    }
    // Else the Card Type was a Manual Entry
    else if([[magtek getCardType] isEqualToString:@"MANUALCARD"])
    {
        NSLog(@"MANUALCARD");
    }
    // Else the Card Type is an Unknown Card
    else if([[magtek getCardType] isEqualToString:@"UNKNOWNCARD"])
    {
        NSLog(@"UNKNOWNCARD");   
    }
    // Else the Card Type is an ICC Card
    else if([[magtek getCardType] isEqualToString:@"ICCCARD"])
    {
        // If the Smart Card used is a Chip & Signature card the the isSignatureRequired method will return YES.
        NSLog(@"ICCCARD");
        NSLog(@"Is Signature Required = %@\n", ([magtek isSignatureRequired] ? @"YES" : @"NO"));
        
        // Card data retrieved through the MTPPSCRA Library
        [cardDataAsDictionary setObject:[magtek getTrack2Equivalent] forKey:@"Track2Equivalent"];
        [cardDataAsDictionary setObject:[magtek getPAN] forKey:@"PAN"];
        [cardDataAsDictionary setObject:[magtek getKSN] forKey:@"KSN"];
        [cardDataAsDictionary setObject:[magtek getDeviceSerial] forKey:@"DeviceSerial"];
        [cardDataAsDictionary setObject:[magtek getLastName] forKey:@"LastName"];
        [cardDataAsDictionary setObject:[magtek getMiddleName] forKey:@"MiddleName"];
        [cardDataAsDictionary setObject:[magtek getFirstName] forKey:@"FirstName"];
        [cardDataAsDictionary setObject:[magtek getCardLast4] forKey:@"CardLast4"];
        [cardDataAsDictionary setObject:[magtek getExpDate] forKey:@"ExpDate"];
        [cardDataAsDictionary setObject:[magtek getCardServiceCode] forKey:@"CardServiceCode"];
    }
    // Else the Card Type is a Contactless ICC Card
    else if([[magtek getCardType] isEqualToString:@"CONTACTLESSICCCARD"])
    {
        NSLog(@"CONTACTLESSICCCARD");   
    }
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self sendEvent:@"RequestSmartCardComplete" withData:cardDataAsDictionary];
    });
    
    [magtek endSession:0];
}

- (void)onRequestSetEMVTagsComplete:(unsigned char)statusCode
                           withData:(NSString *)data
{
    NSLog(@"onRequestSetEMVTagsComplete");
    NSLog(@"%@", data);
    // MTPPSCRA *mtPPSCRA = [MTPPSCRA shareInstance];
    // MTTLV    *mtTLV    = [MTTLV sharedInstance];
    
    // NSInteger returnCode = 0;
    
    // NSString *errorMessage          = @"";
    // NSString *transactionDataString = [data substringWithRange:NSMakeRange(4, [data length] - 10 - 4)];
    // NSLog(@"%@", transactionDataString);
    // returnCode = [mtTLV parseTLVDataObject:transactionDataString
    //                               ErrorMsg:&errorMessage];
    
    // returnCode = [mtTLV printTLVList];
    
    // unsigned char cardStatus[1] = {0};
    // int cardStatusLen           = 1;
    
    // returnCode = [mtTLV getTagValue:0xDFDF1A
    //                        TagValue:cardStatus
    //                          TagLen:&cardStatusLen];
    
    // //      Get the Merchant Data
    // TagEntry tagEntryKSN;
    // tagEntryKSN.Tag = 0xF7;
    // tagEntryKSN.Len = 0;
    
    // //      Get the length
    // returnCode = [mtTLV getTagLen:tagEntryKSN.Tag
    //                        tagLen:&tagEntryKSN.Len];
    
    // //      Allocate memory
    // tagEntryKSN.Value = (unsigned char *)malloc(sizeof(unsigned char)*tagEntryKSN.Len);
    
    // NSInteger *tagLength = (NSInteger *)tagEntryKSN.Len;
    
    // NSMutableString *merchantDataString = [mtTLV returnTLVList];
    
    // if(tagLength == 0 || tagLength == nil)
    // {
    //     [mtPPSCRA endSession:0];
        
    //     dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
    //         NSLog(@"%@", merchantDataString);
    //     });
    // }
    // else
    // {
    //     //Get Value byte
    //     returnCode = [mtTLV getTLV:tagEntryKSN.Tag
    //                       TagEntry:&tagEntryKSN];
        
    //     char sErrorMsg[128] = {0};
        
    //     returnCode = [mtTLV parseSequence:tagEntryKSN.Value
    //                             TLVLength:tagEntryKSN.Len
    //                              ErrorMsg:sErrorMsg];
        
    //     returnCode = [mtTLV printTLVList];
        
    //     free(tagEntryKSN.Value);
        
    //     returnCode = [mtPPSCRA endSession:0];
        
    //     dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
    //         NSLog(@"%@", merchantDataString);
    //         [self sendEvent:@"RequestSetEMVTagsComplete" withData:merchantDataString];
    //     });
    // }
}

- (void)onSendAcquirerResponseComplete:(unsigned char)statusCode
                              withData:(NSString *)data
{
    NSLog(@"onSendAcquirerResponseComplete");
    NSLog(@"%@", data);

//     MTPPSCRA *mtPPSCRA = [MTPPSCRA shareInstance];
//     MTTLV    *mtTLV    = [MTTLV sharedInstance];
    
//     NSInteger returnCode = 0;
    
// #if 1
    
//     NSString *nssARQC = [data substringWithRange:NSMakeRange(4, [data length] - 10 - 4)];
    
//     NSString *errorMessage = @"";
    
//     returnCode = [mtTLV parseTLVDataObject:nssARQC
//                                   ErrorMsg:&errorMessage];
    
//     returnCode = [mtTLV printTLVList];
    
//     //    NSMutableString *TLVOutputString = [mtTLV returnTLVList];
//     //
//     //    NSLog(@"%@", TLVOutputString);
//     //
//     //    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
//     //
//     //        [self performSelectorOnMainThread:@selector(updateDataOutputTextView:)
//     //                               withObject:TLVOutputString
//     //                            waitUntilDone:YES];
//     //
//     //    });
    
//     TagEntry tagEntryKSN;
    
//     tagEntryKSN.Tag   = 0xDFDF54;
//     tagEntryKSN.Len   = 0;
//     tagEntryKSN.Value = (unsigned char *)malloc(sizeof(unsigned char)*21);
    
//     returnCode = [mtTLV getTagLen:tagEntryKSN.Tag
//                            tagLen:&tagEntryKSN.Len];
    
//     returnCode = [mtTLV getTLV:tagEntryKSN.Tag
//                       TagEntry:&tagEntryKSN];
    
//     const unsigned char BDK[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
//     unsigned char ksn [10]    = {0};
//     const unsigned char iv[]  = {0, 0, 0, 0, 0, 0, 0, 0};
    
//     NSString *asciiString = [mtPPSCRA convertHexToASCIIWithString:[self.deviceSerialNumber substringWithRange:NSMakeRange(4, 32)]];
    
    
//     int length                          = [asciiString length] / 2 + 1;
//     unsigned char deviceSerialNumber[8] = {0};
    
//     [mtPPSCRA hexToBytesWithString:asciiString
//                           outBytes:deviceSerialNumber
//                     outBytesLength:&length];
    
//     const char *pcARQC = [nssARQC cStringUsingEncoding:NSASCIIStringEncoding];
    
//     int           acqMsgLen             = strlen(pcARQC);
//     int           commandToDeviceLength = 512;
//     unsigned char commandToDevice[512]  = {0};
//     unsigned char pubAcqMsg[acqMsgLen / 2];
    
//     returnCode = [mtTLV pack:pcARQC
//                       hexout:(char *)pubAcqMsg
//                    dataInLen:acqMsgLen];
    
//     memcpy(ksn, tagEntryKSN.Value, 10);
    
//     unsigned char pubAcquirerApprovedMsg[] = {0x70, 0x04, 0x8A, 0x02, 0x30, 0x30};
    
//     //    unsigned char pubAcquirerDeclinedMsg[] = {0x70, 0x04, 0x8A, 0x02, 0x30, 0x31};
    
//     returnCode = [MTCryptoLib ConstructAcqMsg:BDK
//                                     keyLength:sizeof(BDK)
//                                           ksn:ksn
//                                            IV:iv
//                                      deviceSN:deviceSerialNumber
//                                        acqMsg:pubAcquirerApprovedMsg
//                                     acqMsgLen:sizeof(pubAcquirerApprovedMsg)
//                                    cmd2device:commandToDevice
//                                 cmd2DeviceLen:&commandToDeviceLength];
    
//     returnCode = [mtPPSCRA sendAcquirerResponse:commandToDevice
//                                  responseLength:commandToDeviceLength];
//     NSLog(@"onSendAcquirerResponseCompleteWithData %ld", (long)returnCode);
    
// #endif
}

- (void)onRequestUserDataEntryComplete:(unsigned char *)statusCode
                              withData:(USER_ENTRY_DATA *)data
{
    NSLog(@"onRequestUserDataEntryComplete");
    MTPPSCRA *magtek = [MTPPSCRA shareInstance];
    
    NSInteger returnCode = 0;
    
    NSMutableDictionary *userDataDictionary = [[NSMutableDictionary alloc] init];
    [userDataDictionary setObject:data.MSRKSN forKey:@"MSR"];
    [userDataDictionary setObject:data.EDB forKey:@"EDB"];
    
    returnCode = [magtek endSession:0];
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self sendEvent:@"RequestUserDataEntryComplete" withData:userDataDictionary];
    });
}

#pragma mark -
#pragma mark Util
#pragma mark -

- (NSMutableDictionary*)peripheralToDictionary:(CBPeripheral *)peripheral {
    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
    [dict setObject:[NSString stringWithFormat:@"%@", [peripheral identifier]] forKey:@"identifier"];
    [dict setObject:[NSString stringWithFormat:@"%@" , [peripheral name]] forKey:@"name"];
    // [dict setObject:[NSString stringWithFormat:@"%ld", [peripheral state]] forKey:@"state"];
    switch ([peripheral state]) {
        case CBPeripheralStateDisconnected:
            [dict setObject:@"disconnected" forKey:@"state"];
            break;
        case CBPeripheralStateConnecting:
            [dict setObject:@"connecting" forKey:@"state"];
            break;
        case CBPeripheralStateConnected:
            [dict setObject:@"connected" forKey:@"state"];
            break;
        case CBPeripheralStateDisconnecting:
            [dict setObject:@"disconnecting" forKey:@"state"];
            break;
        default:
            [dict setObject:@"disconnected" forKey:@"state"];
            
    }
    return dict;
}

- (void)sendEvent:(NSString *)dataType withData:(id)data {
    NSLog(@"%@", data);
    if (dataCallbackId != nil) {
        NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
        [dict setObject:dataType forKey:@"dataType"];
        if (data != nil) {
            [dict setObject:data forKey:@"data"];
        }
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:dict];
        [result setKeepCallbackAsBool:YES];
        [self.commandDelegate sendPluginResult:result callbackId:dataCallbackId];
    }
}

@end
