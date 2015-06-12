#include <QDebug>
#include <QTimer>

#include "gauge/QcPolygonItem.h"

#include "HeadingIndicator.h"

//-----------------------------------------------------------------------------

HeadingIndicator::HeadingIndicator(QWidget* pParent) : QcRotatedGaugeWidget(pParent)
{
	m_bInitialized = false;
	setMinimumSize(100, 100);
	// create some background, items are fixed by default!
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
}

//-----------------------------------------------------------------------------

HeadingIndicator::~HeadingIndicator()
{	}

//-----------------------------------------------------------------------------

void HeadingIndicator::Init()
{
	// add the unit scale
	QcDegreesItem* pdi = addDegrees(84);
	pdi->setColor(Qt::white);
	pdi->setValueRange(0, 360);
	pdi->setDgereeRange(90, 450);
	pdi->setStep(10);
	// make it rotational
	pdi->setRotate();

	// add half the unit scale
	pdi = addDegrees(84);
	pdi->setColor(Qt::white);
	pdi->setValueRange(0, 360);
	pdi->setDgereeRange(90, 450);
	pdi->setStep(5);
	pdi->setSubDegree(true);
	// make it rotational
	pdi->setRotate();

	// add text labels
	QString qsNum;
	for (int i = 0; i < 36; i += 3) {
		if (i == 0)
			qsNum = "N";
		else if (i == 9)
			qsNum = "E";
		else if (i == 18)
			qsNum = "S";
		else if (i == 27)
			qsNum = "W";
		else
			qsNum.setNum(i);

		QcLabelItem* plbi = addLabel(60);
		plbi->setColor(Qt::white);
		plbi->setText(qsNum);
		plbi->setAngle(90.0f + i*10.0f);
		plbi->setRotation(i*10.0f);
		// make it rotate with background
		plbi->setRotate(true);
		// increase font for the major directions
		if (i % 9 == 0)
			plbi->setFont(2);
	}

	// add the airplane item
	QcPolygonItem* ppi = new QcPolygonItem(this);
	ppi->setPosition(48);
	mItems.append(ppi);
	ppi->SetColor(Qt::white);
	ppi->AddPoint(0.0, -1.0);
	ppi->AddPoint(0.09, -0.85);
	ppi->AddPoint(0.13, -0.7);
	ppi->AddPoint(0.13, -0.45);
	ppi->AddPoint(0.8, 0.15);
	ppi->AddPoint(0.75, 0.25);
	ppi->AddPoint(0.13, 0.05);
	ppi->AddPoint(0.13, 0.3);
	ppi->AddPoint(0.09, 0.5);
	ppi->AddPoint(0.4, 0.8);
	ppi->AddPoint(0.4, 0.9);
	ppi->AddPoint(0.05, 0.82);
	ppi->AddPoint(0.00, 0.92);
	ppi->AddMirrorY();

	// add glass effect
	addGlass(88);

	// mark as initialized
	m_bInitialized = true;
}

//-----------------------------------------------------------------------------

void HeadingIndicator::SetHeading(double dAng)
{
	if (m_bInitialized == true) {
		setRotation(dAng);
		update();
	}	else {
		qWarning() << "HeadingIndicator not initialized! Call HeadingIndicator::Init method after constructor!";
	}
}

//-----------------------------------------------------------------------------

