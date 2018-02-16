#include "housecouncil.h"
#include "housecouncil_p.h"

#include <QDir>
#include <functional>

HouseCouncil *HouseCouncil::create(const QString &path, const QString &address, QObject *parent)
{
    QDir().mkpath(path);
    HouseCouncil *council = new HouseCouncil(path, parent);
    council->setAddress(address);
    return council;
}

HouseCouncil::HouseCouncil(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new HouseCouncilPrivate)
{
    Q_D(HouseCouncil);
    connect(this, &HouseCouncil::modifiedChanged, std::bind(&HouseCouncilPrivate::_q_onModifiedChanged, d, std::placeholders::_1));
    d->q_ptr = this;
    d->path = path;
    d->open();
}

HouseCouncil::~HouseCouncil()
{
}

QString HouseCouncil::address() const
{
    Q_D(const HouseCouncil);
    return d->address;
}

bool HouseCouncil::isModified() const
{
    Q_D(const HouseCouncil);
    return d->isModified;
}

void HouseCouncil::setAddress(const QString &address)
{
    Q_D(HouseCouncil);
    d->address = address;
    emit modifiedChanged(true);
}

void HouseCouncil::save()
{
    Q_D(HouseCouncil);
    d->save();
}
