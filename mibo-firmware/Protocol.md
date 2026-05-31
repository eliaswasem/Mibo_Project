# ESP ↔ Teensy UART Protocol (Binary Control Link)

---

# Packet Format

```text
[START][CMD][DATA...][CRC8]
```


| Field | Size | Description |
| :--- | :--- | :--- |
| **START** | 1 Byte | Fixed synchronization preamble (`0xAA`) |
| **CMD** | 1 Byte | Command ID (Maps directly to static payload sizes) |
| **DATA** | N Bytes | Payload data (Strictly defined per CMD) |
| **CRC8** | 1 Byte | Trailing Dallas/Maxim check token over `CMD` and `DATA` |

---

# Core Rules

- `START` is always `0xAA`.
- The transmission footprint length is implicit, derived completely from the `CMD` ID lookup.
- `CRC8` protects the link stream against random bit flips caused by EMI.
- Calculation window starts exactly at the `CMD` byte and covers all `DATA` fields.

---

# Commands

## SPEED
- **CMD:** `0x01`
- **TYPE:** `uint8_t`
- **DATA SIZE:** 1 Byte
- **TOTAL FRAME SIZE:** 4 Bytes (`START` + `CMD` + 1B Payload + `CRC8`)

### Example (SPEED = 125 / 0x7D)
- **Packet:** `AA 01 7D 5B` (CRC-8 computed from: 01 7D)

---

## STOP
- **CMD:** `0x02`
- **TYPE:** None
- **DATA SIZE:** 0 Bytes
- **TOTAL FRAME SIZE:** 3 Bytes (`START` + `CMD` + `CRC8`)

### Example
- **Packet:** `AA 02 62` (CRC-8 computed from: 02)

---

## GOTO (lat, lon)
- **CMD:** `0x10`
- **TYPE:** `int32_t` (Latitude) + `int32_t` (Longitude)
- **DATA SIZE:** 8 Bytes
- **TOTAL FRAME SIZE:** 11 Bytes (`START` + `CMD` + 8B Payload + `CRC8`)

### Example
- **Packet:** `AA 10 [LAT 4B] [LON 4B] [CRC8]`

---

# Receiver Logic (Deterministic State Machine)

```text
[WAIT_START] ──(0xAA)──> [READ_CMD] ──(Valid CMD)──> [READ_PAYLOAD] ──(Full Payload)──> [READ_CRC]
     ▲                         │                            │                               │
     └─────────(Invalid)───────┴───────────(Unknown CMD)────┴─────────(Done / Error)────────┘
```

1. **WAIT_START:** Scan incoming bytes until the magic sync preamble `0xAA` is caught.
2. **READ_CMD:** Extract the instruction identifier. Query the size lookup engine. If the command ID is unregistered (returns -1), abort and fallback to step 1.
3. **READ_PAYLOAD:** Read the exact number of fixed payload bytes bound to the validated command ID. If the payload size requirement is 0, progress immediately to step 4.
4. **READ_CRC:** Compare the trailing validation byte from the stream against the running computed software CRC matrix fingerprint.
    - **Match:** Forward the uncorrupted frame payload data to the main execution controller.
    - **Mismatch:** Quietly drop the frame to preserve control line integrity.
5. Fallback tracking to step 1.

---

# Encoder Usage

```cpp
// Serializes and appends the hardware check token automatically
const uint8_t* packet = PacketEncoder::encode(Packet::SPEED, &SpeedPayload{150}, sizeof(SpeedPayload));
PacketWriter::write_packet(packet);
```
