#ifndef HOUSECOUNCIL_H
#define HOUSECOUNCIL_H

#include <QObject>

class HouseCouncilPrivate;

class HouseCouncil : public QObject
{
    Q_OBJECT
public:
    static HouseCouncil* create(const QString &path, const QString &address, QObject *parent);
    explicit HouseCouncil(const QString &path, QObject *parent = nullptr);
    ~HouseCouncil() override;

public:
    QString address() const;
    bool isModified() const;

signals:
    void modifiedChanged(bool isModified);

public slots:
    void setAddress(const QString &address);
    void save();

private:
    QScopedPointer<HouseCouncilPrivate> d_ptr;
    Q_DECLARE_PRIVATE(HouseCouncil)
};

#endif // HOUSECOUNCIL_H
