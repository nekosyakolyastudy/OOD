// visitor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CPlane.h"
#include "CBoat.h"
#include "CBus.h"
#include "CCar.h"
#include "CDrawingVisitor.h"
#include "CPriceVisitor.h"

int main()
{
	CBus bus;
	CDrawingVisitor drawingVisitor;
	CPriceVisitor calculateTicketPriceVisitor;
	
	bus.Accept(drawingVisitor);
	std::cout << "Ticket price: " << calculateTicketPriceVisitor.GetTicketPrice(500.f, bus) << std::endl;

	CCar car;
	car.Accept(drawingVisitor);
	std::cout << "Ticket price: " << calculateTicketPriceVisitor.GetTicketPrice(500.f, car) << std::endl;

	return 0;
}
