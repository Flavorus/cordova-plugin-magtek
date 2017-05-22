//
//  MTPPSCRA.h
//  MTPPSCRA
//
//  Created by Kevin E. Rafferty II on 03/01/2013
//  Copyright (c) 2013 magtek. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <ExternalAccessory/ExternalAccessory.h>

#import "CommonDataType.h"

@class Utility;
@class BLECommunication;

typedef enum
{
    
    ST_IDLE,
    ST_ERROR,
    ST_COMMAND,
    ST_UNKNOWN,
    ST_WAIT_FOR_R_APDU,
    ST_WAIT_FOR_USER_INPUT,
    ST_REQUEST_ATR_DATA_SET,
    ST_WAIT_FOR_POWER_UP_ICC,
    ST_WAIT_FOR_ATR_RESPONSE,
    ST_WAIT_FOR_CMD_RESPONSE,
    ST_WAIT_FOR_PIN_RESPONSE,
    ST_WAIT_FOR_ATR_RESPONSE_2,
    ST_WAIT_FOR_EMV_TAG_RESPONSE,
    ST_WAIT_FOR_GENERIC_RESPONSE,
    ST_WAIT_FOR_EMV_ARQC_RESPONSE,
    ST_WAIT_FOR_CMD_DATA_RESPONSE,
    ST_WAIT_FOR_KEY_ENTRY_RESPONSE,
    ST_WAIT_FOR_CARD_SWIPE_RESPONSE,
    ST_WAIT_FOR_SPECIAL_CMD_RESPONSE,
    ST_WAIT_FOR_GET_EMV_TAG_RESPONSE,
    ST_WAIT_FOR_USER_DATA_ENTRY_RESPONSE,
    ST_WAIT_FOR_DISPLAY_COMPLETE_RESPONSE,
    ST_WAIT_FOR_EMV_EMV_TNX_DATA_RESPONSE,
    ST_WAIT_FOR_DEV_STATE_STATUS_RESPONSE,
    ST_WAIT_FOR_EMV_ICC_CARD_STATUS_RESPONSE,
    
} StateMachineType;

enum MTPPSCRADeviceType
{
    
    MAGTEKDYNAPROMINIBLE,
    MAGTEKDYNAPROMINIUART
    
};

#pragma mark -
#pragma mark MTPPSCRADelegate Methods
#pragma mark -

@protocol MTPPSCRADelegate <NSObject>

@optional

/*
 METHOD         - cardDataAvailable
 
 PARAMETERS     - N/A
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when the Card Data after a Card Swipe is ready
 */
- (void)cardDataAvailable;

/*
 METHOD         - onError:(NSString *)errorCode
 
 PARAMETERS     - errorCode: of type NSString - The error status returned
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method if there is a status error returned from the device
 */
- (void)onError:(NSString *)errorCode;

/*
 METHOD         - onBINDataReceived
 
 PARAMETERS     - N/A
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when the BIN data has been received
 */
- (void)onBINDataReceived:(NSString *)data;

/*
 METHOD         - onDataArriveComplete:(NSString *)data
 
 PARAMETERS     - data: of type NSString - Data returned from sendCommandToDevice:(NSString *)command
 
 RETURN         - N/A
 
 DESCRIPTION    - The library raises this event when a response comes back from the DynaPro Mini for a previous sendCommandToDevice: call.
 */
- (void)onDataArriveComplete:(NSString *)data;

/*
 METHOD         - onATRRequestComplete:(NSString *)data
 
 PARAMETERS     - data: of type NSString - Data returned from requestATRData
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when a response comes back from the DynaPro Mini for a previous requestATR: call.
 */
- (void)onATRRequestComplete:(NSString *)data;

/*
 METHOD         - onSendICCAPDUComplete:(NSString *)data
 
 PARAMETERS     - data: of type NSString - Data returned from sendICCAPDUWithCommand:
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when a response comes back from the DynaPro Mini for a previous sendICCAPDUWithCommand: call.
 */
- (void)onSendICCAPDUComplete:(NSString *)data;

/*
 METHOD         - onSetCAPublicKeyComplete:(NSString *)data
 
 PARAMETERS     - data: of type NSString - Data returned from setCAPublicKey
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when a response comes back from the DynaPro Mini for a previous setCAPublicKeyWithOperation call.
 */
- (void)onSetCAPublicKeyComplete:(NSString *)data;

/*
 METHOD         - onPINRequestComplete:(PINDATA *)retData
 
 PARAMETERS     - retData: of type PINDATA - A pointer to the PIN_DATA structure containing the PIN data returned from the DynaPro Mini
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when a response comes back from the DynaPro Mini for a previous requestPIN call.
 */
- (void)onPINRequestComplete:(PINDATA *)returnData;

/*
 METHOD         - onKeyRequestComplete:(unsigned char)keyPressed
 
 PARAMETERS     - keyPressed: of type unsigned char - The key that the user pressed on the DynaPro Mini
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when a response comes back from the DynaPro Mini for a previous requestResponse call.
 */
- (void)onKeyRequestComplete:(unsigned char)keyPressed;

/*
 METHOD         - currentACKStatusReceived:(NSString *)ACKStatus
 
 PARAMETERS     - errorCode: of type NSString - The error status returned
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method after an ACK has been received from the device
 */
- (void)currentACKStatusReceived:(NSString *)ACKStatus;

/*
 METHOD         - onDisplayRequestComplete:(unsigned char)statusCode
 
 PARAMETERS     - statusCode: of type unsigned char - The status returned
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when a response comes back from the DynaPro Mini for a previous displayMessage call.
 */
- (void)onDisplayRequestComplete:(unsigned char)statusCode;

/*
 METHOD         - onBypassPINCommandComplete:(NSString *)data
 
 PARAMETERS     - data: of type NSString - Data returned from requestBypassPINCommand
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when a response comes back from the DynaPro Mini for a previous requestBypassPINCommand call.
 */
- (void)onBypassPINCommandComplete:(NSString *)data;

/*
 METHOD         - sendCommandTimeOutEventHandler:(NSString *)data
 
 PARAMETERS     - data: of type NSString - Data returned from fireCmdTimeOutHandler
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when a Time Out has been reached within sendCommandToDevice:
 */
- (void)onSendCommandTimeOutComplete:(NSString *)data;

/*
 METHOD         - onRequestDeviceConfigurationComplete:(NSString *)data
 
 PARAMETERS     - data: of type NSString - Data returned from requestDeviceConfigurationForInformation:
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when a response comes back from the DynaPro Mini for a previous requestDeviceConfigurationForInformation: call
 */
- (void)onRequestDeviceConfigurationComplete:(NSString *)data;

/*
 METHOD         - onRequestPowerUpResetICCComplete:(NSString *)data
 
 PARAMETERS     - data: of type NSString - Data returned from requestPowerUpResetICCWithWaitTime:
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when a response comes back from the DynaPro Mini for a previous requestPowerUpResetICCWithWaitTime: call.
 */
- (void)onRequestPowerUpResetICCComplete:(NSString *)data;

/*
 METHOD         - onOperationStatusReceieved:(NSString *)operationStatus
 
 PARAMETERS     - errorCode: of type NSString - The error status returned
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method if there is a status error returned from the device
 */
- (void)onOperationStatusReceieved:(NSString *)operationStatus;

