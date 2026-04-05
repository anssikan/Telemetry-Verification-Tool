# include sensorlib.h

void DhtSensor::DhtSensor(uint8_t pin) : dhtPin(pin) {}

void DhtSensor::start() {
    pinMode(dhtPin, INPUT_PULLUP);
}

bool DhtSensor::record(DhtCapture& record, uint8_t newLevel) {
    if (cap.edgeCount >= EDGES) {
        // stop if too many edges recorded
        record.status = CaptureStatus::manyedges;
        record.captureEndUs = micros();
        return false;
    }

    // record new edge
    uint32_t timeNow  = micros();
    record.edges[record.edgeCount].offset = static_cast<uint16_t>(timeNow - record.startTime);
    record.edges[record.edgeCount].level = newLevel;
    record.edgeCount++;
    return true;
}

DhtSensor::DhtCapture DhtSensor::capture() {
    DhtCapture record{};
    record.startTime = micros();
    record.status = CaptureStatus::ok;

    // mcu gives low start signal at least 1 ms
    pinMode(dhtPin, OUTPUT);
    digitalWrite(dhtPin, LOW);
    delayMicroseconds(1000);
    pinMode(dhtPin, INPUT_PULLUP);

    // collect 
    uint8_t firstLevel = digitalRead(dhtPin);
    uint32_t guardTime = micros();

    while(true) {
        uint8_t secondLevel = digitalRead(dhtPin);

        if (secondLevel != firstLevel) {
            // edge happening
            firstLevel = secondLevel;

            // record
        }

    }





    return record;
}




