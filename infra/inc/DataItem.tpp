#include "DataModel.hpp"

template <typename T>
DataItem<T>::DataItem(DataItemId id)
    : data_(DataItems[id]),
      writable_(false)
{
}

template <typename T>
DataItem<T>::DataItem(DataItemId id, bool writable)
    : data_(DataItems[id]),
      writable_(writable)
{
}

template <typename T>
DataItem<T>::~DataItem()
{
}

template <typename T>
T DataItem<T>::get()
{
    return data_.value;
}

template <typename T>
Datagram &DataItem<T>::getDatagram()
{
    return data_;
}

template <typename T>
void DataItem<T>::set(T val)
{
    if (writable_)
    {
        if (val >= data_.min and val <= data_.max)
        {
            data_.value = val;
        }
    }
}

template <typename T>
void DataItem<T>::reset()
{
    set(data_.reset);
}