/*
 METHOD         - onRequestChallengeAndSessionKeyRequestComplete:(NSString *)data
 
 PARAMETERS     - data: of type NSString - Data returned from requestChallengeAndSessionKeyForInformation:
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when a response comes back from the DynaPro Mini for a previous requestChallengeAndSessionKeyForInformation: call.
 */
- (void)onRequestChallengeAndSessionKeyRequestComplete:(NSString *)data;

/*
 METHOD         - onCardRequestComplete:(unsigned char *)statusCode
 andCarData:(CARD_DATA_INFO *)pCardData
 
 PARAMETERS     - statusCode: of type unsigned char  - The status returned
 pCardData:  of type CARD_DATA_INFO - A pointer to the CARD_DATA structure containing the card data returned from the DynaPro Mini
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when a response comes back from the DynaPro Mini for a previous requestCard: call.
 */
- (void)onCardRequestComplete:(unsigned char *)statusCode
                   andCarData:(CARD_DATA_INFO *)pCardData;

/*
 METHOD         - onRequestICCAPDUComplete:(NSString *)operationStatus
 withCardstatus:(NSString *)cardStatus
 
 PARAMETERS     - operationStatus: of type NSString - Operation status returned from requestICCAPDUForInformation:
 cardStatus:      of type NSString - Card Status returned from requestICCAPDUForInformation:
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when a response comes back from the DynaPro Mini for a previous requestICCAPDUForInformation: call
 */
- (void)onRequestICCAPDUComplete:(NSString *)operationStatus
                  withCardstatus:(NSString *)cardStatus;

/*
 METHOD         - onRequestSmartCardComplete:(unsigned char)statusCode
 withData:(NSString *)data
 
 PARAMETERS     - statusCode: of type unsigned char - Status returned from sendBigBlockData:
 data:       of type NSString      - Data   returned from sendBigBlockData:
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when a response comes back from the DynaPro Mini for a previous sendBigBlockData: call
 */
- (void)onRequestSmartCardComplete:(unsigned char)statusCode
                          withData:(NSString *)data;

/*
 METHOD         - onRequestSetEMVTagsComplete:(unsigned char)statusCode
 withData:(NSString *)data
 
 PARAMETERS     - statusCode: of type unsigned char - Status returned from requestSetEMVTagsWithTagType:
 data:       of type NSString      - Data   returned from requestSetEMVTagsWithTagType:
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when a response comes back from the DynaPro Mini for a previous requestSetEMVTagsWithTagType: call
 */
- (void)onRequestSetEMVTagsComplete:(unsigned char)statusCode
                           withData:(NSString *)data;

/*
 METHOD         - onSendAcquirerResponseComplete:(unsigned char)statusCode
 withData:(NSString *)data
 
 PARAMETERS     - statusCode:      of type unsigned char  - Status returned from sendAcquirerResponseWithResponse:
 AcqResponseData: of type NSString       - Data   returned from sendAcquirerResponseWithResponse:
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when a response comes back from the DynaPro Mini for a previous sendAcquirerResponseWithResponse: call
 */
- (void)onSendAcquirerResponseComplete:(unsigned char)statusCode
                              withData:(NSString *)data;

/*
 METHOD         - onRequestUserDataEntryComplete:(unsigned char *)statusCode
 withData:(USER_ENTRY_DATA *)data
 
 PARAMETERS     - statusCode: of type unsigned char   - Status returned from requestUserDataEntryWithwaitTime:
 data:       of type USER_ENTRY_DATA - Pointer to USER_ENTRY_DATA structure to hold user data returned from the DynaPro Mini
 
 RETURN         - N/A
 
 DESCRIPTION    - The library calls this delegate method when a response comes back from the DynaPro Mini for a previous requestUserDataEntryWithwaitTime:
 */
- (void)onRequestUserDataEntryComplete:(unsigned char *)statusCode
                              withData:(USER_ENTRY_DATA *)data;

- (void)deviceIsConnected;
- (void)deviceIsDisconnected;

@end

@interface MTPPSCRA : NSObject
{
    
@protected
    
    BOOL isDeviceOpened;
    BOOL isDeviceConnected;
    
    NSMutableString *deviceUUIDString;
}

#pragma mark -
#pragma mark MTPPSCRADelegate Property
#pragma mark -

@property(nonatomic, strong) id<MTPPSCRADelegate>delegate2;

#pragma mark -
#pragma mark MTPPSCRA Singleton Method
#pragma mark -

+ (MTPPSCRA *)shareInstance;

#pragma mark -
#pragma mark State Machine Methods
#pragma mark -

/*
 METHOD         - getState
 
 PARAMETERS     - N/A
 
 RETURN         - This method returns a StateMachineType which is a Type Defined ENUM
 
 DESCRIPTION    - This method simply returns the current state of the machine, i.e., ST_WAIT_FOR_CMD_RESPONSE.
 */
- (StateMachineType)getState;

/*
 METHOD         - setState:(StateMachineType)state
 
 PARAMETERS     - state: of type StateMachineType
 
 RETURN         - N/A
 
 DESCRIPTION    - This method takes aa a parameter StateMachineType and sets the _currentState iVar.
 */
- (void)setState:(StateMachineType)state;

#pragma mark -
#pragma mark MTPPSCRA Methods
#pragma mark -

/*
 METHOD         - requestMSR
 
 PARAMETERS     - N/A
 
 RETURN         - N/A
 
 DESCRIPTION    - This method retrieves the available MSR Data
 */
- (void)requestMSR;

/*
 METHOD         - getBINData
 
 PARAMETERS     - N/A
 
 RETURN         - N/A
 
 DESCRIPTION    - This method retrieves the available BIN data
 */
- (NSInteger)getBINData;

/*
 METHOD         - requestATR
 
 PARAMETERS     - N/A
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs the ATR command string to send to the device.
 */
- (NSInteger)requestATR;

/*
 METHOD         - deviceReset
 
 PARAMETERS     - N/A
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This function simply sends the reset command to the device.
 */
- (NSInteger)deviceReset;

/*
 METHOD         - setMTPPSCRALibrary
 
 PARAMETERS     - N/A
 
 RETURN         - N/A
 
 DESCRIPTION    - This function initializes the MTPPSCRA Library
 */
- (void)setMTPPSCRALibrary;

/*
 METHOD         - resetAllBonds
 
 PARAMETERS     - N/A
 
 RETURN         - N/A
 
 DESCRIPTION    - This function erases all the BLE module’s bonds. It will have to be re-paired with any BLE host it wants to communicate with.
                  Remove the device from all paired hosts prior to trying to re-pair the device.  If any previously paired hosts are still in
                  range of the device after issuing this command they may still try to connect with the device thus causing the device to stop
                  advertising which will make it unable to re-pair until the device is removed from that host. The secure codes are required to
                  make sure a user does not accidentally send this command. This command will automatically reset the BLE module 2 seconds after it completes.
 */
- (NSInteger)resetAllBonds;

/*
 METHOD         - cancelOperation
 
 PARAMETERS     - N/A
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This function sends the cancel command to the device to cancel the current operation.
 */
- (NSInteger)cancelOperation;

/*
 METHOD         - getCommandStatus
 
 PARAMETERS     - N/A
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method creates a separate synchronous thread that loops until a response status has been returned.
                  If no response status has been returned the method will time out.
 */
- (NSInteger)requestCommandStatus;

