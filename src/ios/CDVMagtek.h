#import <Cordova/CDVPlugin.h>
#import <Foundation/Foundation.h>
#import <Cordova/CDV.h>
#import <CoreBluetooth/CoreBluetooth.h>

#import "MTPPSCRA.h"
#import "Constants.h"
#import "MTCryptoLib.h"
#import "MTTLV.h"
#import "DUKPT.h"

typedef enum eFunctionKey
{
	FuncKeyLeft   = 0x31,
    FuncKeyMiddle = 0x32,
    FuncKeyRight  = 0x33,
    FuncKeyEnter  = 0x78
    
} eFunctionKey;

@interface CDVMagtek : CDVPlugin <MTPPSCRADelegate>

@property BOOL isConfirmAmountSelected;
@property BOOL displayApproved;
// @property BOOL isCardSwipeSelected;
@property (strong, nonatomic) NSString *deviceSerialNumber;

- (void)init: (CDVInvokedUrlCommand *) command;
- (void)isDeviceConnected: (CDVInvokedUrlCommand *) command;
- (void)isDeviceOpened: (CDVInvokedUrlCommand *) command;
- (void)getDiscoveredPeripherals: (CDVInvokedUrlCommand *) command;
- (void)startScanningForPeripherals: (CDVInvokedUrlCommand *) command;
- (void)stopScanningForPeripherals: (CDVInvokedUrlCommand *) command;
- (void)getConnectedPeripheral: (CDVInvokedUrlCommand *) command;
- (void)connectToBLEReader: (CDVInvokedUrlCommand *) command;
- (void)disconnectFromBLEReader: (CDVInvokedUrlCommand *) command;
- (void)setAmount: (CDVInvokedUrlCommand*) command;
- (void)requestCard: (CDVInvokedUrlCommand*) command;
// - (void)requestConfirmAmount: (CDVInvokedUrlCommand*) command;
- (void)cancelOperation: (CDVInvokedUrlCommand*) command;
- (void)deviceReset: (CDVInvokedUrlCommand*) command;
- (void)getLastTransactionInfo: (CDVInvokedUrlCommand*) command;
- (void)requestSmartCardTransaction: (CDVInvokedUrlCommand*) command;

@end