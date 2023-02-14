#pragma once

#include <QObject>
#include <QBluetoothUuid>


class BleServiceInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString uuid READ uuid CONSTANT)
    Q_PROPERTY(QString description READ description CONSTANT)

public:
    explicit BleServiceInfo(const QBluetoothUuid& source, size_t index, QObject *parent = nullptr);

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
    size_t m_index;
    QBluetoothUuid m_uuid;
    QString m_description;
};
