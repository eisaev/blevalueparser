#pragma once

#include <QObject>
#include <QBluetoothUuid>


class BleServiceInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString uuid READ uuid CONSTANT)
    Q_PROPERTY(QString description READ description CONSTANT)

public:
    explicit BleServiceInfo(const QBluetoothUuid& source, int index = -1, QObject *parent = nullptr);

    QString uuid() const {
        return m_uuid.toString();
    }

    QString description() const {
        return m_description;
    }

    QBluetoothUuid getServiceClassUuid() const {
        return m_uuid;
    }

private:
    int m_index;
    QBluetoothUuid m_uuid;
    QString m_description;
};
