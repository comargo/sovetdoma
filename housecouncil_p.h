#ifndef HOUSECOUNCIL_P_H
#define HOUSECOUNCIL_P_H

#include "housecouncil.h"

class HouseCouncilPrivate
{
public:
    HouseCouncilPrivate();

    // Fields
    bool isModified;
    QString path;
    QString address;

    // Methods
    bool open();
    bool save();

    // private slots:
    void _q_onModifiedChanged(bool _isModified);

    HouseCouncil *q_ptr;
    Q_DECLARE_PUBLIC(HouseCouncil)
};

#endif // HOUSECOUNCIL_P_H
