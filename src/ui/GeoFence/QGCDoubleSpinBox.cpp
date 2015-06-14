#include <QDebug>

#include "QGCDoubleSpinBox.h"

//-----------------------------------------------------------------------------

QGCDoubleSpinBox::QGCDoubleSpinBox(QWidget* pParent) :
	QDoubleSpinBox(pParent)
{	}

//-----------------------------------------------------------------------------

QGCDoubleSpinBox::~QGCDoubleSpinBox()
{	}

//-----------------------------------------------------------------------------

void QGCDoubleSpinBox::focusInEvent(QFocusEvent* pFE)
{
	QDoubleSpinBox::focusInEvent(pFE);
	emit SignalCurrent();
}

//-----------------------------------------------------------------------------

