#ifndef INC_FIBRE_HPP_
#define INC_FIBRE_HPP_

#include <vector>
#include <memory>

class Fibre
{
public:
    Fibre(const char* name): name_(name)
    {}
    virtual ~Fibre() {}

    virtual void Init() = 0;
    virtual void Run() = 0;

    const char* getName()
    {
        return name_;
    }

private:
    const char* name_;

};

enum ThreadID
{
    THREAD_POLLED_ID,
    THREAD_1MS_ID,
    THREAD_10MS_ID
};


class FibreManager
{
public:
    static FibreManager& getInstance(ThreadID id);
    ~FibreManager();

    void Init();
    void Run();
    void Add(std::shared_ptr<Fibre> f);

private:
    FibreManager();
    std::vector<std::shared_ptr<Fibre>> fibres_;
};

#endif /* INC_FIBRE_HPP_ */
