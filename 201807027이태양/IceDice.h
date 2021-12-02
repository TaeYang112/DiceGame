#pragma once
#include "DiceBase.h"
class IceDice :
    public DiceBase
{
public:
    IceDice(int slot, int eye);
    void EyeChanged();
};