/*
 METHOD         - stopScanningForPeripherals
 
 PARAMETERS     - N/A
 
 RETURN         - N/A
 
 DESCRIPTION    - This method calls the Discovery Service stopScanning method to stop scanning for surrounding Peripherals
 */
- (void)stopScanningForPeripherals;

/*
 METHOD         - startScanningForPeripherals
 
 PARAMETERS     - N/A
 
 RETURN         - N/A
 
 DESCRIPTION    - This method calls the Discovery Service startScanningForUUIDString method to start scanning for surrounding Peripherals
 */
- (void)startScanningForPeripherals;

/*
 METHOD         - requestTransactionData
 
 PARAMETERS     - N/A
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method sends the "01AB" command to the device for the Transaction Data.
 */
- (NSInteger)requestTransactionData;

/*
 METHOD         - requestBypassPINCommand
 
 PARAMETERS     - N/A
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs the Bypass PIN command string to send to the device.
 */
- (NSInteger)requestBypassPINCommand;

/*
 METHOD         - setPAN:(NSString *)AccountNumber
 
 PARAMETERS     - AccountNumber: of type NSString - The PAN data (8-19 ASCII digits)
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This function sends PAN data to the DynaPro Mini.
                  However, this method checks if the PAN length is too long and/or if the PAN length is NULL.
 */
- (NSInteger)setPAN:(NSString *)accountNumber;

/*
 METHOD         - endSession:(unsigned char)displayMessageID
 
 PARAMETERS     - displayMessageID: of type unsigned char - unsigned char value between 0 – 4 indicating the message to display on the DynaPro Mini screen.
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This function clears all existing session data including PIN, PAN, and amount. The device returns to the idle state and sets the display to the specified Welcome screen.
 Use of displayMsg IDs 1-4 require that the associated bitmaps have been previously loaded during configuration; otherwise, use 0 for displayMsg and the DynaPro Mini will display
 its default “Welcome” screen (shown below).
 */
- (NSInteger)endSession:(unsigned char)displayMessageID;

/*
 METHOD         - setCommandTimeOut:(NSTimeInterval)timeoutInMilSec
 
 PARAMETERS     - timeoutInMilSec: of type NSTimeInterval - This is measured in miliseconds
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method simply sets the send command timeout interval.
 */
- (NSInteger)setCommandTimeOut:(NSTimeInterval)interval;

/*
 METHOD         - sendSpecialCommand:(NSString *)command
 
 PARAMETERS     - command: of type NSString - A pointer that contains the returned information from the device
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This function sends a custom special command to the device.
 */
- (NSInteger)sendSpecialCommand:(NSString *)command;

/*
 ** DEPRECATED **
 
 METHOD         - sendSpecialCommandWithCommand:(NSString *)command
 
 PARAMETERS     - command: of type NSString - A pointer that contains the returned information from the device
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This function sends a custom special command to the device.
 */
- (NSInteger)sendSpecialCommandWithCommand:(NSString *)command __deprecated;

/*
 METHOD         - requestICCAPDU:(NSString **)information
 
 PARAMETERS     - information: of type NSString - A pointer that contains the returned information from the device
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs a command string to send to the requestSpecialCommand method. It returns a NSString with the requested ICC APDU Information.
 */
- (NSInteger)requestICCAPDU:(NSString **)information;

/*
 ** DEPRECATED **
 
 METHOD         - requestICCAPDUForInformation:(NSString **)information
 
 PARAMETERS     - information: of type NSString - A pointer that contains the returned information from the device
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs a command string to send to the requestSpecialCommand method. It returns a NSString with the requested ICC APDU Information.
 */
- (NSInteger)requestICCAPDUForInformation:(NSString **)information __deprecated;

/*
 METHOD         - requestPowerDownICC:(unsigned char)waitTime
 
 PARAMETERS     - waitTime:  of type BYTE - The desired wait time
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method takes as a parameter waitTime and constructs a command string to send to the device.
 */

- (NSInteger)requestPowerDownICC:(unsigned char)waitTime;

/*
 ** DEPRECATED **
 
 METHOD         - requestPowerDownICCWithWaitTime:(unsigned char)waitTime
 
 PARAMETERS     - waitTime:  of type BYTE - The desired wait time
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method takes as a parameter waitTime and constructs a command string to send to the device.
 */

- (NSInteger)requestPowerDownICCWithWaitTime:(unsigned char)waitTime __deprecated;

/*
 METHOD         - requestDeviceConfiguration:(NSString **)information
 
 PARAMETERS     - information: of type NSString - A pointer that contains the returned information from the device
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This constructs a command string to send to the requestSpecialCommand method. It returns a NSString with the requested Device Configuration information.
 */
- (NSInteger)requestDeviceConfiguration:(NSString **)information;

/*
 ** DEPRECATED **
 
 METHOD         - requestDeviceConfigurationForInformation:(NSString **)information
 
 PARAMETERS     - information: of type NSString - A pointer that contains the returned information from the device
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This constructs a command string to send to the requestSpecialCommand method. It returns a NSString with the requested Device Configuration information.
 */
- (NSInteger)requestDeviceConfigurationForInformation:(NSString **)information __deprecated;

/*
 METHOD         - requestChallengeAndSessionKey:(NSString **)information
 
 PARAMETERS     - information: of type NSString - A pointer that contains the returned information from the device
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs a command string to send to the device. It returns a NSString with the requested feature report information.
 */
- (NSInteger)requestChallengeAndSessionKey:(NSString **)information;

/*
 ** DEPRECATED **
 
 METHOD         - requestChallengeAndSessionKeyForInformation:(NSString **)information
 
 PARAMETERS     - information: of type NSString - A pointer that contains the returned information from the device
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs a command string to send to the device. It returns a NSString with the requested feature report information.
 */
- (NSInteger)requestChallengeAndSessionKeyForInformation:(NSString **)information __deprecated;

/*
 METHOD         - confirmAmount:(unsigned char)waitTime
 withTone:(unsigned char)tone
 
 PARAMETERS     - waitTime: of type unsigned char - The wait time, in seconds, the DynaPro Mini will wait for the user to respond to the confirm amount selection.
 tone:     of type unsigned char - The tone that will be used to prompt the user to interact with the DynaPro Mini device.
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method sends a command to the device to prompt the user to confirm the amount.
 */

- (NSInteger)confirmAmount:(unsigned char)waitTime
                  withTone:(unsigned char)tone;

/*
 METHOD         - setDisplayMessage:(unsigned char)timeOut
 messageId:(unsigned char)messageID
 
 PARAMETERS     - timeOut: of type unsigned char - Time in seconds the DynaPro Mini will wait to display the message.
 msgID:   of type unsigned char - unsigned char value indicating the message to display. User can select from the following predefined messages:
 DisplayMsgBlank, DisplayMsgApproved, DisplayMsgDeclined, DisplayMsgCancelled, DisplayMsgThankYou, DisplayMsgPINInvalid,
 DisplayMsgProcessing, DisplayMsgPleaseWait, DisplayMsgHandsOff
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method sends a command to the device to display a predefined message on its LCD for the desired period of time.
 */
- (NSInteger)setDisplayMessage:(unsigned char)timeOut
                     messageId:(unsigned char)messageID;

/*
 METHOD         - sendICCAPDU:(unsigned char *)command
 withCommandLength:(NSInteger)commandLength
 
 PARAMETERS     - command:       of type unsigned char - The command to passed in
 commandLength: of type NSInteger     - The length of the command to be passed in
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs the ICC APDU report to send to the device.
 */
