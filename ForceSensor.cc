#include "ForceSensor.h"

void ForceSensor::configure()
{
    free_ = &buffer0_;
    consume_ = &buffer1_;
    // Reset
    std::vector<uint8_t> forceSensorConfig{0x85, 0x00};
    spi_.sendData(forceSensorConfig, true);

    // Write Auto Seq Register
    forceSensorConfig = std::vector<uint8_t>{0x01 << 0x1 | 0b1U, 0b00011111, 0x00};
    spi_.sendData(forceSensorConfig, true);

    // Write Power Down Register
    forceSensorConfig = std::vector<uint8_t>{0x02 << 0x1 | 0b1U, 0b11100000, 0x00};
    spi_.sendData(forceSensorConfig, true);

    // Write Feature Register
    forceSensorConfig = std::vector<uint8_t>{0x03 << 0x1 | 0b1U, 0b00 << 6 | 0b0 << 4 | 0b001 << 0, 0x00};
    spi_.sendData(forceSensorConfig, true);

    forceSensorConfig = std::vector<uint8_t>{0x05 << 0x1 | 0b1U, 0b0101, 0x00};
    spi_.sendData(forceSensorConfig, true);

    forceSensorConfig = std::vector<uint8_t>{0x06 << 0x1 | 0b1U, 0b0101, 0x00};
    spi_.sendData(forceSensorConfig, true);

    forceSensorConfig = std::vector<uint8_t>{0x07 << 0x1 | 0b1U, 0b0101, 0x00};
    spi_.sendData(forceSensorConfig, true);

    forceSensorConfig = std::vector<uint8_t>{0x08 << 0x1 | 0b1U, 0b0101, 0x00};
    spi_.sendData(forceSensorConfig, true);

    forceSensorConfig = std::vector<uint8_t>{0x09 << 0x1 | 0b1U, 0b0101, 0x00};
    spi_.sendData(forceSensorConfig, true);

    // Auto mode enabled following a reset (AUTO_RST)
    forceSensorConfig = std::vector<uint8_t>{0x0A, 0x00};
    spi_.sendData(forceSensorConfig, true);
}

void ForceSensor::read()
{
    std::vector<uint8_t> txDataForceSensor{0x00, 0x00, 0x00, 0x00};
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

    spi_.sendData(txDataForceSensor);
}

void ForceSensor::bufferizeForceSensorData()
{
    std::vector<uint8_t> readDataFS = getRawData();
    uint32_t forceSensorData = (readDataFS[2] << 8) + readDataFS[3];

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
        read();
    }
}

ForceSensorData ForceSensor::getForceSensorData()
{
    continueRead_ = true;
    std::swap(free_, consume_);
    return *consume_;
}