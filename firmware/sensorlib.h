#ifndef SENSORLIB_H
#define SENSORLIB_H

#include <Arduino.h>

class DhtSensor {
    public:
        static const uint8_t EDGES = 84;

        enum class RecordStatus : uint8_t {
            ok,
            timeout,
            manyEdges
        };
        struct EdgeEvent {
            uint16_t offset; // since startTime
            uint8_t status; // after edge, high or low
        };
        struct DhtRecord {
            uint64_t startTime;
            uint64_t endTime;
            uint8_t edgeCount;
            RecordStatus status;
            EdgeEvent edges[EDGES];
        };

        explicit DhtSensor(uint8_t pin);
        void start();
        DhtRecord recordTransaction();
    
    private:
        uint8_t dhtPin;
        bool recordEdge(DhtRecord& record, uint8_t recordStatus);
};

#endif