- (NSInteger)sendICCAPDU:(unsigned char *)command
           commandLength:(NSInteger)commandLength;

/*
 METHOD         - setBINData:(unsigned char *)tlvDataBlock
 tlvDataBlockLength:(int)tlvDataBlockLength
 
 PARAMETERS     - tlvDataBlock:       of type unsigned char * - The command to passed in
                  tlvDataBlockLength: of type int             - The length of the command to be passed in
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs the Set BIN Data report to send to the device.
 */
- (NSInteger)setBINData:(unsigned char *)tlvDataBlock
     tlvDataBlockLength:(int)tlvDataBlockLength;

/*
 ** DEPRECATED **
 
 METHOD         - sendICCAPDUWithCommand:(unsigned char *)command
 withCommandLength:(NSInteger)commandLength
 
 PARAMETERS     - command:       of type unsigned char - The command to passed in
 commandLength: of type NSInteger     - The length of the command to be passed in
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs the ICC APDU report to send to the device.
 */
- (NSInteger)sendICCAPDUWithCommand:(unsigned char *)command
                  withCommandLength:(NSInteger)commandLength __deprecated;

/*
 METHOD         - requestSpecialCommand:(NSString *)command
 forResponse:(NSString **)response
 
 PARAMETERS     - command:  of type NSString - The command to be passed in
 response: of type NSString - A pointer that conatains the returned information from the device
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method takes as parameters command and response and constructs a command string to send to the Send Command method.
 */
- (NSInteger)requestSpecialCommand:(NSString *)command
                          response:(NSString **)response;

/*
 ** DEPRECATED **
 
 METHOD         - requestSpecialCommandWithCommand:(NSString *)command
 forResponse:(NSString **)response
 
 PARAMETERS     - command:  of type NSString - The command to be passed in
 response: of type NSString - A pointer that conatains the returned information from the device
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method takes as parameters command and response and constructs a command string to send to the Send Command method.
 */
- (NSInteger)requestSpecialCommandWithCommand:(NSString *)command
                                  forResponse:(NSString **)response __deprecated;

/*
 METHOD         - sendEMVTagResponse:(unsigned char *)response
 withResponseLength:(int)responseLength
 
 PARAMETERS     - response:       of type unsigned char - A pointer containing the EMV Tag Response data
 responseLength: of type int           - An int    containing the EMV Tag Response data length
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method takes as parameters response and responseLength and constructs the command to send to the sendBigBlockData method
 */
- (NSInteger)sendEMVTagResponse:(unsigned char *)response
                 responseLength:(int)responseLength;

/*
 ** DEPRECATED **
 
 METHOD         - sendEMVTagResponseWithResponse:(unsigned char *)response
 withResponseLength:(int)responseLength
 
 PARAMETERS     - response:    of type unsigned char - A pointer containing the EMV Tag Response data
 blockLength: of type int           - An int    containing the EMV Tag Response data length
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method takes as parameters response and responseLength and constructs the command to send to the sendBigBlockData method
 */
- (NSInteger)sendEMVTagResponseWithResponse:(unsigned char *)response
                         withResponseLength:(int)responseLength __deprecated;

/*
 METHOD         - sendAcquirerResponse:(unsigned char *)response
 withResponseLength:(int)responseLength
 
 PARAMETERS     - response:       of type unsigned char - A pointer containing the Acquirer Response data
 responseLength: of type int           - An int    containing the Acquirer Response data length
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method takes as parametera response and responseLength and constructs the command to send to the sendBigBlockData method
 */
- (NSInteger)sendAcquirerResponse:(unsigned char *)response
                   responseLength:(int)responseLength;

/*
 ** DEPRECATED **
 
 METHOD         - sendAcquirerResponseWithResponse:(unsigned char *)response
 withResponseLength:(int)responseLength
 
 PARAMETERS     - response:    of type unsigned char - A pointer containing the Acquirer Response data
 blockLength: of type int           - An int    containing the Acquirer Response data length
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method takes as parametera response and responseLength and constructs the command to send to the sendBigBlockData method
 */
- (NSInteger)sendAcquirerResponseWithResponse:(unsigned char *)response
                           withResponseLength:(int)responseLength __deprecated;

/*
 METHOD         - requestDeviceInformation:(unsigned chat)mode
 forInformation:(NSString **)information
 
 PARAMETERS     - mode:        of type unsigned char - The mode to be passed in: 0 – Product_ID
 1 – Maximum Application Message Size
 2 – Capability String
 3 – Manufacturer
 4 – Product Name
 5 – Serial Number
 6 – Firmware Number
 7 – Build Info
 8 – MAC address for ethernet versions only
 
 information: of type NSString      - A pointer that conatains the returned information from the device
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method takes as parameters mode and information and constructs a command string to send to the requestSpecialCommand method.
 */
- (NSInteger)requestDeviceInformation:(unsigned char)mode
                          information:(NSString **)information;

/*
 ** DEPRECATED **
 
 METHOD         - requestDeviceInformationWithMode:(unsigned chat)mode
 forInformation:(NSString **)information
 
 PARAMETERS     - mode:        of type unsigned char - The mode to be passed in: 0 – Product_ID
 1 – Maximum Application Message Size
 2 – Capability String
 3 – Manufacturer
 4 – Product Name
 5 – Serial Number
 6 – Firmware Number
 7 – Build Info
 8 – MAC address for ethernet versions only
 
 information: of type NSString      - A pointer that conatains the returned information from the device
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method takes as parameters mode and information and constructs a command string to send to the requestSpecialCommand method.
 */
- (NSInteger)requestDeviceInformationWithMode:(unsigned char)mode
                               forInformation:(NSString **)information __deprecated;

/*
 METHOD         - requestPowerUpResetICC:(unsigned char)waitTime
 withOperation:(unsigned char)operation
 
 PARAMETERS     - waitTime:  of type unsigned char - The desired wait time
 operation: of type unsigned char - The type of operation to be performed: 0x01 = Wait for and Power-up ICC
 0x02 = Power-Down ICC
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs the Power Up/Reset ICC report to send to the device.
 */

- (NSInteger)requestPowerUpResetICC:(unsigned char)waitTime
                          operation:(unsigned char)operation;

/*
 ** DEPRECATED **
 
 METHOD         - requestPowerUpResetICCWithWaitTime:(unsigned char)waitTime
 withOperation:(unsigned char)operation
 
 PARAMETERS     - waitTime:  of type unsigned char - The desired wait time
 operation: of type unsigned char - The type of operation to be performed: 0x01 = Wait for and Power-up ICC
 0x02 = Power-Down ICC
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs the Power Up/Reset ICC report to send to the device.
 */

- (NSInteger)requestPowerUpResetICCWithWaitTime:(unsigned char)waitTime
                                  withOperation:(unsigned char)operation __deprecated;

/*
 METHOD         - requestDeviceStatus:(DEV_STATE_STAT **)information
 withStatus:(unsigned char *)status
 
 PARAMETERS     - devStateInfo: of type DEV_STATE_STAT - A pointer to DEV_STATE_STAT structure containing 5 byte values indicating: DeviceState,
 SessionState,
 DeviceStatus,
 DevCertStatus,
 HWStatus
 opStatus:     of type unsigned char  - A pointer to the buffer to be used to store the return status
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method takes as parameters information and status and constructs a command string to send to the device.
 */
