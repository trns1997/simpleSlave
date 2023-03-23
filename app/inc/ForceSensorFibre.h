#include "DataModel.h"
#include "Fibre.h"
#include "ForceSensor.h"

class ForceSensorFibre : public Fibre
{
public:
    ForceSensorFibre(const char *name, board::spi_identifier spi_name, DataItemId *dataItems);
    ~ForceSensorFibre() override;

    void Init() override;

    void Run() override;

    void Interrupt();

private:
    ForceSensor forceSensors_;
    DataItemId *dataItems_;
};
