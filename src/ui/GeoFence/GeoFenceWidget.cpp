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

	setAutoFillBackground(true);
	Update();
}

//-----------------------------------------------------------------------------

GeoFenceWidget::~GeoFenceWidget()
{	}

//-----------------------------------------------------------------------------

void GeoFenceWidget::Update()
{
	// first clear all the remaining widgets
	for (int i = 0; i < m_lipEdit.count(); i++) {
		m_pLayout->removeWidget(m_lipEdit[i]);
		delete m_lipEdit[i];
	}

	GeoFenceEdit* pGFE;
	for (int i = 0; i < m_rGFC.GetCount(); i++) {
		pGFE = new GeoFenceEdit(i, &m_rGFC.GetZone(i));
		m_pLayout->addWidget(pGFE);
		pGFE->Update();
		m_lipEdit << pGFE;
	}

	setMinimumSize(480, 60*m_rGFC.GetCount() + 10);
	update();
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