- (NSInteger)requestDeviceStatus:(DEV_STATE_STAT **)information
                          status:(unsigned char *)status;

/*
 ** DEPRECATED **
 
 METHOD         - requestDeviceStatusForInformation:(DEV_STATE_STAT **)information
 withStatus:(unsigned char *)status
 
 PARAMETERS     - devStateInfo: of type DEV_STATE_STAT - A pointer to DEV_STATE_STAT structure containing 5 byte values indicating: DeviceState,
 SessionState,
 DeviceStatus,
 DevCertStatus,
 HWStatus
 opStatus:     of type unsigned char  - A pointer to the buffer to be used to store the return status
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method takes as parameters information and status and constructs a command string to send to the device.
 */
- (NSInteger)requestDeviceStatusForInformation:(DEV_STATE_STAT **)information
                                    withStatus:(unsigned char *)status __deprecated;

/*
 METHOD         - requestKeyInformation:(unsigned char)identification
 forInformation:(NSString **)information
 
 PARAMETERS     - identification: of type unsigned char - Key Information ID
 information:    of type NSString      - A pointer that contains the returned information from the device
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method retrieves the model, local device path, serial number, firmware version, PID, and VID of the connected device.
 */
- (NSInteger)requestKeyInformation:(unsigned char)identification
                       information:(NSString **)information;

/*
 ** DEPRECATED **
 
 METHOD         - requestKeyInformationWithIdentification:(unsigned char)identification
 forInformation:(NSString **)information
 
 PARAMETERS     - identification: of type unsigned char - Key Information ID
 information:    of type NSString      - A pointer that contains the returned information from the device
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method retrieves the model, local device path, serial number, firmware version, PID, and VID of the connected device.
 */
- (NSInteger)requestKeyInformationWithIdentification:(unsigned char)identification
                                      forInformation:(NSString **)information __deprecated;

/*
 METHOD         - requestKernalInformation:(unsigned char)identification
 forInformation:(NSString **)information
 
 PARAMETERS     - identification: of type unsigned char - Kernal Information ID: 0x00 – Version L1 Kernel
 0x01 – Version L2 Kernel
 0x02 – Checksum/Signature L1 Kernel
 0x03 – Checksum/Signature L2 Kernel
 0x03 – Checksum/Signature L2 Kernel + Configuration
 
 information:    of type NSString      - Pointer that contains the returned information
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method retrieves the Kernal Information of the connected device.
 */
- (NSInteger)requestKernalInformation:(unsigned char)identification
                          information:(NSString **)information;

/*
 ** DEPRECATED **
 
 METHOD         - requestKernalInformationWithIdentification:(unsigned char)identification
 forInformation:(NSString **)information
 
 PARAMETERS     - identification: of type unsigned char - Kernal Information ID: 0x00 – Version L1 Kernel
 0x01 – Version L2 Kernel
 0x02 – Checksum/Signature L1 Kernel
 0x03 – Checksum/Signature L2 Kernel
 0x03 – Checksum/Signature L2 Kernel + Configuration
 
 information:    of type NSString      - Pointer that contains the returned information
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method retrieves the Kernal Information of the connected device.
 */
- (NSInteger)requestKernalInformationWithIdentification:(unsigned char)identification
                                         forInformation:(NSString **)information __deprecated;

/*
 METHOD         - requestCard:(unsigned char)waitTime
 messageID:(unsigned char)cardMsg
 tone:(unsigned char)tones
 
 PARAMETERS     - waitTime: of type unsigned char - The amount of time in seconds to wait for user selection.
 cardMsg:  of type unsigned char - The card message to prompt user: 0 - CardMsgSwipeCardIdle
 1 - CardMsgSwipeCard
 2 - CardMsgPleaseSwipeCard
 3 - CardMsgPleaseSwipeAgain
 tones:    of type unsigned char - The type of tone to be used: None
 Single Beep
 Double Beep
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method causes the DynaPro Mini to prompt the user for a card swipe transaction.
 */
- (NSInteger)requestCard:(unsigned char)waitTime
               messageID:(unsigned char)messageID
                    tone:(unsigned char)tones;

/*
 METHOD         - sendAmount:(unsigned char)amountType
 amount:(NSString *)amount
 opStatus:(unsigned char *)status
 
 PARAMETERS     - amountType: of type unsigned char: 0x67 – Credit
 0x68 – Debit
 amount:     of type NSString
 status:     of type unsigned char
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method takes as parameters amountType, amount, and status and constructs a command string to send to the Send Command method.
 */
- (NSInteger)setAmount:(unsigned char)amountType
                amount:(NSString *)amount
              opStatus:(unsigned char *)opStatus;

/*
 METHOD         - setCAPublicKey:(unsigned char)operation
 withCAPublicKeyBlock:(unsigned char *)CAPublicKeyBlock
 withCAPublicKeyBlockLength:(int)CAPublicKeyBlockLength
 
 PARAMETERS     - operation:              of type unsigned char - The type of operation to be performed: 0 – Erase all CA Public Keys
 1 – Erase all CA Public Keys for a given RID
 2 – Erase a single CA Public Key
 3 – Add a single CA Public Key
 0x0F – Read all CA Public Keys
 CAPublicKeyBlock:       of type unsigned char - The Public Key Block
 CAPublicKeyBlockLength: of type int           - The Public Key Block length
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method sets/deletes the corresponding CA Public key given the type of operation.
 */
- (NSInteger)setCAPublicKey:(unsigned char)operation
           CAPublicKeyBlock:(unsigned char *)CAPublicKeyBlock
     CAPublicKeyBlockLength:(int)CAPublicKeyBlockLength;

/*
 ** DEPRECATED **
 
 METHOD         - setCAPublicKeyWithOperation:(unsigned char)operation
 withCAPublicKeyBlock:(unsigned char *)CAPublicKeyBlock
 withCAPublicKeyBlockLength:(int)CAPublicKeyBlockLength
 
 PARAMETERS     - operation:              of type unsigned char - The type of operation to be performed: 0 – Erase all CA Public Keys
 1 – Erase all CA Public Keys for a given RID
 2 – Erase a single CA Public Key
 3 – Add a single CA Public Key
 0x0F – Read all CA Public Keys
 CAPublicKeyBlock:       of type unsigned char - The Public Key Block
 CAPublicKeyBlockLength: of type int           - The Public Key Block length
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method sets/deletes the corresponding CA Public key given the type of operation.
 */
- (NSInteger)setCAPublicKeyWithOperation:(unsigned char)operation
                    withCAPublicKeyBlock:(unsigned char *)CAPublicKeyBlock
              withCAPublicKeyBlockLength:(int)CAPublicKeyBlockLength __deprecated;

/*
 METHOD         - requestManualCardData:(unsigned char)waitTime
 withTone:(unsigned char)tone
 withOption:(unsigned char)option
 withStatus:(unsigned char *)status
 
 PARAMETERS     - waitTime: of type BYTE
 tone:     of type BYTE: None
 Single Beep
 Double Beep
 option:   of type BYTE
 status:   of type BYTE
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This function causes the DynaPro Mini to prompt the user to input Card Data manually.
 */
- (NSInteger)requestManualCardData:(unsigned char)waitTime
                              tone:(unsigned char)tone
                            option:(unsigned char)option
                            status:(unsigned char *)status;

