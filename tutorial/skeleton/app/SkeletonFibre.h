#include "Fibre.h"

////////////////////////////////////////////////////////////////
// Include stuff if needed (GPIO object, IMU object and etc.) //
////////////////////////////////////////////////////////////////

class SkeletonFibre : public Fibre
{
public:
    SkeletonFibre(const char *name);
    ~SkeletonFibre() override;

    void Init() override;

    void Run() override;

private:
};
