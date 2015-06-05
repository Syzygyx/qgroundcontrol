#include "gauge/QcPixmapItem.h"

#include "WeightGauge.h"

//-----------------------------------------------------------------------------

WeightGauge::WeightGauge(double dMaxWeight, bool bLabels, QWidget *pParent) :
	QcGaugeWidget(pParent)
{
	setMinimumSize(150, 150);
	m_dMaxWeight = dMaxWeight;

	// some background items
	QcBackgroundItem* pbg = addBackground(99);
	pbg->clearrColors();
	pbg->addColor(0.1, QColor(240, 240, 240));
	pbg->addColor(1.0, QColor(16, 16, 16));

	pbg = addBackground(95);
	pbg->clearrColors();
	pbg->addColor(0.1, QColor(32, 32, 32));
	pbg->addColor(1.0, QColor(224, 224, 224));

	pbg = addBackground(88);
	pbg->clearrColors();
	pbg->addColor(0.1, QColor(32, 32, 32));
	pbg->addColor(1.0, QColor(64, 64, 64));

	// color band
	QcColorBand* pcb = addColorBand(80);
	// create the color list
	QList<QPair<QColor, float> > li1;
	QPair<QColor, float> pair;
	pair.first = Qt::darkGreen;
	pair.second = 80;
	li1 << pair;
	pair.first = Qt::red;
	pair.second = 100;
	li1 << pair;
	pcb->setColors(li1);
	pcb->setDgereeRange(-45.0f, 225.0f);

	// second color band
	pcb = addColorBand(75);
	QList<QPair<QColor, float> > li2;
	pair.first = Qt::darkGreen;
	pair.second = 95;
	li2 << pair;
	pair.first = Qt::red;
	pair.second = 100;
	li2 << pair;
	pcb->setColors(li2);
	pcb->setDgereeRange(-45.0f, 225.0f);

	// scales
	QcDegreesItem* pdi;
	pdi = addDegrees(84);
	pdi->setValueRange(0.0, m_dMaxWeight);
	pdi->setSubDegree(true);
	pdi->setStep(m_dMaxWeight/4);
	pdi->setColor(Qt::white);

	// labels
	if (bLabels == true) {
		QString qsText;
		for (int i = 0; i <= 4; i++) {
			qsText.setNum(i*m_dMaxWeight/4.0, 'f', 0);
			// move longer numbers more away from color band
			QcLabelItem* plbi = addLabel(60 - qsText.length());
			plbi->setAngle(-45 + 270*i/4.0);
			plbi->setText(qsText);
			plbi->setColor(Qt::white);
		}
	}

	// Central pixmap item
	QPixmap pix(":/files/Person.png");
	QcPixmapItem* ppi = new QcPixmapItem(pix, 20, this);
	ppi->setAngle(90);
	addItem(ppi, 10);

	// bottom label
	QcLabelItem* plbi = addLabel(30);
	plbi->setAngle(-90);
	plbi->setText("WEIGHT");
	plbi->setColor(Qt::white);

	// unit label
	plbi = addLabel(50);
	plbi->setAngle(-90);
	plbi->setText("kg");
	plbi->setColor(Qt::white);

	addGlass(88);

	// needle
	m_pNeedle = addNeedle(80);
	m_pNeedle->setNeedle(QcNeedleItem::FeatherNeedle);
	m_pNeedle->setMinValue(0.0);
	m_pNeedle->setMaxValue(m_dMaxWeight);
	m_pNeedle->setCurrentValue(0.0);
	m_pNeedle->setColor(Qt::white);
}

//-----------------------------------------------------------------------------

WeightGauge::~WeightGauge()
{	}

//-----------------------------------------------------------------------------

void WeightGauge::SetWeight(double dWeight)
{
	m_pNeedle->setCurrentValue(dWeight);
	update();
}

//-----------------------------------------------------------------------------

