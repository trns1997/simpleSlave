#include "DataModel.h"
#include "Fibre.h"
#include "BMI088.h"

class BMI088Fibre : public Fibre
{
public:
    BMI088Fibre(const char *name,
             board::spi_identifier spi_name,
             DataItemId imuGyroX,
             DataItemId imuGyroY,
             DataItemId imuGyroZ,
             DataItemId imuAccelX,
             DataItemId imuAccelY,
             DataItemId imuAccelZ,
             DataItemId imuTemp);

    ~BMI088Fibre() override;

    void Init() override;

    void Run() override;

    void Interrupt();

private:
    BMI088 boardIMU_;
    DataItem imuGyroX_;
    DataItem imuGyroY_;
    DataItem imuGyroZ_;
    DataItem imuAccelX_;
    DataItem imuAccelY_;
    DataItem imuAccelZ_;
    DataItem imuTemp_;
};
