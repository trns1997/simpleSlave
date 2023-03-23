#include "DataModel.h"
#include "Fibre.h"
#include "LSM6DSM.h"

class IMUFibre : public Fibre
{
public:
    IMUFibre(const char *name, board::spi_identifier spi_name, DataItemId *dataItems);
    ~IMUFibre() override;

    void Init() override;

    void Run() override;

    void Interrupt();

private:
    LSM6DSM boardIMU_;
    DataItemId *dataItems_;
};
