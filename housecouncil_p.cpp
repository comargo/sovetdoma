#include "housecouncil_p.h"

HouseCouncilPrivate::HouseCouncilPrivate()
    : isModified(false)
{

}

bool HouseCouncilPrivate::open()
{
    Q_Q(HouseCouncil);
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
