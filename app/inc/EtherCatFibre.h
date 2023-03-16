#include "Fibre.h"

class EtherCatFibre : public Fibre
{
public:
    EtherCatFibre(const char *name);
    ~EtherCatFibre() override;

    void Init() override;

    void Run() override;

private:
};
