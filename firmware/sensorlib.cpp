# include sensorlib.h

void DhtSensor::DhtSensor(uint8_t pin) : dhtPin(pin) {}

void DhtSensor::start() {
    pinMode(dhtPin, INPUT_PULLUP);
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
}




