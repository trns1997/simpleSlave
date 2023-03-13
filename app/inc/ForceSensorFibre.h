#include "Fibre.hpp"
#include "ForceSensor.h"

class ForceSensorFibre : public Fibre
{
public:
    ForceSensorFibre(const char *name, board::spi_identifier spi_name);
    ~ForceSensorFibre() override;

    void Init() override;

    void Run() override;

    void Interrupt();

private:
    ForceSensor forceSensors_;
};
