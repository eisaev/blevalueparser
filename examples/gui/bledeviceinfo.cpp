#include "bledeviceinfo.h"


BleDeviceInfo::BleDeviceInfo(const QBluetoothDeviceInfo &source, size_t index, QObject *parent) :
    QObject{parent},
    m_index{index},
    m_device{source}
{
    //
}

bool BleDeviceInfo::update(const QBluetoothDeviceInfo &source)
{
#ifdef Q_OS_DARWIN
    // workaround for Core Bluetooth
    if (source.deviceUuid() == m_device.deviceUuid())
#else
    if (source.address() == m_device.address())
#endif
    {
        m_device = source;
        return true;
    }

    return false;
}
