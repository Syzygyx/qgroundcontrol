#include <QDebug>
#include "AirspeedIndicator.h"

//-----------------------------------------------------------------------------

AirspeedIndicator::AirspeedIndicator(
		double dMinSpeed,
		double dMaxSpeed,
		AirspeedUnit eAU,
		QWidget *pParent
		) :
	QcGaugeWidget(pParent)
{
	setMinimumSize(150, 150);
	m_eAU = eAU;
	m_dMinSpeed = dMinSpeed;
	m_dMaxSpeed = dMaxSpeed;

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

	// set the needle to 0, so that we can check if Init was called
	// and prevent the application from crashing
	m_pNeedle = 0;
}

//-----------------------------------------------------------------------------

AirspeedIndicator::~AirspeedIndicator()
{	}

//-----------------------------------------------------------------------------

void AirspeedIndicator::Init()
{
	// top text label
	QcLabelItem* plbi = addLabel(73);
	plbi->setAngle(90.0f);
	plbi->setColor(Qt::white);
	plbi->setText(tr("AIRSPEED"));

	// unit label
	plbi = addLabel(20);
	plbi->setAngle(-90.0f);
	plbi->setColor(Qt::white);
	if (m_eAU == auKmh)
		plbi->setText("KM/H");
	else if (m_eAU == auKnots)
		plbi->setText("KNOTS");
	else
		plbi->setText("MPH");

	// add the white color band
	QcColorBand* pcb = addColorBand(80);
	QList<QPair<QColor, float> > li;
	QPair<QColor, float> pair;
	pair.first = Qt::white;
	pair.second = 45.0f/1.6f;
	li << pair;
	pcb->setColors(li);
	pcb->setDgereeRange(135, 405);

	// add the second color band
	pcb = addColorBand(75);
	li.clear();
	pair.first = Qt::transparent;
	pair.second = 5.0f/1.6f;
	li << pair;
	pair.first = Qt::green;
	pair.second = 90.0f/1.6f;
	li << pair;
	pair.first = Qt::yellow;
	pair.second = 120.0f/1.6f;
	li << pair;
	pair.first = Qt::red;
	pair.second = 100.0f;
	li << pair;
	pcb->setColors(li);
	pcb->setDgereeRange(135, 405);

	// big scale
	QcDegreesItem* pdi = addDegrees(84);
	pdi->setColor(Qt::white);
	pdi->setValueRange(m_dMinSpeed, m_dMaxSpeed);
	if (m_eAU == auKmh)
		pdi->setStep(50.0);
	else
		pdi->setStep(20.0);
	pdi->setDgereeRange(135, 405);

	// small scale
	pdi = addDegrees(84);
	pdi->setColor(Qt::white);
	pdi->setValueRange(m_dMinSpeed, m_dMaxSpeed);
	if (m_eAU == auKmh)
		pdi->setStep(10.0);
	else
		pdi->setStep(5.0);
	pdi->setDgereeRange(135, 405);
	pdi->setSubDegree(true);

	// value labels
	QString qsNum;
	double dVal = m_dMinSpeed;
	double dStep;
	if (m_eAU == auKmh)
		dStep = 50.0;
	else
		dStep = 20.0;

	int iStep = 0;
	while (dVal <= m_dMaxSpeed) {
		qsNum.setNum(dVal, 'f', 0);
		// make shorter labels closer to the edge
		QcLabelItem* plbiNum = addLabel(61 - 2*qsNum.length());
		plbiNum->setColor(Qt::white);
		plbiNum->setText(qsNum);
		plbiNum->setAngle(135 + 270*(dVal - m_dMinSpeed)/(m_dMaxSpeed - m_dMinSpeed));
		iStep++;
		dVal = m_dMinSpeed + iStep*dStep;
	}

	m_pNeedle = addNeedle(75);
	m_pNeedle->setColor(Qt::white);
	m_pNeedle->setNeedle(QcNeedleItem::DiamonNeedle);
	// we want needle to point straight up at speed 0, thus range (90, 405)
	// instead of (135, 405)
	m_pNeedle->setDgereeRange(90, 405);
	// now we must correct the minimal value as well. (405-135)/45 = 6
	m_pNeedle->setMinValue(m_dMinSpeed - (m_dMaxSpeed-m_dMinSpeed)/6);
	m_pNeedle->setMaxValue(m_dMaxSpeed);
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

void AirspeedIndicator::SetSpeed(double dSpeed)
{
	if (m_pNeedle != 0) {
		m_pNeedle->setCurrentValue(dSpeed);
		update();
	}	else {
		qWarning() << "AirspeedIndicator not initialized! Call AirspeedIndicator::Init method after constructor!";
	}
}

//-----------------------------------------------------------------------------


