#include "DataModel.h"
#include "Fibre.h"

#include "SPI_Slave.h"

class IMUFibre : public Fibre
{
public:
    IMUFibre(const char *name,
             std::unique_ptr<SPI_Slave> imuObj,
             DataItemId imuGyroX,
             DataItemId imuGyroY,
             DataItemId imuGyroZ,
             DataItemId imuAccelX,
             DataItemId imuAccelY,
             DataItemId imuAccelZ,
             DataItemId imuTemp);

    ~IMUFibre() override;

    void Init() override;

    void Run() override;

    void Interrupt();

private:
    std::unique_ptr<SPI_Slave> boardIMU_;
    DataItem imuGyroX_;
    DataItem imuGyroY_;
    DataItem imuGyroZ_;
    DataItem imuAccelX_;
    DataItem imuAccelY_;
    DataItem imuAccelZ_;
    DataItem imuTemp_;
};
