#pragma once

#include <QObject>
#include <QLowEnergyCharacteristic>


class BleCharacteristicInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString uuid READ uuid CONSTANT)
    Q_PROPERTY(QString description READ description CONSTANT)

public:
    explicit BleCharacteristicInfo(const QLowEnergyCharacteristic& source, int index = -1, QObject *parent = nullptr);

    QString uuid() const {
        return m_characteristic.uuid().toString();
    }

    QString description() const {
        return m_description;
    }

    QLowEnergyCharacteristic getServiceCharacteristic() const {
        return m_characteristic;
    }

private:
    int m_index;
    QLowEnergyCharacteristic m_characteristic;
    QString m_description;
};
