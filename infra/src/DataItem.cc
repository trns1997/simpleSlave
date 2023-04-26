#include "DataItem.h"

extern Datagram& datagram_(DataItemId id);

DataItem::DataItem(DataItemId id)
        :   data_(getDatagram(id)),
            writable_(false)
{}

DataItem::DataItem(DataItemId id, bool writable)
        :   data_(getDatagram(id)),
            writable_(writable)
{}

DataItem::~DataItem()
{}

int32_t DataItem::get()
{
    return data_.value;
}

Datagram& DataItem::getDatagram()
{
    return data_;
}


void DataItem::set(int32_t val)
{
    if (writable_)
    {
        if (val >= data_.min and val <= data_.max)
        {
            data_.value = val;
        }
    }
}

void DataItem::reset()
{
    set(data_.reset);
}