/*
 ** DEPRECATED **
 
 METHOD         - requestManualCardDataWithWaitTime:(unsigned char)waitTime
 withTone:(unsigned char)tone
 withOption:(unsigned char)option
 withStatus:(unsigned char *)status
 
 PARAMETERS     - waitTime: of type BYTE
 tone:     of type BYTE: None
 Single Beep
 Double Beep
 option:   of type BYTE
 status:   of type BYTE
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This function causes the DynaPro Mini to prompt the user to input Card Data manually.
 */
- (NSInteger)requestManualCardDataWithWaitTime:(unsigned char)waitTime
                                      withTone:(unsigned char)tone
                                    withOption:(unsigned char)option
                                    withStatus:(unsigned char *)status __deprecated;

/*
 METHOD         - requestEMVTags:(unsigned char)tagType
 withOperation:(unsigned char)operation
 withTLVDataBlock:(unsigned char *)tlvDataBlock
 withBlockLength:(int)blockLength
 transactionType:(unsigned char)transactionType
 
 PARAMETERS     - tagType:      of type unsigned char: 0x00 - Reader Tags
 operation:    of type unsigned char: 1 – Write Operation
 0xFF – Set to Factory defaults
 tlvDataBlock: of type unsigned char
 blockLength:  of type intgth:  of type int
 transactionType: of type unsigned char: 0x00 – Payment
 0x01 – Cash
 0x09 – Purchase with Cashback
 0x20 – Refund
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs a EMV Tag command to send to the device for getting and setting EMV Tags.
 */
- (NSInteger)requestGetEMVTags:(unsigned char)tagType
                     operation:(unsigned char)operation
                  tlvDataBlock:(unsigned char *)tlvDataBlock
                   blockLength:(int)blockLength
               transactionType:(unsigned char)transactionType;

/*
 METHOD         - requestSetEMVTags:(unsigned char)tagType
 withOperation:(unsigned char)operation
 withTLVDataBlock:(unsigned char *)tlvDataBlock
 withBlockLength:(int)blockLength
 database:(unsigned char)database
 transactionType:(unsigned char)transactionType
 
 PARAMETERS     - tagType:      of type unsigned char: 0x00 - Reader Tags
 operation:    of type unsigned char: 1 – Write Operation
 0xFF – Set to Factory defaults
 tlvDataBlock: of type unsigned char
 blockLength:  of type int
 database: of type unsigned char: 00 – Contact L2 EMV Tags
 01 – PayPass - MasterCard
 02 – PayWave – VISA
 03 – ExpressPay - AMEX
 04 - Discover
 transactionType: of type unsigned char: 0x00 – Payment
 0x01 – Cash
 0x09 – Purchase with Cashback
 0x20 – Refund
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs a EMV Tag command to send to the device for getting and setting EMV Tags.
 */
- (NSInteger)requestSetEMVTags:(unsigned char)tagType
                     operation:(unsigned char)operation
                  tlvDataBlock:(unsigned char *)tlvDataBlock
                   blockLength:(int)blockLength
                      database:(unsigned char)database
               transactionType:(unsigned char)transactionType;

/*
 METHOD         - requestEMVTags:(unsigned char)tagType
 withOperation:(unsigned char)operation
 withTLVDataBlock:(unsigned char *)tlvDataBlock
 withBlockLength:(int)blockLength
 
 PARAMETERS     - tagType:      of type unsigned char: 0x00 - Reader Tags
 operation:    of type unsigned char: 1 – Write Operation
 0xFF – Set to Factory defaults
 tlvDataBlock: of type unsigned char
 blockLength:  of type intgth:  of type int
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs a EMV Tag command to send to the device for getting and setting EMV Tags.
 */
- (NSInteger)requestEMVTags:(unsigned char)tagType
                  operation:(unsigned char)operation
               tlvDataBlock:(unsigned char *)tlvDataBlock
                blockLength:(int)blockLength __deprecated;

/*
 ** DEPRECATED **
 
 METHOD         - requestEMVTagsWithTagType:(unsigned char)tagType
 withOperation:(unsigned char)operation
 withTLVDataBlock:(unsigned char *)tlvDataBlock
 withBlockLength:(int)blockLength
 
 PARAMETERS     - tagType:      of type unsigned char: 0x00 - Reader Tags
 operation:    of type unsigned char: 1 – Write Operation
 0xFF – Set to Factory defaults
 tlvDataBlock: of type unsigned char
 blockLength:  of type intgth:  of type int
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs a EMV Tag command to send to the device for getting and setting EMV Tags.
 */
- (NSInteger)requestEMVTagsWithTagType:(unsigned char)tagType
                         withOperation:(unsigned char)operation
                      withTLVDataBlock:(unsigned char *)tlvDataBlock
                       withBlockLength:(int)blockLength __deprecated;

/*
 METHOD         - requestUserDataEntry:(BYTE)waitTime
 withDisplayMessage:(BYTE)displayMessage
 withTone:(BYTE)tone
 withStatus:(BYTE *)status
 
 PARAMETERS     - waitTime: of type unsigned char - The amount of time in seconds to wait for user data entry
 selMsg:   of type unsigned char - One of 4 messagesto prompt user: 0 — SSN,
 1 – Zip Code,
 2 – Birth (Four Year),
 3 – Birth (Two Year)
 tone:     of type unsigned char - The type of tone to be used: None,
 Single Beep,
 Double Beep
 opStatus: of type unsigned char - Pointer to the buffer to be used to store the return status.
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs the response report to send to the device. The device will prompt the user to select the transaction type.
 */
- (NSInteger)requestUserDataEntry:(unsigned char)waitTime
                   displayMessage:(unsigned char)displayMessage
                             tone:(unsigned char)tone
                           status:(unsigned char *)status;

/*
 METHOD         - MTIPADRequestUserDataEntry:(BYTE)waitTime
 withDisplayMessage:(BYTE)displayMessage
 withTone:(BYTE)tone
 withStatus:(BYTE *)status
 
 PARAMETERS     - waitTime: of type unsigned char - The amount of time in seconds to wait for user data entry
 selMsg:   of type unsigned char - One of 4 messagesto prompt user: 0 — SSN,
 1 – Zip Code,
 2 – Birth (Four Year),
 3 – Birth (Two Year)
 tone:     of type unsigned char - The type of tone to be used: None,
 Single Beep,
 Double Beep
 opStatus: of type unsigned char - Pointer to the buffer to be used to store the return status.
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs the response report to send to the device. The device will prompt the user to select the transaction type.
 */
- (NSInteger)requestUserDataEntryWithwaitTime:(unsigned char)waitTime
                           withDisplayMessage:(unsigned char)displayMessage
                                     withTone:(unsigned char)tone
                                   withStatus:(unsigned char *)status __deprecated;

/*
 METHOD         - requestResponse:(unsigned char)waitTime
 selectMsgType:(unsigned char)selectMsg
 mask:(unsigned char)maskVal
 tones:(unsigned char)toneVal
 keyPressed:(unsigned char *)keyPressedVal
 opStatus:(unsigned char *)retVal
 
 PARAMETERS     - waitTime:      of type unsigned char - The amount of time in seconds to wait for user selection
 selectMsg:     of type unsigned char - The message to prompt user: 0 – Transaction Type (Credit/Debit),
 1 - Verify Transaction Amount,
 2 – Credit Other Debit,
 3 – Credit EBT Debit,
 4 – Credit Gift Debit,
 5 – EBT Gift Other
 maskVal:       of type unsigned char - Key codes to mask: 8 – Enter,
 4 – Right,
 2 – Middle,
 1 – Left. These values can be combined using OR
 toneVal:        of type unsigned char - User can choose one of the following: BuzzerNone, BuzzerSingleBeep, BuzzerDoubleBeep
 keyPressedVal:  of type unsigned char - Byte value indicating the key pressed
 retVal:         of type unsigned char - Pointer to the buffer to be used to store the return status
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This function causes the DynaPro Mini to prompt the user to select the transaction type (debit or credit) or to verify the transaction amount.
 */
