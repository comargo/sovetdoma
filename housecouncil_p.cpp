#include "housecouncil_p.h"

#include <QFileInfo>

HouseCouncilPrivate::HouseCouncilPrivate()
    : isModified(false)
    , ownersRegistry(nullptr)
{

}

bool HouseCouncilPrivate::open()
{
    Q_Q(HouseCouncil);

    ownersRegistry = new QxtCsvModel(q);
    ownersRegistry->setHeaderData(QStringList({"flat", "name", "document", "part_in_flat", "part_in_house", "active"}));
    if(QFileInfo::exists(path + "/ownersregistry.csv")) {
        ownersRegistry->setSource(path + "/ownersregistry.csv");
    }

    emit q->modifiedChanged(false);
    return true;
}

bool HouseCouncilPrivate::save()
{
    Q_Q(HouseCouncil);
    emit q->modifiedChanged(false);

    return true;
}

void HouseCouncilPrivate::_q_onModifiedChanged(bool _isModified)
{
    isModified = _isModified;
}
