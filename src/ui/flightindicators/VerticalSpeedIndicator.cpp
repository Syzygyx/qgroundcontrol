#include <QDebug>

#include "SizeDef.h"

#include "VerticalSpeedIndicator.h"

//-----------------------------------------------------------------------------

VerticalSpeedIndicator::VerticalSpeedIndicator(double dMaxVS, QWidget *pParent) :
	QcGaugeWidget(pParent)
{
	m_dMaxVS = dMaxVS;

    setMinimumSize(MIN_GAUGE_SIZE);
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

	// set the needle to 0, so that we can check if Init was called
	// and prevent the application from crashing
	m_pNeedle = 0;
}

//-----------------------------------------------------------------------------

VerticalSpeedIndicator::~VerticalSpeedIndicator()
{	}

//-----------------------------------------------------------------------------

void VerticalSpeedIndicator::Init()
{
	// add the scale
	QcDegreesItem* pdi = addDegrees(84);
	pdi->setColor(Qt::white);
	pdi->setValueRange(-m_dMaxVS, m_dMaxVS);
	pdi->setStep(m_dMaxVS/4.0);
	pdi->setDgereeRange(-170, 170);

	// add the labels
	double dVal = -m_dMaxVS;
	QString qsNum;
	for (int i = 0; i < 8; i++) {
		qsNum.setNum(fabs(dVal), 'f', 0);
		QcLabelItem* plbi = addLabel(59);
		plbi->setText(qsNum);
		plbi->setColor(Qt::white);
		if (i == 0)
			plbi->setAngle(180);
		else
			plbi->setAngle(-170.0 + i*340.0/8.0);
		dVal += m_dMaxVS/4.0;
	}

	// add small scale
	pdi = addDegrees(84);
	pdi->setColor(Qt::white);
	pdi->setValueRange(-m_dMaxVS/2.0, m_dMaxVS/2.0);
	pdi->setStep(m_dMaxVS/20.0);
	pdi->setDgereeRange(-85, 85);
	pdi->setSubDegree(true);

	// up and down labels
	QcLabelItem* plbi;
	plbi = addLabel(47);
	plbi->setText(tr("UP"));
	plbi->setColor(Qt::white);
	plbi->setAngle(22);

	plbi = addLabel(47);
	plbi->setText(tr("DN"));
	plbi->setColor(Qt::white);
	plbi->setAngle(-22);

	// unit labels
	plbi = addLabel(38);
	plbi->setText(tr("VERTICAL"));
	plbi->setColor(Qt::white);
	plbi->setAngle(125);

	plbi = addLabel(20);
	plbi->setText(tr("SPEED"));
	plbi->setColor(Qt::white);
	plbi->setAngle(130);

	plbi = addLabel(27);
	plbi->setText(tr("100 FEET"));
	plbi->setColor(Qt::white);
	plbi->setAngle(-140);

	plbi = addLabel(45);
	plbi->setText(tr("PER MINUTE"));
	plbi->setColor(Qt::white);
	plbi->setAngle(-135);

	// add the needle
	m_pNeedle = addNeedle(75);
	m_pNeedle->setColor(Qt::white);
	m_pNeedle->setNeedle(QcNeedleItem::DiamonNeedle);
	m_pNeedle->setDgereeRange(-170, 170);
	m_pNeedle->setMinValue(-m_dMaxVS);
	m_pNeedle->setMaxValue(m_dMaxVS);
	m_pNeedle->setCurrentValue(0.0);

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

void VerticalSpeedIndicator::SetVerticalSpeed(double dVerticalSpeed)
{
	if (m_pNeedle != 0) {
		m_pNeedle->setCurrentValue(dVerticalSpeed);
		update();
	}	else {
		qWarning() << "VerticalSpeedIndicator not initialized! Call VerticalSpeedIndicator::Init method after constructor!";
	}
}

//-----------------------------------------------------------------------------


