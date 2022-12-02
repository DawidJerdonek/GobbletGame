#include "Cell.h"

Cell::Cell()
{	m_id = -1;
	m_previousCellId = -1;
}

int Cell::getID() const
{
	return m_id;
}