#include <QDebug>
#include <QTimer>

#include "AltitudeIndicator.h"

//-----------------------------------------------------------------------------

AltitudeIndicator::AltitudeIndicator(QWidget* pParent) :
	QcGaugeWidget(pParent)
{
	setMinimumSize(150, 150);
	// create some background
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

	// set the needles to 0, so that we can check if Init was called
	// and prevent the application from crashing
	m_pNeedle1 = 0;
	m_pNeedle100 = 0;

	// Testing only
	m_dAlt = 0.0;

	QTimer* pTimer = new QTimer(this);
	pTimer->setInterval(50);
	connect(pTimer, SIGNAL(timeout()), this, SLOT(IncreaseAltitude()));
	pTimer->start();
}

//-----------------------------------------------------------------------------

AltitudeIndicator::~AltitudeIndicator()
{	}

//-----------------------------------------------------------------------------

void AltitudeIndicator::Init()
{
	// add some scales
	QcDegreesItem* pdi = addDegrees(84);
	pdi->setColor(Qt::white);
	pdi->setDgereeRange(90, 450);
	pdi->setValueRange(0, 100);
	pdi->setStep(10);

	// small scales
	pdi = addDegrees(84);
	pdi->setColor(Qt::white);
	pdi->setDgereeRange(90, 450);
	pdi->setValueRange(0, 100);
	pdi->setStep(2);
	pdi->setSubDegree(true);

	// add numbers
	QString qsNum;
	for (int i = 0; i < 10; i++) {
		qsNum.setNum(i);
		QcLabelItem* plbi = addLabel(60);
		plbi->setText(qsNum);
		plbi->setColor(Qt::white);
		plbi->setAngle(90 + i*36);
	}

	// add ALT label
	QcLabelItem* plbi = addLabel(30);
	plbi->setText(tr("ALT"));
	plbi->setColor(Qt::white);
	plbi->setAngle(126);

	// 100 FEET labels
	plbi = addLabel(64);
	plbi->setText("100");
	plbi->setFont(-2);
	plbi->setColor(Qt::white);
	plbi->setFontWeight(QFont::Normal);
	plbi->setAngle(72);
	plbi->setRotation(-15);

	plbi = addLabel(64);
	plbi->setText(tr("FEET"));
	plbi->setFont(-2);
	plbi->setColor(Qt::white);
	plbi->setFontWeight(QFont::Normal);
	plbi->setAngle(108);
	plbi->setRotation(15);

	// add the needles
	// 100 feet needle
	m_pNeedle100 = addNeedle(65);
	m_pNeedle100->setColor(Qt::white);
	m_pNeedle100->setNeedle(QcNeedleItem::SwordNeedle);
	m_pNeedle100->setOutline(Qt::black);
	m_pNeedle100->setDgereeRange(90, 449.64);
	m_pNeedle100->setMinValue(0);
	m_pNeedle100->setMaxValue(9.99);
	m_pNeedle100->setCurrentValue(0.0);
	// 1 feet needle
	m_pNeedle1 = addNeedle(75);
	m_pNeedle1->setColor(Qt::white);
	m_pNeedle1->setNeedle(QcNeedleItem::FeatherNeedle);
	m_pNeedle1->setDgereeRange(90, 446.4);
	m_pNeedle1->setMinValue(0);
	m_pNeedle1->setMaxValue(99);
	m_pNeedle1->setCurrentValue(0);

	// needle covering button
	QcBackgroundItem* pbg = addBackground(8);
	pbg->clearrColors();
	pbg->addColor(0.2, QColor(0, 0, 128));
	pbg->addColor(0.5, QColor(0, 0, 64));
	pbg->addColor(0.8, Qt::black);

	// and finally a cool glass effect
	addGlass(88);
}

//-----------------------------------------------------------------------------

void AltitudeIndicator::SetAltitude(double dAlt)
{
	if (m_pNeedle1 != 0 && m_pNeedle100 != 0) {
		double dAlt100 = 100.0*floor(dAlt/100.0);
		m_pNeedle1->setCurrentValue(floor(dAlt-dAlt100));
		m_pNeedle100->setCurrentValue(dAlt/100.0);
	}	else {
		qWarning() << "AltitudeIndicator not initialized! Call AltitudeIndicator::Init method after constructor!";
	}
}

//-----------------------------------------------------------------------------

void AltitudeIndicator::IncreaseAltitude()
{
	m_dAlt += 1.0;
	SetAltitude(m_dAlt);
}

//-----------------------------------------------------------------------------

