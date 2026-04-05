#include "sensorlib.h"

DhtSensor::DhtSensor(uint8_t pin) : dhtPin(pin) {}

void DhtSensor::start() {
    pinMode(dhtPin, INPUT_PULLUP);
}

bool DhtSensor::recordEdge(DhtRecord& record, uint8_t recordStatus) {
    if (record.edgeCount >= EDGES) {
        // stop if too many edges recorded
        record.status = RecordStatus::manyEdges;
        return false;
    }

    // record new edge
    uint32_t timeNow  = micros();
    record.edges[record.edgeCount].offset = static_cast<uint16_t>(timeNow - record.startTime);
    record.edges[record.edgeCount].status = recordStatus;
    record.edgeCount++;
    return true;
}

DhtSensor::DhtRecord DhtSensor::recordTransaction() {
    DhtRecord record{};
    record.startTime = micros();
    record.status = RecordStatus::ok;

    // mcu gives low start signal at least 1 ms
    pinMode(dhtPin, OUTPUT);
    digitalWrite(dhtPin, LOW);
    delayMicroseconds(1000);
    pinMode(dhtPin, INPUT_PULLUP);

    // collect 
    uint8_t firstStatus = digitalRead(dhtPin);
    uint32_t guardTime = micros();

    while(true) {
        uint8_t secondStatus = digitalRead(dhtPin);

        if (secondStatus != firstStatus) {
            // edge happening, set new status as current status
            firstStatus = secondStatus;

            // record the edge, function does check for edge count
            if (!recordEdge(record, firstStatus)) {
                break;
            }
            guardTime = micros();

            if (record.edgeCount >= EDGES) {
                break;
            }
        }
        if ((micros() - guardTime) > 255) {
            record.status = RecordStatus::timeout;
            break;
        }
    }
    record.endTime = micros();
    return record;
}
