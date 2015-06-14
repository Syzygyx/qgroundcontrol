#include <QGridLayout>
#include <QDoubleValidator>
#include <QPushButton>

#include "GeoFenceEdit.h"

#define MAX_LON_LAT				6

//-----------------------------------------------------------------------------

GeoFenceEdit::GeoFenceEdit(int iInd, GeoFenceZone* pZone, QWidget* pParent) :
	QWidget(pParent)
{
	setObjectName("GeoFenceEdit");
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

void GeoFenceEdit::BuildGUI()
{
	// we put everything in layout
	QGridLayout* pLayout = new QGridLayout(this);

	m_plbIndex = new QLabel(this);
	m_plbIndex->setText(QString::number(m_iIndex + 1));

	pLayout->addWidget(m_plbIndex, 0, 0, 3, 1);

	QLabel* plb;
	plb = new QLabel(tr("Min. alt."));
	pLayout->addWidget(plb, 1, 1);

	plb = new QLabel(tr("Max. alt."));
	pLayout->addWidget(plb, 2, 1);

	m_psbMinAlt = new QDoubleSpinBox(this);
	m_psbMinAlt->setRange(0.0, 10000.0);
	m_psbMinAlt->setDecimals(0);
	m_psbMinAlt->setSuffix("m");
	pLayout->addWidget(m_psbMinAlt, 1, 2);

	m_psbMaxAlt = new QDoubleSpinBox(this);
	m_psbMaxAlt->setRange(0.0, 10000.0);
	m_psbMaxAlt->setDecimals(0);
	m_psbMaxAlt->setSuffix("m");
	pLayout->addWidget(m_psbMaxAlt, 2, 2);

	QPushButton* pb;
	pb = new QPushButton("<<");
	pLayout->addWidget(pb, 0, 3, 3, 1);
	QChar ch(0x00b0);

	QDoubleSpinBox* psbPos;
	for (int i = 0; i < qMin(MAX_LON_LAT, m_pZone->GetCount()); i++) {
		QLabel* plbVert = new QLabel;
		plbVert->setText(tr("Vertex %1").arg(m_iLeftMost + i + 1));
		pLayout->addWidget(plbVert, 0, 4 + i, 1, 1);

		psbPos = new QDoubleSpinBox;
		psbPos->setRange(-180.0, 180.0);
		psbPos->setSuffix(ch);
		psbPos->setPrefix("lon ");
		psbPos->setDecimals(10);
		m_liLongitudes << psbPos;
		pLayout->addWidget(psbPos, 1, 4 + i, 1, 1);

		psbPos = new QDoubleSpinBox;
		psbPos->setRange(-90.0, 90.0);
		psbPos->setSuffix(ch);
		psbPos->setPrefix("lat ");
		psbPos->setDecimals(10);
		pLayout->addWidget(psbPos, 2, 4 + i, 1, 1);
		m_liLatitudes << psbPos;
	}

	pb = new QPushButton(">>");
	pLayout->addWidget(pb, 0, 4 + MAX_LON_LAT, 3, 1);
	pLayout->setSizeConstraint(QLayout::SetFixedSize);
}

//-----------------------------------------------------------------------------

