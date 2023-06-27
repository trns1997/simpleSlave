#include "Fibre.h"
#include "UART.h"

class UARTFibre : public Fibre
{
public:
    UARTFibre(const char *name);
    ~UARTFibre() override;

    void Init() override;

    void Run() override;

private:
    UART uart_{board::UART};
};
