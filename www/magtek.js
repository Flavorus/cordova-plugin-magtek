var exec = require('cordova/exec');

module.exports = {
	getDiscoveredPeripherals: function (success, error) {
        exec(success, error, "CDVMagtek", "getDiscoveredPeripherals", []);
    },
    startScanningForPeripherals: function (success, error) {
        exec(success, error, "CDVMagtek", "startScanningForPeripherals", []);
    },
    stopScanningForPeripherals: function (success, error) {
        exec(success, error, "CDVMagtek", "stopScanningForPeripherals", []);
    },
    isDeviceOpened: function (success, error) {
        exec(success, error, "CDVMagtek", "isDeviceOpened", []);
    },
    isDeviceConnected: function (success, error) {
        exec(success, error, "CDVMagtek", "isDeviceConnected", []);
    },
    getConnectedPeripheral: function (success, error) {
        exec(success, error, "CDVMagtek", "getConnectedPeripheral", []);
    },
    connectToBLEReader: function (success, error, identifier) {
        exec(success, error, "CDVMagtek", "connectToBLEReader", [identifier]);
    },
    init: function (callback, bkn) {
    	var connected = false;
    	exec(function (result) {
    		if (!connected) {
    			callback(null, result);
    			connected = true;
    		} else {
                console.log(result);
    			cordova.fireWindowEvent("magtekEvent", result);
    		}
    	},
    	function (error) {
    		callback(error)
    	}, 'CDVMagtek', 'init', [bkn]);
    },
    disconnectFromBLEReader: function (success, error) {
    	exec(success, error, "CDVMagtek", "disconnectFromBLEReader", []);
    },
    setAmount: function (success, error, amount) {
    	exec(success, error, "CDVMagtek", "setAmount", [amount]);
    },
    requestCard: function (success, error) {
    	exec(success, error, "CDVMagtek", "requestCard", []);
    },
    requestConfirmAmount: function (success, error) {
    	exec(success, error, "CDVMagtek", "requestConfirmAmount", []);
    },
    cancelOperation: function (success, error) {
    	exec(success, error, "CDVMagtek", "cancelOperation", []);
    },
    deviceReset: function (success, error) {
    	exec(success, error, "CDVMagtek", "deviceReset", []);
    },
    getLastTransactionInfo: function (success, error) {
    	exec(success, error, "CDVMagtek", "getLastTransactionInfo", []);
    },
    requestSmartCardTransaction: function (success, error, amount) {
    	exec(success, error, "CDVMagtek", "requestSmartCardTransaction", [amount]);
    }
};