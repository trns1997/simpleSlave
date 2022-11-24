#ifndef ForceSensor_H_
#define ForceSensor_H_

#include <vector>
#include "XMC_Slave.h"

struct ForceSensorData
{
    uint32_t f0;
    uint32_t f1;
    uint32_t f2;
    uint32_t f3;
    uint32_t f4;
};

class ForceSensor : public XMC_Slave
{
public:
    ForceSensor() = default;
    ~ForceSensor() = default;

    void configure() override;
    void read() override;
    void bufferizeForceSensorData();
    ForceSensorData getForceSensorData();

private:
    uint16_t forceSensorCnt_{0};
    ForceSensorData fsData_{0};
    ForceSensorData buffer0_{0};
    ForceSensorData buffer1_{0};
    ForceSensorData *free_;
    ForceSensorData *consume_;
    bool continueRead_{true};
};

#endif
