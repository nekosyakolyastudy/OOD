#pragma once
#include "IFlyBehavior.h"
class CFlyNoWay :
	public IFlyBehavior
{
public:
	void Fly() override;
	void SetFlightNumber(int) override;
	int GetFlightNumber() const override;
};
