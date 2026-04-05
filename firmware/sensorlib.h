
class Sensorlib {
    public:
        static const uint8_t EDGES = 84;

        enum class CaptureStatus : uint8_t {
            ok,
            timeout,
            manyedges
        }
        struct EdgeEvent {
            uint16_t offset; // since startTime
            uint8_t status; // after edge, high or low
        }
        struct DhtCapture {
            uint64_t startTime;
            uint64_t endTime;
            uint8_t edgeCount;
            CaptureStatus captureStatus;
            EdgeEvent edges[EDGES]
        }

        explicit DhtSensor(uint8_t pin);
        void start();
        DhtCapture capture();
    
    private:
        uint8_t dhtPin;
        // functions
}
