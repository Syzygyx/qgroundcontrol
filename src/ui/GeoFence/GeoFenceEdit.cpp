#include <QGridLayout>
#include <QDoubleValidator>
#include <QPushButton>

#include "GeoFenceEdit.h"

#define MAX_LON_LAT				6

//-----------------------------------------------------------------------------

GeoFenceEdit::GeoFenceEdit(int iInd, GeoFenceZone* pZone, QWidget* pParent) :
	QWidget(pParent)
{
	m_pMapper = new QSignalMapper(this);
	connect(m_pMapper, SIGNAL(mapped(int)), this, SLOT(ReportPosition(int)));
	m_iLeftMost = 0;
	m_iIndex = iInd;
	m_pZone = pZone;
	BuildGUI();
	setAutoFillBackground(true);
	SetCurrent(false);
}

//-----------------------------------------------------------------------------

GeoFenceEdit::~GeoFenceEdit()
{	}

//-----------------------------------------------------------------------------

void GeoFenceEdit::SetCurrent(bool bCur)
{
	m_bCurrent = bCur;
	update();
}

//-----------------------------------------------------------------------------

void GeoFenceEdit::Update()
{
	m_psbMinAlt->setValue(m_pZone->GetMinAltitude());
	m_psbMaxAlt->setValue(m_pZone->GetMaxAltitude());

	int iLast = qMin(m_iLeftMost + m_liLatitudes.count(), m_pZone->GetCount());
	for (int i = m_iLeftMost; i < iLast; i++) {
		m_liLongitudes[i]->setValue(m_pZone->GetPoint(i).x());
		m_liLatitudes[i]->setValue(m_pZone->GetPoint(i).y());
	}
	update();
}

//-----------------------------------------------------------------------------

void GeoFenceEdit::UpdateLocation(int i, double dLon, double dLat)
{
	// prevent signals to be sent!
	blockSignals(true);
	m_liLongitudes[i]->setValue(dLon);
	m_liLatitudes[i]->setValue(dLat);
	blockSignals(false);
}

//-----------------------------------------------------------------------------

void GeoFenceEdit::AddLatestFields()
{
	AddFields(m_pZone->GetCount() - 1);
}

//-----------------------------------------------------------------------------

void GeoFenceEdit::BuildGUI()
{
	// we put everything in layout
	m_pLayout = new QGridLayout(this);

	m_plbIndex = new QLabel(this);
	m_plbIndex->setText(QString::number(m_iIndex + 1));

	m_pLayout->addWidget(m_plbIndex, 0, 0, 3, 1);

	QLabel* plb;
	plb = new QLabel(tr("Min. alt."));
	m_pLayout->addWidget(plb, 1, 1);

	plb = new QLabel(tr("Max. alt."));
	m_pLayout->addWidget(plb, 2, 1);

	m_psbMinAlt = new QGCDoubleSpinBox(this);
	m_psbMinAlt->setRange(0.0, 10000.0);
	m_psbMinAlt->setDecimals(0);
	m_psbMinAlt->setSuffix("m");
	connect(m_psbMinAlt, SIGNAL(SignalCurrent()), this, SLOT(ReportCurrent()));
	connect(m_psbMinAlt, SIGNAL(valueChanged(double)), this, SLOT(ReportMinAlt()));
	m_pLayout->addWidget(m_psbMinAlt, 1, 2);

	m_psbMaxAlt = new QGCDoubleSpinBox(this);
	m_psbMaxAlt->setRange(0.0, 10000.0);
	m_psbMaxAlt->setDecimals(0);
	m_psbMaxAlt->setSuffix("m");
	connect(m_psbMaxAlt, SIGNAL(SignalCurrent()), this, SLOT(ReportCurrent()));
	connect(m_psbMaxAlt, SIGNAL(valueChanged(double)), this, SLOT(ReportMaxAlt()));
	m_pLayout->addWidget(m_psbMaxAlt, 2, 2);

	/*
	QPushButton* pb;
	pb = new QPushButton("<<");
	connect(pb, SIGNAL(clicked()), this, SLOT(ReportCurrent()));
	pLayout->addWidget(pb, 0, 3, 3, 1);
	*/

	for (int i = 0; i < m_pZone->GetCount(); i++) {
		AddFields(i);
	}

	/*
	pb = new QPushButton(">>");
	connect(pb, SIGNAL(clicked()), this, SLOT(ReportCurrent()));
	pLayout->addWidget(pb, 0, 4 + MAX_LON_LAT, 3, 1);
	*/

	m_pLayout->setSizeConstraint(QLayout::SetFixedSize);
}

//-----------------------------------------------------------------------------

void GeoFenceEdit::AddFields(int i)
{
	QChar ch(0x00b0);
	QGCDoubleSpinBox* psbPos;

	QLabel* plbVert = new QLabel;
	plbVert->setText(tr("Vertex %1").arg(m_iLeftMost + i + 1));
	m_pLayout->addWidget(plbVert, 0, 3 + i, 1, 1);

	psbPos = new QGCDoubleSpinBox;
	psbPos->setRange(-180.0, 180.0);
	psbPos->setSuffix(ch);
	psbPos->setPrefix("lon ");
	psbPos->setDecimals(10);
	m_liLongitudes << psbPos;
	connect(psbPos, SIGNAL(SignalCurrent()), this, SLOT(ReportCurrent()));

	connect(psbPos, SIGNAL(valueChanged(double)), m_pMapper, SLOT(map()));
	// let's give longitude fields positive indices to accomodate for
	// the latitude fields to be binded on the same signal mapper
	m_pMapper->setMapping(psbPos, i+1);

	m_pLayout->addWidget(psbPos, 1, 3 + i, 1, 1);

	psbPos = new QGCDoubleSpinBox;
	psbPos->setRange(-90.0, 90.0);
	psbPos->setSuffix(ch);
	psbPos->setPrefix("lat ");
	psbPos->setDecimals(10);
	m_liLatitudes << psbPos;
	connect(psbPos, SIGNAL(SignalCurrent()), this, SLOT(ReportCurrent()));

	connect(psbPos, SIGNAL(valueChanged(double)), m_pMapper, SLOT(map()));
	// let's give latitude fields negative indices
	m_pMapper->setMapping(psbPos, -(i+1));

	m_pLayout->addWidget(psbPos, 2, 3 + i, 1, 1);
}

//-----------------------------------------------------------------------------

void GeoFenceEdit::ReportCurrent()
{
	emit SignalCurrent(m_iIndex);
}

//-----------------------------------------------------------------------------

void GeoFenceEdit::ReportMinAlt()
{
	emit SignalMinAlt(m_iIndex, m_psbMinAlt->value());
}

//-----------------------------------------------------------------------------

void GeoFenceEdit::ReportMaxAlt()
{
	emit SignalMaxAlt(m_iIndex, m_psbMaxAlt->value());
}

//-----------------------------------------------------------------------------

void GeoFenceEdit::ReportPosition(int iInd)
{
	if (iInd > 0) {
		// longitude changed
		// this is for 1 bigger than the real index
		iInd--;
		emit SignalLon(m_iIndex, iInd, m_liLongitudes[iInd]->value());
	}	else {
		// latitude changed
		// to get the real index, first change the sign
		iInd = -iInd;
		// and then it is for 1 bigger than the real index
		iInd--;
		emit SignalLat(m_iIndex, iInd, m_liLatitudes[iInd]->value());
	}
}

//-----------------------------------------------------------------------------

