#include "DataModel.h"
#include "Fibre.h"
#include "LSM6DSM.h"

class IMUFibre : public Fibre
{
public:
    IMUFibre(const char *name,
             board::spi_identifier spi_name,
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
    LSM6DSM boardIMU_;
    DataItem imuGyroX_;
    DataItem imuGyroY_;
    DataItem imuGyroZ_;
    DataItem imuAccelX_;
    DataItem imuAccelY_;
    DataItem imuAccelZ_;
    DataItem imuTemp_;
};