- (NSInteger)requestResponse:(unsigned char)waitTime
           selectMessageType:(unsigned char)selectMsg
                        mask:(unsigned char)maskVal
                       tones:(unsigned char)tones
                  keyPressed:(unsigned char *)keyPressedVal
                    opStatus:(unsigned char *)retVal;

/*
 METHOD         - requestConfirmSessionKey:(unsigned char)mode
 withEncryptedTransformedRandomNumber:(unsigned char)encryptedTransformedRandomNumber
 withEncryptedTransformedRandomNumberLength:(unsigned char)encryptedTransformedRandomNumberLength
 withCMAC:(unsigned char)CMAC
 withCMACLength:(int)CMACLength
 withStatus:(NSString **)status
 
 PARAMETERS     - mode:                                  of type unsigned char - The mode type: 0 - End Session
 1 - Confirm Session
 encyptedTransformedRandomNumber:       of type unsigned char - The encrypted transformed random number to be passed in
 encyptedTransformedRandomNumberLength: of type int           - The encrypted transformed random number's length to be passed in
 CMAC:                                  of type unsigned char - The CMAC to be passed in
 CMACLength:                            of type int           - The CMAC length to be passed in
 status:                                of type NSString      - The returned status
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs a CMAC message to send to the device to confirm the session key.
 */
- (NSInteger)requestConfirmSessionKey:(unsigned char)mode
     encryptedTransformedRandomNumber:(unsigned char *)encryptedTransformedRandomNumber
encryptedTransformedRandomNumberLength:(int)encryptedTransformedRandomNumberLength
                                 CMAC:(unsigned char *)CMAC
                           CMACLength:(int)CMACLength
                               status:(NSString **)status;

/*
 ** DEPRECATED **
 
 METHOD         - requestConfirmSessionKeyWithMode:(unsigned char)mode
 withEncryptedTransformedRandomNumber:(unsigned char)encryptedTransformedRandomNumber
 withEncryptedTransformedRandomNumberLength:(unsigned char)encryptedTransformedRandomNumberLength
 withCMAC:(unsigned char)CMAC
 withCMACLength:(int)CMACLength
 withStatus:(NSString **)status
 
 PARAMETERS     - mode:                                  of type unsigned char - The mode type: 0 - End Session
 1 - Confirm Session
 encyptedTransformedRandomNumber:       of type unsigned char - The encrypted transformed random number to be passed in
 encyptedTransformedRandomNumberLength: of type int           - The encrypted transformed random number's length to be passed in
 CMAC:                                  of type unsigned char - The CMAC to be passed in
 CMACLength:                            of type int           - The CMAC length to be passed in
 status:                                of type NSString      - The returned status
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method constructs a CMAC message to send to the device to confirm the session key.
 */
- (NSInteger)requestConfirmSessionKeyWithMode:(unsigned char)mode
         withEncryptedTransformedRandomNumber:(unsigned char *)encryptedTransformedRandomNumber
   withEncryptedTransformedRandomNumberLength:(int)encryptedTransformedRandomNumberLength
                                     withCMAC:(unsigned char *)CMAC
                               withCMACLength:(int)CMACLength
                                   withStatus:(NSString **)status __deprecated;

/*
 METHOD         - requestPIN:(unsigned char)waitTime
 messageType:(unsigned char)pinMsg
 PINLenMin:(unsigned char)minLen
 PINLenMax:(unsigned char)maxLen
 tones:(unsigned char)tonetype
 options:(unsigned char)option
 
 PARAMETERS     - waitTime: of type unsigned char - The amount of time in seconds to wait for user selection
 pinMsg:   of type unsigned char - One of 5 messages to prompt user: 0—PinMsgEnterPin, 1 – PinMsgEnterPinAmt, 2 – PinMsgReenterPINAmt, 3 – PinMsgReenterPIN, 4 – PinMsgVerifyPIN
 minLen:   of type unsigned char - The minumum PIN value to accept. Must be greater than 3.
 maxLen:   of type unsigned char - The maxium PIN value to accept. Must be less than 13.
 tonetype: of type unsigned char - User can choose one of the following: BuzzerNone, BuzzerSingleBeep, BuzzerDoubleBeep
 option:   of type unsigned char - 0 - ISO0 Format, No verify PIN 1 - ISO3 Format, No verify PIN 2 - ISO0 Format, Verify PIN 3 - ISO3 Format, Verify PIN
 
 Note: If there is no PAN (from card swipe or sent via command), then the EPB will use ISO format 1. If a PAN exists, then the PIN option will be used to determine if the created PIN  block   will be ISO 12 Methods format 0 or ISO format 3. If the VerifyPIN option is set, the DynaPro Mini will request the user to enter his or her PIN twice and will generate an EPB only if both entries match. The EPB is encrypted under the current PIN DUKPT key as DES or TDES depending on the injected key type.
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This function causes the DynaPro Mini to prompt the user for his or her PIN.
 */
- (NSInteger)requestPIN:(unsigned char)waitTime
            messageType:(unsigned char)pinMsg
           PINLengthMin:(unsigned char)minLen
           PINLengthMax:(unsigned char)maxLen
                  tones:(unsigned char)tones
                options:(unsigned char)option;

/*
 METHOD         - requestSmartCard:(unsigned char)cardType
 withConfirmationWaitTime:(unsigned char)confirmationWaitTime
 withPINWaitTime:(unsigned char)PINWaitTime
 withTone:(unsigned char)tone
 withOption:(unsigned char)option
 withAmount:(unsigned char *)amount         //6 bytes
 withTransactionType:(unsigned char)transactionType
 withCashBack:(unsigned char *)cashBack    //4 bytes
 withReservedBytes:(unsigned char *)reservedBytes
 
 PARAMETERS     - cardType:             of type unsigned char - The card type that will be used: 1 - Magnetic Stripe
 2 - Contact Smart Card
 confirmationWaitTime: of type unsigned char - The wait time in seconds for the user to respond
 PINWaitTime:          of type unsigned char - The wait time in seconds for the user to enter their PIN
 tone:                 of type unsigned char - The type of tone to be used: None
 Single Beep
 Double Beep
 option:               of type unsigned char - The type of option to be used (this should be set to 0 for normal functionality)
 amount:               of type unsigned char - The amount of the current transaction
 transactionType:      of type unsigned char - The type of transaction to be used
 cashBack:             of type unsigned char - The amount of cash back to be used
 reservedBytes:        of type unsigned char - The reserved bytes to be used (Example: 'unsigned char rb[28] = {0};')
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method causes the DynaPro Mini to prompt the user for a smart card transaction.
 */
