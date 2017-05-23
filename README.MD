**Magtek Plugin**

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
magtek.getDiscoveredPeripherals(q,q); //Response example: '{name: "DPMini040F16100D", state: "disconnected", identifier: "C1553D35-CCDC-4CC7-A600-58E2F82DAD4E"}'
magtek.connectToBLEReader(q,q,"C1553D35-CCDC-4CC7-A600-58E2F82DAD4E"); //Device should start
magtek.requestCard(q,q)
//After swiping the card, the `CardRequestComplete` event contains the card information
```
# API Reference

**you need to call init function before using any other method**

1. Functions
  1. init(callback, BDK)
  2. Device connection functions
    2. startScanningForPeripherals(success, error)
      2. stopScanningForPeripherals(success, error)
      2. getDiscoveredPeripherals(success, error)
      2. isDeviceOpened(success, error)
      2. isDeviceConnected(success, error)
      2. getConnectedPeripheral(success, error)
      2. connectToBLEReader(success, error, identifier)
      2. disconnectFromBLEReader(success, error)
  3. Device operation functions
      3. deviceReset(success, error)
      3. cancelOperation(success, error)
  4. Transaction functions
      4. requestCard(success, error)
      4. requestConfirmAmount(success, error)
      4. getLastTransactionInfo(success, error)
      4. requestSmartCardTransaction(success, error, amount)
2. Events
  2. Card
  2. Error
  2. BINDataReceived
  2. DataArriveComplete
  2. ACKStatusReceived
  2. ATRRequestComplete
  2. SendICCAPDUComplete
  2. SetCAPublicKeyComplete
  2. PINRequestComplete
  2. KeyRequestComplete
  2. BypassPinCommandComplete
  2. SendCommandTimeOutComplete
  2. RequestPowerUpResetICCComplete
  2. OperationStatusReceived
  2. CardRequestComplete
  2. RequestICCAPDUComplete
  2. RequestSmartCardComplete
  2. RequestSetEMVTagsComplete
  2. RequestUserDataEntryComplete

**Functions**

## init
The `init(callback, BDK)` function sets the BDK ([Base Derivation Key](https://en.wikipedia.org/wiki/Derived_unique_key_per_transaction#Keys)) and initializes the magtek instance.

**you need to set the BDK before using any other method**

### Parameters
#### callback
function(err,res){}

#### BDK
The [Base Derivation Key](https://en.wikipedia.org/wiki/Derived_unique_key_per_transaction#Keys) is the unique company fixed key 

## startScanningForPeripherals
## stopScanningForPeripherals
## getDiscoveredPeripherals
## isDeviceOpened
## isDeviceConnected
## getConnectedPeripheral
## connectToBLEReader
## disconnectFromBLEReader
## deviceReset
## cancelOperation
## requestCard
## requestConfirmAmount
## getLastTransactionInfo
## requestSmartCardTransaction

**Events**
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
##OperationStatusReceived
Data is a String

Eg: "00"

##Card
Data is a String

Eg: "cardDataAvailable"

##CardRequestComplete
Data is a JSON

Eg:
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