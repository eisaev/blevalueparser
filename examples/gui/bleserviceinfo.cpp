#include "bleserviceinfo.h"


BleServiceInfo::BleServiceInfo(const QBluetoothUuid &source, size_t index, QObject *parent) :
    QObject{parent},
    m_index{index},
    m_uuid{source}
{
    // 0xSSSS
    quint32 serviceClassUuidShort = source.toUInt32();
    qDebug() << serviceClassUuidShort;
    // 0000SSSS-0000-1000-8000-00805f9b34fb
    auto serviceClassUuid = static_cast<QBluetoothUuid::ServiceClassUuid>(serviceClassUuidShort);
    m_description = source.serviceClassToString(serviceClassUuid);
    if (m_description.isEmpty())
    {
        m_description = "<Unknown>";
    }
    qDebug() << m_description;
}
