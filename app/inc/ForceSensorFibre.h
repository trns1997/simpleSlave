#include "Fibre.hpp"
#include "ForceSensor.h"

class ForceSensorFibre : public Fibre
{
public:
    ForceSensorFibre(const char *name);
    ~ForceSensorFibre() override;

    void Init() override;

    void Run() override;

    void Interrupt();

private:
    ForceSensor forceSensors_{board::SPI_FS};
};
