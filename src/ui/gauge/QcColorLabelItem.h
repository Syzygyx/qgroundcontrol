#ifndef QCCOLORLABELITEM_H
#define QCCOLORLABELITEM_H

#include "gauge/qcgaugewidget.h"

//! This class implements a text label with colored background
class QCGAUGE_DECL QcColorLabelItem : public QcLabelItem
{
public:
	//! Constructor
	QcColorLabelItem(QObject* pParent);
	//! Sets the background color
	void SetBackground(QColor clr)
	{	m_clrBG = clr; }
	//! Sets the width in [%]
	void SetWidth(int iPer)
	{	m_iPer = iPer; }
	//! Sets the value
	void SetValue(QString qsVal);
	//! Draws the item
	void draw(QPainter* pP);

protected:
	//! Background color
	QColor m_clrBG;
	//! Background field width [%]
	int m_iPer;
	//! Displayed value
	QString m_qsValue;
};

#endif // QCCOLORLABELITEM_H
