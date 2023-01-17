#include "blecharacteristicinfo.h"


BleCharacteristicInfo::BleCharacteristicInfo(const QLowEnergyCharacteristic& source, int index, QObject *parent) :
    QObject{parent},
    m_index{index},
    m_characteristic{source},
    m_description{source.name()}
{
    if (m_description.isEmpty()) {
        m_description = "<Unknown>";
    }
    qDebug() << m_description;
}
