#include "ESPNOW_Slave.h"
#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>

SoftwareSerial pzemSerial(PZEM_RX, PZEM_TX);
PZEM004Tv30 pzem(pzemSerial);

unsigned long lastReconnectAttempt = 0;
unsigned long lastSensorSend = 0;
float lastCurrent = -100;
float currentLimit = CURRENT_LIMIT_VALUE;
bool overCurrentTrip = false;

void requestEnergyReset() {
    pzem.resetEnergy();
    Serial.println("Energy Reset");
}

float voltage ;
float current ;
float power;
float energy;

void sendAllData() {
    if (isnan(voltage)) {
        Serial.println("PZEM Error");
        return;
    }

    uint8_t relayState = digitalRead(relay1);
        if (abs(current - lastCurrent) > 0.05) {
        // Gateway: vpin = data + 4*ID → Slave3: V13..V16
        espSlave.sendData(DATA_RELAY,   relayState);
        espSlave.sendData(DATA_CURRENT, current);
        espSlave.sendData(DATA_POWER,   power);
        espSlave.sendData(DATA_ENERGY,  energy);

        Serial.printf("RelayState:%d  | V: %.2fV  | I: %.2fA | P: %.1fW | E: %.3fkWh\n",
                      relayState, voltage, current, power, energy);
        lastCurrent = current;
      }

}

void setup() {
    Serial.begin(SERIAL_BAUD);
    delay(50);
    Serial.printf("\n =========ESPNOW SLAVE %d======== \n", ID);

    pinMode(relay1, OUTPUT);
    digitalWrite(relay1, HIGH);

    espSlave.connectWiFi();
    yield();
    delay(50);
    WiFi.setAutoReconnect(true);

    espSlave.begin();
    espSlave.addPeer(serverMAC);
    pzemSerial.begin(9600);
    IPAddress addr = pzem.readAddress();
    Serial.printf("Address: %d.%d.%d.%d\n",
              addr[0], addr[1], addr[2], addr[3]);
}

void loop() {
    voltage = pzem.voltage();
    current = pzem.current();
    power = pzem.power();
    energy = pzem.energy();
    if (millis() - lastSensorSend > 1000) {
        sendAllData();
        lastSensorSend = millis();
    }
    if(current > currentLimit)
   {
    Serial.printf( "Over Current %.2fA > %.2fA\n",current,currentLimit );
    digitalWrite(relay1, LOW);
    espSlave.sendData(DATA_RELAY,0);
    }

}