- (NSInteger)requestSmartCard:(unsigned char)cardType
         confirmationWaitTime:(unsigned char)confirmationWaitTime
                  PINWaitTime:(unsigned char)PINWaitTime
                         tone:(unsigned char)tone
                       option:(unsigned char)option
                       amount:(unsigned char *)amount              //6 bytes
              transactionType:(unsigned char)transactionType
                     cashBack:(unsigned char *)cashBack            //4 bytes
                reservedBytes:(unsigned char *)reservedBytes;

/*
 ** DEPRECATED **
 
 METHOD         - requestSmartCardWithCardType:(unsigned char)cardType
 withConfirmationWaitTime:(unsigned char)confirmationWaitTime
 withPINWaitTime:(unsigned char)PINWaitTime
 withTone:(unsigned char)tone
 withOption:(unsigned char)option
 withAmount:(unsigned char *)amount         //6 bytes
 withTransactionType:(unsigned char)transactionType
 withCashBack:(unsigned char *)cashBack    //4 bytes
 withReservedBytes:(unsigned char *)reservedBytes
 
 PARAMETERS     - cardType:             of type unsigned char - The card type that will be used: 1 - Magnetic Stripe
 2 - Contact Smart Card
 confirmationWaitTime: of type unsigned char - The wait time in seconds for the user to respond
 PINWaitTime:          of type unsigned char - The wait time in seconds for the user to enter their PIN
 tone:                 of type unsigned char - The type of tone to be used: None
 Single Beep
 Double Beep
 option:               of type unsigned char - The type of option to be used (this should be set to 0 for normal functionality)
 amount:               of type unsigned char - The amount of the current transaction
 transactionType:      of type unsigned char - The type of transaction to be used
 cashBack:             of type unsigned char - The amount of cash back to be used
 reservedBytes:        of type unsigned char - The reserved bytes to be used (Example: 'unsigned char rb[28] = {0};')
 
 RETURN         - This method returns a NSInteger value (0: SUCCESS, Non-Zero: ERROR)
 
 DESCRIPTION    - This method causes the DynaPro Mini to prompt the user for a smart card transaction.
 */
- (NSInteger)requestSmartCardWithCardType:(unsigned char)cardType
                 withConfirmationWaitTime:(unsigned char)confirmationWaitTime
                          withPINWaitTime:(unsigned char)PINWaitTime
                                 withTone:(unsigned char)tone
                               withOption:(unsigned char)option
                               withAmount:(unsigned char *)amount              //6 bytes
                      withTransactionType:(unsigned char)transactionType
                             withCashBack:(unsigned char *)cashBack            //4 bytes
                        withReservedBytes:(unsigned char *)reservedBytes __deprecated;

#pragma mark -
#pragma mark MTPPSCRA Helper Methods
#pragma mark -

- (NSString *)convertHexToASCIIWithString:(NSString *)hexString;

- (NSString *)bytesToHexStringWithData:(unsigned char *)data
                        withDataLength:(int)dataLength;

- (NSInteger)hexToBytesWithString:(NSString *)hexString
                         outBytes:(unsigned char *)outBytes
                   outBytesLength:(NSInteger *)outBytesLength;

#pragma mark -
#pragma mark PIN Data Helper Methods
#pragma mark -

// Returns the Encrypted PIN Block Data information
- (NSString *)getEPB;

// Returns the PIN KSN information
- (NSString *)getPINKSN;

// Returns the PIN Status Code information
- (NSString *)getPINStatusCode;

#pragma mark -
#pragma mark Card Data Helper Methods
#pragma mark -

// Clears the property values
- (void)clearBuffer;

// Returns the current Status Code
- (int)getStatusCode;

// Returns the PAN information
- (NSString *)getPAN;

// Returns the KSN information
- (NSString *)getKSN;

// Returns the Library Version
- (NSString *)getSDKVersion;

// Returns the Card Type
- (NSString *)getEncodeType;

// Returns the Product ID
- (NSString *)getProductID;

// Returns the Device Model information
- (NSString *)getDeviceModel;

// Returns the Device Serial information
- (NSString *)getDeviceSerial;

// Returns the Device Firmware Version information
- (NSString *)getDeviceFirmwareVersion;

// Returns the Encrypted Track 1 information
- (NSString *)getTrack1;

// Returns the Encrypted Track 2 information
- (NSString *)getTrack2;

// Returns the Encrypted Track 3 information
- (NSString *)getTrack3;

// Returns the Masked Track 1 information
- (NSString *)getTrack1Masked;

// Returns the Masked Track 2 information
- (NSString *)getTrack2Masked;

// Returns the Masked Track 3 information
- (NSString *)getTrack3Masked;

// Returns the Masked Tracks
- (NSString *)getMaskedTracks;

// Returns the Track 2 Equivalent information from an ICC Card's Chip
- (NSString *)getTrack2Equivalent;

// Returns the MagnePrint information
- (NSString *)getMagnePrint;

// Returns the MagnePrint Status information
- (NSString *)getMagnePrintStatus;

// Returns the Track 1 Decode Status information
- (NSString *)getTrack1DecodeStatus;

// Returns the Track 2 Decode Status information
- (NSString *)getTrack2DecodeStatus;

// Returns the Track 3 Decode Status information
- (NSString *)getTrack3DecodeStatus;

// Returns the Last Name information
- (NSString *)getLastName;

// Returns the First Name information
- (NSString *)getFirstName;

// Returns the Middle Name information
- (NSString *)getMiddleName;

// Returns the Card Expiration Date information
- (NSString *)getExpDate;

// Returns the Card Type
- (NSString *)getCardType;

// Returns the last four digits of the Card Number
- (NSString *)getCardLast4;

// Returns the Card Service Code information
- (NSString *)getCardServiceCode;

// Returns the Response Data from the DynaPro Mini
- (NSString *)getResponseData;

// Returns the Response Data from the DynaPro Mini using SRED Firmware
- (NSString *)getSREDResponseData;

// Returns the Transaction Status of the current transaction
- (NSString *)getTransactionStatus;

// Returns if the signature is required from the user
- (BOOL)isSignatureRequired;

// Returns if the DynaPro Mini device firmware is SRED or Non-SRED
- (BOOL)isDeviceSRED:(NSString **)error;

// Returns the current ACK Status after a command has been sent to the device
- (NSString *)getCurrentACKStatus;

// Returns the Capability string of the Device
- (NSString *)getDeviceCapabilityString;

#pragma mark -
#pragma mark Device Handler Methods
#pragma mark -

// Initialize the device
- (BOOL)openDevice;

// Close the device
- (BOOL)closeDevice;

// Retrieves the Device Type
- (int)getDeviceType;

// Retrieves the Device open status
- (BOOL)isDeviceOpened;

// Retrieves the Device connection status
- (BOOL)isDeviceConnected;

// Retrieves the Device Firmware type boolean (YES = SRED; NO = Non-SRED)
- (BOOL)isDeviceFirmwareSRED;

// Retrieves the currently connected Peripheral
- (CBPeripheral *)getConnectedPeripheral;

// Sets the type of device to open
- (void)setDeviceType:(UInt32)deviceType;

// Retrieves the list of Peripherals that are in range and can be connected to
- (NSMutableArray *)getDiscoveredPeripherals;

// Sets the UUID String for the DynaPro Min BLE
- (void)setDeviceUUIDString:(NSString *)uuidString;

// Sets the Device Protocol String
- (void)setDeviceProtocolString:(NSString *)protocolString;

- (void)_mergeData:(NSString *)input;

@end