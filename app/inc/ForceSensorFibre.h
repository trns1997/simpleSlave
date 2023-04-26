#include "DataModel.h"
#include "Fibre.h"
#include "ForceSensor.h"

class ForceSensorFibre : public Fibre
{
public:
    ForceSensorFibre(const char *name,
                     board::spi_identifier spi_name,
                     DataItemId FS0,
                     DataItemId FS1,
                     DataItemId FS2,
                     DataItemId FSVref,
                     DataItemId FS3);
    ~ForceSensorFibre() override;

    void Init() override;

    void Run() override;

    void Interrupt();

private:
    ForceSensor forceSensors_;
    DataItem FS0_;
    DataItem FS1_;
    DataItem FS2_;
    DataItem FSVref_;
    DataItem FS3_;
};
