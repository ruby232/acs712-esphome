#include "ACS712.h"

class ACS712Sensor : public PollingComponent {
   public:
    ACS712 *ACS = new ACS712(A0,4.67);
    Sensor *current_sensor = new Sensor();
    Sensor *power_sensor = new Sensor();

    ACS712Sensor() : PollingComponent(15000) {}

    void setup() override {
        ACS->autoMidPoint();
        ESP_LOGD("acs712", "MidPoint: %d", ACS->getMidPoint());
        ACS->setNoisemV(43);
        ESP_LOGD("acs712", "Noise mV: %d", ACS->getNoisemV());
    }

    void update() override {
        float average = 0;
        int count = 5;
        for (int i = 0; i < count; i++) {
            average += ACS->mA_AC();
        }
        float amps = average / count / 1000.0;
        float power = amps * 230;
        
        current_sensor->publish_state(amps);
        power_sensor->publish_state(power);
    }
};
