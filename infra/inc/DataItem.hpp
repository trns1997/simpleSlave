#ifndef ARC_DATAITEM_HPP
#define ARC_DATAITEM_HPP

#include "DataModel.hpp"

template <typename T>
class DataItem
{
public:
    DataItem(DataItemId id);
    DataItem(DataItemId id, bool writable);
    ~DataItem();

    T get();
    Datagram &getDatagram();
    void set(T val);
    void reset();

private:
    Datagram &data_;
    bool writable_{false};
};

#include "DataItem.tpp"

#endif