# Magtek Plugin

Cordova plugin for [Magtek](https://www.magtek.com/) devices, with this plugin you can search, connect and make transactions using magtek devices to read data from credit/debit cards.

# Security
Remember that all cordova code is exposed (client side) and you shouldn't store any private keys in code.

# Use
This plugin defines global **magtek** object.

Although in the global scope, it is not available until after the deviceready event.
```javascript
document.addEventListener("deviceready", onDeviceReady, false);
function onDeviceReady() {
    console.log(magtek);
}
```

Note: Plugin requires the following frameworks, although plugin adds them, double check that are properly referenced in xcode project:

- AVFoundation
- CoreBluetooth
- libMTPPSCRA.a
- libCryptographicLibrary.a
- libTLVParserLibrary.a

# Install

Install using `cordova plugin add https://github.com/auctifera-josed/cordova-plugin-cardflight`

# Example
```javascript
magtek.init(function(err,res){
  if (err) console.log(err);
  else console.log(res);
}, 'XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX')

var q = function(res){console.log(res);}
magtek.startScanningForPeripherals(q,q);
magtek.getDiscoveredPeripherals(q,q); //Response example: '{name: "DPMini040F16100D", state: "disconnected", identifier: "C1553D35-XXXX-XXXX-XXXX-58E2F82DAD4E"}'
magtek.connectToBLEReader(q,q,"C1553D35-XXXX-4CC7-XXXX-58E2F82DAD4E"); //Device should start
magtek.requestCard(q,q)//After swiping the card, the `CardRequestComplete` event contains the card information
```
# API Reference

**you need to call init function before using any other method**

Function List
- [init(callback, BDK)](#init)
- Device connection functions
  - [startScanningForPeripherals(success, error)](#startscanningforperipherals)
  - [stopScanningForPeripherals(success, error)](#stopscanningforperipherals)
  - [getDiscoveredPeripherals(success, error)](#getdiscoveredperipherals)
  - [isDeviceOpened(success, error)](#isdeviceopened)
  - [isDeviceConnected(success, error)](#isdeviceconnected)
  - [getConnectedPeripheral(success, error)](#getconnectedperipheral)
  - [connectToBLEReader(success, error, identifier)](#connecttoblereader)
  - [disconnectFromBLEReader(success, error)](#disconnectfromblereader)
- Device operation functions
  - [deviceReset(success, error)](#devicereset)
  - [cancelOperation(success, error)](#canceloperation)
- Transaction functions
  - [requestCard(success, error)](#requestcard)
  - [requestConfirmAmount(success, error)](#requestconfirmamount)
  - [getLastTransactionInfo(success, error)](#getlasttransactioninfo)
  - [requestSmartCardTransaction(success, error, amount)](#requestsmartcardtransaction)

Event List
- [Card](#card)
- Error
- BINDataReceived
- DataArriveComplete
- ACKStatusReceived
- ATRRequestComplete
- SendICCAPDUComplete
- SetCAPublicKeyComplete
- PINRequestComplete
- KeyRequestComplete
- BypassPinCommandComplete
- SendCommandTimeOutComplete
- RequestPowerUpResetICCComplete
- OperationStatusReceived
- [CardRequestComplete](#cardrequestcomplete)
- RequestICCAPDUComplete
- RequestSmartCardComplete
- RequestSetEMVTagsComplete
- RequestUserDataEntryComplete

# Functions

## init
The `init(callback, BDK)` function sets the BDK ([Base Derivation Key](https://en.wikipedia.org/wiki/Derived_unique_key_per_transaction#Keys)) and initializes the magtek instance.

**you need to set the BDK before using any other method**

### Parameters
#### callback
function(err,res){}

#### BDK
The [Base Derivation Key](https://en.wikipedia.org/wiki/Derived_unique_key_per_transaction#Keys) is the unique company fixed key 

## startScanningForPeripherals
The `startScanningForPeripherals This method starts the scanning of surrounding Peripherals.

## stopScanningForPeripherals
This method stops the scanning for surrounding Peripherals.

## getDiscoveredPeripherals
This method retrieves the surrounding discovered peripherals(DynaPro Minis)

## isDeviceOpened
Retrieves the device’s open status

## isDeviceConnected
Retrieves the device’s connection status

## getConnectedPeripheral
This method retrieves the currently connected peripheral (DynaPro Mini)

## connectToBLEReader
This method sets the UUID string for the device to be connected to through BLE, connecting to the device

### Parameters
####

## disconnectFromBLEReader
## deviceReset
This method simply sends the reset command to the device.

## cancelOperation
This method sends the cancel command to the device.

## requestCard
This method triggers the device to begin the Card Swipe Transaction.

## requestConfirmAmount
This method sends the Response report to the device. The device will prompt the user to select a transaction type.

## getLastTransactionInfo
This methods returns an object containing the last transaction information (last name, first name, middle name, expiration date, card type, card last 4, card service code)

## requestSmartCardTransaction
This method triggers a Smart Card transaction.

# Events
Listen to Magtek events as cases of the **magtekEvent** event and get the event `data` attribute: 

```javascript
window.addEventListener('magtekEvent', function (e) {
  switch (e.dataType) {
    case 'CardRequestComplete':
      console.log(e.data);
      break;
    case 'Card':
      console.log(e.data);
      break;
    case 'OperationStatusReceived':
      console.log(e.data);
      break;
    case ...:
      console.log(e.data);
      break;
    default:
      console.log(e);
  }
});
```
## Card
Called when the MSR data is ready to be retrieved after issuing requestCard. Data is a String

## Error
Called when an error is encountered.
data: A string value containing the error description

## DataArriveComplete
Called when data is returned from sendSpecialCommandWithCommand.
data: A String value is returned containing the data received from the device

## ATRRequestComplete
Called when data is returned from requestATR.
data: A String value is returned containing the ATR data received from the device

## SendICCAPDUComplete
Called when data is returned from sendICCAPDUWithCommand.
data: A String value is returned containing the ICC APDU data received from the device

## SetCAPublicKeyComplete
Called when data is returned from setCAPublicKeyWithOperation.
data: A String value is returned containing the CA Public Key data received from the device

## PINRequestComplete
Called when data is returned from requestPIN.
data: A PIN DATA object is returned containing the KSN, Encrypted PIN Block, and Status Code

## KeyRequestComplete
Called when data is returned from requestResponse.
data: An Unsigned Char value is returned containing the Key Value data of the Key that was pressed by the user

## DisplayRequestComplete
Called when data is returned from setDisplayMessage.
data: An Unsigned Char value is returned containing the Status Code of the Display Message

## BypassPINCommandComplete
Called when data is returned from requestBypassPINCommand.
data: A String value is returned containing the Bypass PIN data received from the device

## SendCommandTimeOutComplete
Called when data is returned from sendSpecialCommandWithCommand.
data: A String value is returned containing data (if any) from the Time

## RequestDeviceConfigurationComplete
Called when data is returned from requestDeviceConfigurationForInformation.
data: A String value is returned containing the Device Configuration information from the device

## RequestPowerUpResetICCAPDUComplete
Called when data is returned from requestPowerUpResetICCWithWaitTime.
data: A String value is returned containing the ICC APDU data (if any) after the device has completed the Reset/Power Up

## RequestChallengeAndSessionKeyRequestComplete
Called when data is returned from requestChallengeAndSessionForInformation.
data: A String value is returned containing the Challenge and Session Key from the device

## CardRequestComplete
Called when data is returned from requestCard.
data: A CARD DATA INFO object is returned containing all of the necessary card data

Eg:
```javascript
{
  CardExpDate = 2312;
  CardLast4 = 4242;
  CardServiceCode = 000;
  DeviceSerial = 98D50C040F16100D;
  EncodeType = 01;
  FirstName = "";
  KSN = 95000300000cd6200030;
  LastName = 11;
  MagnePrint = 5d6d3686basdasdasd9aa6fcde77909b4ead3b125e8066e41b9b0cc65a08fc4deece3d059473df2ee83a9fc74192a692ef71a240b98cd3;
  MagnePrintStatus = 00002200;
  MiddleName = "";
  PAN = 4242424243004242;
  SDKVersion = "105.01";
  Track1 = 9dffabf6c9a8b08284a0c020920fa5cfa212fe687808039f6f0ad39199725a363bae82131lnasdnasafa6ff9ab599bdad2af3c305a471ee4d141670887a09564e4257af921500224f937b4571609b8f;
  Track1DecodeStatus = 00;
  Track1Masked = "%B4242424243004242^TEST CARD   ^2312000000000000000000000000000?";
  Track1UnMasked = "%B4242424242424242^TEST CARD   ^2312000000000000000000000000000?";
  Track2 = 94a3c0f4e1f17912321312b5a563c91d110491d81105d60ec09ee9aae39a238d84992312f12e3abf;
  Track2DecodeStatus = 00;
  Track2Masked = ";4894210003004211=23120000000000000000?";
  Track2Masked = ";4242424243004242=23120000000000000000?";
  Track2Unmasked = ";4242424242424242=23120000000000000000?";
  Track3 = "";
  Track3Masked = "";
  Track3Unmasked = "";
}
```

## RequestICCAPDUComplete
Called when data is returned from requestICCAPDUForInformation.
data: An object with two attributes: operationStatus (A String value is returned for the operation status) and cardStatus (A String value is returned for the card status)

## RequestSetEMVTagsComplete
Called when data is returned from requestSetEMVTagsWithTagType.
data: A String value is returned containing the EMV Tag data

## RequestSmartCardComplete
Called after sendAcquirerResponseWithResponse is completed.
data: A String value is returned containing the Smart Card batch data

## SendAcquirerResponseComplete
Called when data is returned from sendAcquirerResponseWithResponse.
data: A String value is returned containing the Acquirer Response data

## RequestUserDataEntryComplete
Called when data is returned from requestUserDataEntryWithWaitTime.
data: A USER DATA ENTRY object is returned containing the Encrypted Data Block and the MSR KSN.
