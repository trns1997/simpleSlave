#include "Fibre.hpp"
#include "LSM6DSM.h"

class IMUFibre : public Fibre
{
public:
    IMUFibre(const char *name, board::spi_identifier spi_name);
    ~IMUFibre() override;

    void Init() override;

    void Run() override;

    void Interrupt();

private:
    LSM6DSM boardIMU_;
};
