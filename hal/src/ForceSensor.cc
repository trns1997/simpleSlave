#include "ForceSensor.h"

void ForceSensor::configure()
{
    free_ = &buffer0_;
    consume_ = &buffer1_;

    // Reset
    uint8_t resetConfig[] = {0x85, 0x00};
    uint32_t size = sizeof(resetConfig) / sizeof(resetConfig[0]);
    sendData(resetConfig, size, true);

    // Write Auto Seq Register
    uint8_t autoConfig[] = {0x01 << 0x1 | 0b1U, 0b00011111, 0x00};
    size = sizeof(autoConfig) / sizeof(autoConfig[0]);
    sendData(autoConfig, size, true);

    // Write Power Down Register
    uint8_t pwrDownConfig[] = {0x02 << 0x1 | 0b1U, 0b11100000, 0x00};
    size = sizeof(pwrDownConfig) / sizeof(pwrDownConfig[0]);
    sendData(pwrDownConfig, size, true);

    // Write Feature Register
    uint8_t feat1Config[] = {0x03 << 0x1 | 0b1U, 0b00 << 6 | 0b0 << 4 | 0b001 << 0, 0x00};
    size = sizeof(feat1Config) / sizeof(feat1Config[0]);
    sendData(feat1Config, size, true);

    uint8_t feat2Config[] = {0x05 << 0x1 | 0b1U, 0b0101, 0x00};
    size = sizeof(feat2Config) / sizeof(feat2Config[0]);
    sendData(feat2Config, size, true);

    uint8_t feat3Config[] = {0x06 << 0x1 | 0b1U, 0b0101, 0x00};
    size = sizeof(feat3Config) / sizeof(feat3Config[0]);
    sendData(feat3Config, size, true);

    uint8_t feat4Config[] = {0x07 << 0x1 | 0b1U, 0b0101, 0x00};
    size = sizeof(feat4Config) / sizeof(feat4Config[0]);
    sendData(feat4Config, size, true);

    uint8_t feat5Config[] = {0x08 << 0x1 | 0b1U, 0b0101, 0x00};
    size = sizeof(feat5Config) / sizeof(feat5Config[0]);
    sendData(feat5Config, size, true);

    uint8_t feat6Config[] = {0x09 << 0x1 | 0b1U, 0b0101, 0x00};
    size = sizeof(feat6Config) / sizeof(feat6Config[0]);
    sendData(feat6Config, size, true);

    // Auto mode enabled following a reset (AUTO_RST)
    uint8_t autoEnableConfig[] = {0x0A, 0x00};
    size = sizeof(autoEnableConfig) / sizeof(autoEnableConfig[0]);
    sendData(autoEnableConfig, size, true);
}

void ForceSensor::request_read()
{
    uint8_t txDataForceSensor[] = {0x00, 0x00, 0x00, 0x00};
    uint32_t tx_size = sizeof(txDataForceSensor) / sizeof(txDataForceSensor[0]);
    switch (forceSensorCnt_)
    {
    case 0:
    {
        txDataForceSensor[0] = 0xC0;
        break;
    }
    case 1:
    {
        txDataForceSensor[0] = 0xC4;
        break;
    }
    case 2:
    {
        txDataForceSensor[0] = 0xC8;
        break;
    }
    case 3:
    {
        txDataForceSensor[0] = 0xCC;
        break;
    }
    case 4:
    {
        txDataForceSensor[0] = 0xD0;
        break;
    }
    }
    sendData(txDataForceSensor, tx_size);
}

void ForceSensor::read()
{
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00};
    uint32_t size = sizeof(data) / sizeof(data[0]);
    readData(data, size);
    uint32_t forceSensorData = (data[2] << 8) + data[3];

    switch (forceSensorCnt_)
    {
    case 0:
    {
        fsData_.f0 = forceSensorData;
        forceSensorCnt_ = 1;
        break;
    }
    case 1:
    {
        fsData_.f1 = forceSensorData;
        forceSensorCnt_ = 2;
        break;
    }
    case 2:
    {
        fsData_.f2 = forceSensorData;
        forceSensorCnt_ = 3;
        break;
    }
    case 3:
    {
        fsData_.f3 = forceSensorData;
        forceSensorCnt_ = 4;
        break;
    }
    case 4:
    {
        fsData_.f4 = forceSensorData;
        forceSensorCnt_ = 0;
        continueRead_ = false;
        break;
    }
    }
    *free_ = fsData_;
    if (continueRead_)
    {
        request_read();
    }
}

ForceSensorData ForceSensor::getForceSensorData()
{
    continueRead_ = true;
    std::swap(free_, consume_);
    return *consume_;
}
