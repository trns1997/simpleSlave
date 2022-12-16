#ifndef ARC_DATAITEM_HPP
#define ARC_DATAITEM_HPP

#include "DataModel.hpp"

class DataItem
{
public:
    DataItem(DataItemId id);
    DataItem(DataItemId id, bool writable);
    ~DataItem();

    int32_t get();
    Datagram& getDatagram();
    void set(int32_t val);
    void reset();


private:
    Datagram&   data_;
    bool        writable_ {false};
};

#endif
