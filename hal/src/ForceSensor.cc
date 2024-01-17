#include "ForceSensor.h"

ForceSensor::ForceSensor(board::spi_identifier spi_name) : SPI_Slave(spi_name)
{
}

void ForceSensor::configure()
{
    static int step = 0;
    free_ = &buffer0_;
    consume_ = &buffer1_;

    uint8_t size = 0;
    switch (step)
    {
    case 0:
        // Reset
        config_[0] = 0x85;
        config_[1] = 0x00;
        size = 2;
        break;
    case 1:
        // Write Auto Seq Register
        config_[0] = 0x01 << 0x1 | 0b1U;
        config_[1] = 0b00011111;
        config_[2] = 0x00;
        size = 3;
        break;
    case 2:
        // Write Power Down Register
        config_[0] = 0x02 << 0x1 | 0b1U;
        config_[1] = 0b11100000;
        config_[2] = 0x00;
        size = 3;
        break;
    case 3:
        // Write Feature Register
        config_[0] = 0x03 << 0x1 | 0b1U;
        config_[1] = 0b00 << 6 | 0b0 << 4 | 0b001 << 0;
        config_[2] = 0x00;
        size = 3;
        break;
    case 4:
        config_[0] = 0x05 << 0x1 | 0b1U;
        config_[1] = 0b0101;
        config_[2] = 0x00;
        size = 3;
        break;
    case 5:
        config_[0] = 0x06 << 0x1 | 0b1U;
        config_[1] = 0b0101;
        config_[2] = 0x00;
        size = 3;
        break;
    case 6:
        config_[0] = 0x07 << 0x1 | 0b1U;
        config_[1] = 0b0101;
        config_[2] = 0x00;
        size = 3;
        break;
    case 7:
        config_[0] = 0x08 << 0x1 | 0b1U;
        config_[1] = 0b0101;
        config_[2] = 0x00;
        size = 3;
        break;
    case 8:
        config_[0] = 0x09 << 0x1 | 0b1U;
        config_[1] = 0b0101;
        config_[2] = 0x00;
        size = 3;
        break;
    case 9:
        // Auto mode enabled following a reset (AUTO_RST)
        config_[0] = 0x0A;
        config_[1] = 0x00;
        size = 2;
        state_ = INITIALIZED;
        break;
    }
    step++;
    sendData(config_, size);
}

void ForceSensor::checkConfiguration()
{
    uint8_t readConfig[3] = {};
    uint8_t size = 3;
    readData(readConfig, size);
    if (readConfig[2] != config_[1])
    {
        state_ = ERROR;
    }
}

void ForceSensor::request_read()
{
    uint8_t txData[] = {0x00, 0x00, 0x00, 0x00};
    uint32_t tx_size = sizeof(txData) / sizeof(txData[0]);
    switch (channelCnt_)
    {
    case 0:
    {
        txData[0] = 0xC0;
        break;
    }
    case 1:
    {
        txData[0] = 0xC4;
        break;
    }
    case 2:
    {
        txData[0] = 0xC8;
        break;
    }
    case 3:
    {
        txData[0] = 0xCC;
        break;
    }
    case 4:
    {
        txData[0] = 0xD0;
        break;
    }
    }
    sendData(txData, tx_size);
}

void ForceSensor::read()
{
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00};
    uint32_t size = sizeof(data) / sizeof(data[0]);
    readData(data, size);
    int16_t channelData = static_cast<int16_t>((data[2] << 8) + data[3]);

    switch (channelCnt_)
    {
    case 0:
    {
        channelData_[0] = channelData;
        channelCnt_ = 1;
        break;
    }
    case 1:
    {
        channelData_[1] = channelData;
        channelCnt_ = 2;
        break;
    }
    case 2:
    {
        channelData_[2] = channelData;
        channelCnt_ = 3;
        break;
    }
    case 3:
    {
        channelData_[3] = channelData;
        channelCnt_ = 4;
        break;
    }
    case 4:
    {
        channelData_[4] = channelData;
        channelCnt_ = 0;
        continueRead_ = false;
        break;
    }
    }
    *free_ = channelData_;
    if (continueRead_)
    {
        request_read();
    }
}

int16_t *ForceSensor::getData()
{
    continueRead_ = true;
    std::swap(free_, consume_);
    return *consume_;
}
