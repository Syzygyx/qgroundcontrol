#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#include "core/ModelData.h"
#include "GeoFenceWidget.h"

//-----------------------------------------------------------------------------

GeoFenceWidget::GeoFenceWidget(QWidget* pParent) :
	QWidget(pParent),
	m_rGFC(ModelData::GetInstance()->GetGFC())
{
	connect(&m_rGFC, SIGNAL(SignalRefresh()), this, SLOT(Update()));

	m_pLayout = new QVBoxLayout(this);
	m_pLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	m_pLayout->setContentsMargins(10, 0, 10, 0);
	m_pLayout->setSpacing(5);

	Update();
}

//-----------------------------------------------------------------------------

GeoFenceWidget::~GeoFenceWidget()
{	}

//-----------------------------------------------------------------------------

void GeoFenceWidget::Update()
{
	setEnabled(false);
	// first clear all the remaining widgets
	for (int i = 0; i < m_lipEdit.count(); i++) {
		m_pLayout->removeWidget(m_lipEdit[i]);
		delete m_lipEdit[i];
	}
	m_lipEdit.clear();

	GeoFenceEdit* pGFE;
	for (int i = 0; i < m_rGFC.GetCount(); i++) {
		pGFE = new GeoFenceEdit(i, &m_rGFC.GetZone(i));
		m_pLayout->addWidget(pGFE);
		pGFE->Update();
		m_lipEdit << pGFE;
		connect(pGFE, SIGNAL(SignalCurrent(int)), this, SLOT(SetCurrent(int)));
		connect(&m_rGFC, SIGNAL(SignalMapCurrent(int)), this, SLOT(SetCurrent(int)));
		connect(pGFE, SIGNAL(SignalMinAlt(int,double)), this, SLOT(SetMinAlt(int,double)));
		connect(pGFE, SIGNAL(SignalMaxAlt(int,double)), this, SLOT(SetMaxAlt(int,double)));
		connect(pGFE, SIGNAL(SignalLon(int,int,double)), &m_rGFC, SLOT(SetLongitude(int,int,double)));
		connect(pGFE, SIGNAL(SignalLat(int,int,double)), &m_rGFC, SLOT(SetLatitude(int,int,double)));
		connect(
					&m_rGFC,
					SIGNAL(SignalMoved(int,int,double,double)),
					this,
					SLOT(MoveVertex(int,int,double,double))
					);
	}

	setMinimumSize(480, 60*m_rGFC.GetCount() + 10);
	setEnabled(true);
	update();
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::SetCurrent(int iInd)
{
	for (int i = 0; i < m_lipEdit.count(); i++)
		m_lipEdit[i]->SetCurrent(i == iInd);
	update();
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::SetMinAlt(int iInd, double dAlt)
{
	m_rGFC.GetZone(iInd).SetMinAltitude(dAlt);
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::SetMaxAlt(int iInd, double dAlt)
{
	m_rGFC.GetZone(iInd).SetMaxAltitude(dAlt);
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::paintEvent(QPaintEvent* pPE)
{
	QWidget::paintEvent(pPE);

	QPainter P(this);
	P.setRenderHints(QPainter::Antialiasing);

	QRect rect;
	QColor clr;
	qDebug() << "GeoFenceWidget::paintEvent" << m_rGFC.GetCount() << m_lipEdit.count();
	for (int i = 0; i < m_lipEdit.count(); i++) {
		rect = m_lipEdit[i]->geometry();
		rect.adjust(-1, -1, 1, 1);
		if (m_lipEdit[i]->IsCurrent())
			clr = Qt::darkCyan;
		else if (i % 2 == 0)
			clr = QColor(112, 112, 112);
		else
			clr = QColor(64, 64, 64);

		P.setBrush(clr);
		P.drawRoundedRect(rect, 5, 5);
	}
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::mousePressEvent(QMouseEvent* pME)
{
	for (int i = 0; i < m_lipEdit.count(); i++) {
		if (m_lipEdit[i]->geometry().contains(pME->pos())) {
			m_lipEdit[i]->SetCurrent();
		}	else {
			m_lipEdit[i]->SetCurrent(false);
		}
	}
	update();
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::showEvent(QShowEvent* pSE)
{
	qDebug() << "*** GeoFenceWidget::showEvent";
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::hideEvent(QHideEvent* pHE)
{
	qDebug() << "*** GeoFenceWidget::hideEvent";
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::MoveVertex(int iInd, int iP, double dLon, double dLat)
{
	m_lipEdit[iInd]->UpdateLocation(iP, dLon, dLat);
	m_rGFC.SetLocation(iInd, iP, dLon, dLat);
}

//-----------------------------------------------------------------------------

