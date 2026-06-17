# ESP-NOW Smart Switch
Real-time Wireless Smart Switch Network using ESP-NOW on ESP32/ESP8266

---

## Overview

This project implements a real-time wireless control network based on the ESP-NOW protocol using ESP32/ESP8266 microcontrollers.

The system is designed for smart switch and embedded IoT applications where:
- low latency,
- lightweight communication,
- low cost,
- and decentralized wireless control

are required.

Unlike traditional WiFi smart switches that depend heavily on cloud communication, this system allows direct peer-to-peer communication between nodes through ESP-NOW while still supporting optional cloud connectivity through Blynk.

The architecture is inspired by commercial smart home systems such as:
- Zigbee Smart Switch
- Aqara
- Hunonic Switch
- Tuya Smart Switch

but implemented using ESP32/ESP8266 hardware and ESP-NOW protocol.

---

## Objectives

- Build a real-time wireless control network.
- Reduce latency compared to cloud-only systems.
- Support multiple relay nodes.
- Implement ACK and retransmission mechanisms.
- Evaluate communication quality and reliability.
- Study the feasibility of ESP-NOW for smart home applications.

---

## System Architecture

```text
Mobile App / Blynk Cloud
            |
         WiFi Router
            |
      ESP32 Gateway
            |
      =================
      ||    ESP-NOW  ||
      =================
        |      |      
     Relay1 Relay2 
```

### Topology
- Star topology
- Optional multi-hop repeater extension

---

## Features

### Current Features
- ESP-NOW peer-to-peer communication
- Real-time ON/OFF control
- Multi-node support
- Relay control
- Device addressing
- ACK response
- Retry transmission
- WiFi + ESP-NOW coexistence
- Blynk integration
- RSSI monitoring

### Future Features
- ESP-NOW mesh / multi-hop
- OTA firmware update
- AES encryption
- Local web dashboard
- MQTT integration
- Node-RED monitoring

---

## Technologies Used

| Category | Technology |
|---|---|
| MCU | ESP32 / ESP8266 |
| Wireless Protocol | ESP-NOW |
| Cloud Platform | Blynk |
| Programming Language | C++ |
| IDE | Arduino IDE / PlatformIO |
| Communication | WiFi + ESP-NOW |
| Version Control | Git + GitHub |

---

## Project Structure

```text
espnow-smart-switch/
│
├── firmware/
│   ├── gateway/
│   ├── relay_node/
│   └── repeater_node/
│
├── hardware/
│   ├── schematic/
│   └── pcb/
│
├── docs/
│   ├── report/
│   └── images/
│
├── README.md
└── .gitignore
```

---

## Hardware Requirements

### Gateway
- ESP32 DevKit V1
- WiFi connection
- External power supply

### Relay Node
- ESP8266 
- Relay module
- External power supply

---

## Communication Flow

1. User sends command from mobile application.
2. Gateway receives command through WiFi/Blynk.
3. Gateway forwards command using ESP-NOW.
4. Relay node executes command.
5. Relay node sends response.
6. Gateway updates device status.

---

## Performance Evaluation

The following parameters are evaluated:

- End-to-end latency
- Response time
- Packet delivery ratio
- Packet loss
- RSSI vs distance
- Power consumption
- Multi-hop performance

---

## Experimental Metrics

| Parameter | Target |
|---|---|
| Control latency | < 50 ms |
| Response | < 50 ms |
| Packet success rate | > 99% |
| Indoor range | > 20 m |
| Outdoor range | > 100 m |

---

## Advantages

- Low communication latency
- Lightweight protocol
- No router dependency between nodes
- Low deployment cost
- Suitable for embedded systems
- Real-time communication

---

## Limitations

- Limited ESP-NOW payload size
- Channel synchronization required
- Not a native full mesh protocol
- Limited scalability compared to Zigbee

---

## Comparison with Commercial Systems

| System       | Protocol  | Gateway  | Mesh         | Cloud    |
|--------------|-----------|----------|--------------|----------|
| Zigbee       | Zigbee    | Yes      | Yes          | Optional |
| Tuya WiFi    | WiFi      | No       | No           | Yes      |
| This Project | ESP-NOW   | Yes      | Experimental | Optional |

---

## Research Direction

Potential future research:
- ESP-NOW mesh routing
- Dynamic node discovery
- Sleep scheduling
- Energy optimization
- Industrial wireless control
- Hybrid ESP-NOW + MQTT systems

---

## Team Members

| Member | Responsibility |
|---|---|
| Member 1 |             |


---

## References

1. Espressif ESP-NOW Documentation  
2. ESP-IDF Programming Guide  
3. Blynk IoT Platform  
4. Zigbee Smart Home Architecture  
5. Real-time Wireless Embedded Systems Research

---

## License

This project is developed for educational and research purposes.
---

## Author
Embedded Systems Project  
Faculty of Electrical and Electronics Engineering

2026
