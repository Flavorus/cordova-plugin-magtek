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

Note: **you need to call init function before using any other method**

Function List
- [init(BDK, callback)](#init)
- Device connection functions
  - [startScanningForPeripherals(success, error)](#startscanningforperipherals)
  - [stopScanningForPeripherals(success, error)](#stopscanningforperipherals)
  - [getDiscoveredPeripherals(success, error)](#getdiscoveredperipherals)
  - [connectToBLEReader(identifier, success, error)](#connecttoblereader)
  - [getConnectedPeripheral(success, error)](#getconnectedperipheral)
  - [disconnectFromBLEReader(success, error)](#disconnectfromblereader)
  - [isDeviceConnected(success, error)](#isdeviceconnected)
- Device operation functions
  - [deviceReset(success, error)](#devicereset)
  - [cancelOperation(success, error)](#canceloperation)
  - [isDeviceOpened(success, error)](#isdeviceopened)
- Transaction functions
  - [requestCard(success, error)](#requestcard)
  - [requestConfirmAmount(success, error)](#requestconfirmamount)
  - [getLastTransactionInfo(success, error)](#getlasttransactioninfo)
  - [requestSmartCardTransaction(amount, success, error)](#requestsmartcardtransaction)

[Event List](#events)
- Card
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
- CardRequestComplete
- RequestICCAPDUComplete
- RequestSmartCardComplete
- RequestSetEMVTagsComplete
- RequestUserDataEntryComplete

---

# Functions
Almost all the functions take success an error parameters, this are callback functions to execute in either case.

E.g: 
```javascript
var res = function(r){console.log(r);}
```

## init
The `init(BDK, callback)` function sets the BDK ([Base Derivation Key](https://en.wikipedia.org/wiki/Derived_unique_key_per_transaction#Keys)) and initializes the magtek instance.

**you need to set the BDK before processing a card**
| Parameter | Value    | 
| --------- | -------- |
| BDK       | The [Base Derivation Key](https://en.wikipedia.org/wiki/Derived_unique_key_per_transaction#Keys) is the unique company fixed key |
| callback  | `function(err,res){}` |

## startScanningForPeripherals
The `startScanningForPeripherals(success, error)` method starts the scanning of surrounding Peripherals.

## stopScanningForPeripherals
The `stopScanningForPeripherals(success, error)` method stops the scanning for surrounding Peripherals.

## getDiscoveredPeripherals
The `getDiscoveredPeripherals(success, error)` method retrieves the surrounding discovered peripherals(DynaPro Minis)

## isDeviceOpened
The `isDeviceOpened(success, error)` method retrieves the device’s open status

## isDeviceConnected
The `isDeviceConnected(success, error)` method retrieves the device’s connection status

## getConnectedPeripheral
The `getConnectedPeripheral(success, error)` method retrieves the currently connected peripheral (DynaPro Mini)

## connectToBLEReader
The `connectToBLEReader(identifier, success, error)` method sets the UUID string for the device to be connected to through BLE, connecting to the device

| Parameter   | Value    | 
| ----------- | -------- |
| identifier  | The magtek device's unique identifier (obtained using the `getDiscoveredPeripherals` method)     |

## disconnectFromBLEReader
The `disconnectFromBLEReader(success, error)` method removes the UUID string for the device to be disconnected from BLE, disconnecting from the device

## deviceReset
The `deviceReset(success, error)` method simply sends the reset command to the device.

## cancelOperation
The `cancelOperation(success, error)` method sends the cancel command to the device.

## requestCard
The `requestCard(success, error)` method triggers the device to begin the Card Swipe Transaction.

## requestConfirmAmount
The `requestConfirmAmount(success, error)` method sends the Response report to the device. The device will prompt the user to select a transaction type.

## getLastTransactionInfo
The `getLastTransactionInfo(success, error)` methods returns an object containing the last transaction information (last name, first name, middle name, expiration date, card type, card last 4, card service code)

## requestSmartCardTransaction
The `requestSmartCardTransaction(amount, success, error)` method triggers a Smart Card transaction.

| Parameter   | Value    | Example |
| ----------- | -------- | --- |
| amount  | A String containing the amount to pay | "200" |


---

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

| Event | description | data  |
| --- | -------- | -------- |
| SetCAPublicKeyComplete  | Called when data is returned from setCAPublicKeyWithOperation.| A String value is returned containing the CA Public Key data received from the device |
| SendICCAPDUComplete | Called when data is returned from sendICCAPDUWithCommand. | A String value is returned containing the ICC APDU data received from the device |
| ATRRequestComplete | Called when data is returned from requestATR. | A String value is returned containing the ATR data received from the device |
| DataArriveComplete | Called when data is returned from sendSpecialCommandWithCommand. | A String value is returned containing the data received from the device |
| Error | Called when an error is encountered. | A string value containing the error description |
| Card | Called when the MSR data is ready to be retrieved after issuing requestCard. | A String |
| PINRequestComplete | Called when data is returned from requestPIN. | A PIN DATA object is returned containing the KSN, Encrypted PIN Block, and Status Code |
| KeyRequestComplete | Called when data is returned from requestResponse. | An Unsigned Char value is returned containing the Key Value data of the Key that was pressed by the user |
| DisplayRequestComplete | Called when data is returned from setDisplayMessage. | An Unsigned Char value is returned containing the Status Code of the Display Message |
| BypassPINCommandComplete | Called when data is returned from requestBypassPINCommand. | A String value is returned containing the Bypass PIN data received from the device |
| SendCommandTimeOutComplete | Called when data is returned from sendSpecialCommandWithCommand. | A String value is returned containing data (if any) from the Time |
| RequestDeviceConfigurationComplete | Called when data is returned from requestDeviceConfigurationForInformation. | A String value is returned containing the Device Configuration information from the device |
| RequestPowerUpResetICCAPDUComplete | Called when data is returned from requestPowerUpResetICCWithWaitTime. | A String value is returned containing the ICC APDU data (if any) after the device has completed the Reset/Power Up |
| RequestChallengeAndSessionKeyRequestComplete | Called when data is returned from requestChallengeAndSessionForInformation. | A String value is returned containing the Challenge and Session Key from the device |
| CardRequestComplete | Called when data is returned from requestCard. | A CARD DATA INFO object is returned containing all of the necessary card data |
| RequestICCAPDUComplete | Called when data is returned from requestICCAPDUForInformation. | An object with two attributes: operationStatus (A String value is returned for the operation status) and cardStatus (A String value is returned for the card status) |
| RequestSetEMVTagsComplete | Called when data is returned from requestSetEMVTagsWithTagType. | A String value is returned containing the EMV Tag data |
| RequestSmartCardComplete | Called after sendAcquirerResponseWithResponse is completed. | A String value is returned containing the Smart Card batch data |
| SendAcquirerResponseComplete | Called when data is returned from sendAcquirerResponseWithResponse. | A String value is returned containing the Acquirer Response data |
| RequestUserDataEntryComplete | Called when data is returned from requestUserDataEntryWithWaitTime. | A USER DATA ENTRY object is returned containing the Encrypted Data Block and the MSR KSN. |

CardRequestComplete response example:
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