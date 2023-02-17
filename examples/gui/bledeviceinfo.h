#pragma once

#include <QObject>
#include <QBluetoothUuid>
#include <QBluetoothAddress>
#include <QBluetoothDeviceInfo>


class BleDeviceInfo : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString address READ address CONSTANT)
    Q_PROPERTY(qint16 rssi READ rssi CONSTANT)

public:
    explicit BleDeviceInfo(const QBluetoothDeviceInfo& source, size_t index, QObject *parent = nullptr);

    QString name() const {
        return m_device.name();
    }

    QString address() const {
#ifdef Q_OS_DARWIN
        // workaround for Core Bluetooth
        return m_device.deviceUuid().toString();
#else
        return m_device.address().toString();
#endif
    }

    qint16 rssi() const {
        return m_device.rssi();
    }

    QBluetoothDeviceInfo getDeviceInfo() const {
        return m_device;
    }

    bool update(const QBluetoothDeviceInfo &source);

private:
    size_t m_index;
    QBluetoothDeviceInfo m_device;
};
