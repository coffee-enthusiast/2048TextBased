#include "Cell.h"
#include <stdlib.h>
int Cell::getValue()
{
	return m_value;
}

void Cell::setValue(int value)
{
	if (value >= 0)
		m_value = value;
}

Cell::Cell()
{
	m_value = 0;
}

Cell::~Cell()
{
}

