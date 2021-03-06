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
	m_iCurrent = -1;

	// connect signals for reconstruction of GeoFence edit widgets,
	// adding point to current zone, making a zone current and moving vertex
	// through map

	connect(&m_rGFC, SIGNAL(SignalRefresh()), this, SLOT(Update()));
	connect(
				&m_rGFC,
				SIGNAL(SignalAddPoint(double,double)),
				this,
				SLOT(AddPoint(double,double))
				);

	connect(&m_rGFC, SIGNAL(SignalMapCurrent(int)), this, SLOT(SetCurrent(int)));
	connect(
				&m_rGFC,
				SIGNAL(SignalMoved(int,int,double,double)),
				this,
				SLOT(MoveVertex(int,int,double,double))
				);

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
	// signal to this slot comes from GeoFenceContainer (via WaypointList button)
	setEnabled(false);
	m_iCurrent = -1;
	// first clear all the remaining widgets
	for (int i = 0; i < m_lipEdit.count(); i++) {
		m_pLayout->removeWidget(m_lipEdit[i]);
		delete m_lipEdit[i];
	}
	m_lipEdit.clear();

	for (int i = 0; i < m_rGFC.GetCount(); i++) {
		CreateEditWidget(i);
	}
	UpdateMinSize();
	setEnabled(true);
	update();
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::SetCurrent(int iInd)
{
	// this slot can be triggered via GeoFenceContainer (via selecting zone on map),
	// via GeoFenceEdit widgets (clicking on its edit boxes) or via
	// via WaypointList (clicking on empty space)
	// mousePressEvent does similar thing as this
	m_iCurrent = iInd;
	for (int i = 0; i < m_lipEdit.count(); i++)
		m_lipEdit[i]->SetCurrent(i == m_iCurrent);
	update();
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::SetMinAlt(int iInd, double dAlt)
{
	// triggered from GeoFenceEdit
	m_rGFC.GetZone(iInd).SetMinAltitude(dAlt);
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::SetMaxAlt(int iInd, double dAlt)
{
	// triggered from GeoFenceEdit
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
	m_iCurrent = -1;
	for (int i = 0; i < m_lipEdit.count(); i++) {
		if (m_lipEdit[i]->geometry().contains(pME->pos())) {
			m_lipEdit[i]->SetCurrent();
			m_iCurrent = i;
		}	else {
			m_lipEdit[i]->SetCurrent(false);
		}
	}
	update();
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::showEvent(QShowEvent* pSE)
{
	QWidget::showEvent(pSE);
	m_rGFC.SetGeoFenceMode(true);
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::hideEvent(QHideEvent* pHE)
{
	QWidget::hideEvent(pHE);
	m_rGFC.SetGeoFenceMode(false);
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::MoveVertex(int iInd, int iP, double dLon, double dLat)
{
	// signal to this slot comes from GeoFenceContainer (via map)
	m_lipEdit[iInd]->UpdateLocation(iP, dLon, dLat);
	m_rGFC.SetLocation(iInd, iP, dLon, dLat);
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::AddPoint(double dLon, double dLat)
{
	// signal to this slot comes from GeoFenceContainer (via map)
	if (m_iCurrent >= 0 && m_iCurrent < m_rGFC.GetCount()) {
		// add point to existing (current zone)
		m_rGFC.GetZone(m_iCurrent).Append(QPointF(dLon, dLat));
		// make container report the change
		emit m_rGFC.SignalUpdate(m_iCurrent);
		// also add lon/lat fields into current zone edit widget
		m_lipEdit[m_iCurrent]->AddLatestFields();
	}	else {
		// create new zone with given point
		GeoFenceZone zone;
		zone.Append(QPointF(dLon, dLat));
		m_rGFC.Append(zone);
		CreateEditWidget(m_rGFC.GetCount() - 1);
		UpdateMinSize();

		emit m_rGFC.SignalAddZone();
	}
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::RemoveZone(int iInd)
{
	// triggered from GeoFenceEdit
	m_rGFC.Remove(iInd);
	m_lipEdit[iInd]->deleteLater();
	m_lipEdit.removeAt(iInd);
	SetCurrent(-1);

	// update indices
	for (int i = 0; i < m_lipEdit.count(); i++)
		m_lipEdit[i]->SetIndex(i);
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::CreateEditWidget(int i)
{
	GeoFenceEdit* pGFE;
	pGFE = new GeoFenceEdit(i, &m_rGFC.GetZone(i));
	m_pLayout->addWidget(pGFE);
	pGFE->Update();
	m_lipEdit << pGFE;

	// connect all the signals from underlying widget pGFE
	connect(pGFE, SIGNAL(SignalCurrent(int)), this, SLOT(SetCurrent(int)));
	connect(pGFE, SIGNAL(SignalMinAlt(int,double)), this, SLOT(SetMinAlt(int,double)));
	connect(pGFE, SIGNAL(SignalMaxAlt(int,double)), this, SLOT(SetMaxAlt(int,double)));
	connect(pGFE, SIGNAL(SignalLon(int,int,double)), &m_rGFC, SLOT(SetLongitude(int,int,double)));
	connect(pGFE, SIGNAL(SignalLat(int,int,double)), &m_rGFC, SLOT(SetLatitude(int,int,double)));
	connect(pGFE, SIGNAL(SignalRemove(int)), this, SLOT(RemoveZone(int)));
}

//-----------------------------------------------------------------------------

void GeoFenceWidget::UpdateMinSize()
{
	setMinimumSize(480, 60*m_rGFC.GetCount() + 10);
}

//-----------------------------------------------------------------------------

