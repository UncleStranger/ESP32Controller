#include "BluetoothSerial.h"
 
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif
 
// Bluetooth Serial Object (Handle)
BluetoothSerial SerialBT;
#define BT_DISCOVER_TIME  10000

static bool btScanSync = false;

void InitBluetooth(const char * btName, esp_spp_cb_t handler) 
{
    // Serial.println(btName);
    if(SerialBT.begin(btName)) // Bluetooth device name
    {
        //Serial.println("The device started, now you can pair it with bluetooth!");
        if (btScanSync) {
            Serial.println("Starting discover...");
            BTScanResults *pResults = SerialBT.discover(BT_DISCOVER_TIME);
            if (pResults)
                pResults->dump(&Serial);
            else
                Serial.println("Error on BT Scan, no result!");
        }
        // Attach The CallBack Function Definition To SerialBlutooth Events
        SerialBT.register_callback(&handler); // Attach The CallBack Function Definition To SerialBlutooth Events

        // If above line is in error, try the line below.
        // For Earlier versions of BluetoothSerial.h (SerialBT)
        //SerialBT.register_callback(handler); 
    }
}


