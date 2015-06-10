#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

#include "VehicleWidget.h"

#define PHOTO_W			550
#define PHOTO_H			500

//-----------------------------------------------------------------------------

VehicleWidget::VehicleWidget(QWidget* pParent) : QWidget(pParent)
{
	setMinimumSize(3*PHOTO_W/5, 3*PHOTO_H/5);
	QString qsFile = ":/files/Vehicle.svg";
	m_pSvgRender = new QSvgRenderer(qsFile, this);
	for (int i = 0; i < GAUGE_COUNT; i++)
		m_apGauges[i] = 0;

	m_pPixVehicle = 0;
}

//-----------------------------------------------------------------------------

VehicleWidget::~VehicleWidget()
{
	delete m_pSvgRender;
	if (m_pPixVehicle != 0)
		delete m_pPixVehicle;
}

//-----------------------------------------------------------------------------

void VehicleWidget::SetGauge(int i, QcGaugeWidget* pGauge)
{
	pGauge->setParent(this);
	int iW = GetSize(i);
	pGauge->setFixedSize(iW, iW);
	// moving the center to ptCenter is like moving the topleft corner
	// to the center minus half of gauge's width and height respectively
	QPoint ptCenter = GetCenter(i);
	pGauge->move(ptCenter.x() - iW/2, ptCenter.y() - iW/2);
	m_apGauges[i] = pGauge;
	pGauge->show();
}

//-----------------------------------------------------------------------------

QPoint VehicleWidget::GetCenter(int i) const
{
	// engine coordinates on 800 pix width
	// engine 0: 225, 196
	// engine 1: 399, 97
	// engine 2: 573, 196
	// engine 3: 574, 397
	// engine 4: 398, 496
	// engine 5: 226, 396
	// engine 6: 400, 297

	//int aiX[] = { 501, 602, 500, 300, 199, 300, 400 };
	//int aiY[] = { 122, 296, 471, 471, 296, 122, 297 };
	//int aiX[] = { 376, 478, 375, 175, 74, 175, 275 };
	//int aiY[] = { 87, 246, 406, 406, 246, 87, 247 };
	int aiX[] = { 101, 203, 101, -100, -201, -100, 0 };
	int aiY[] = { -178, -4, 172, 171, -4, -178, -3 };

	QPoint pt;
	if (i >= 0 &&  i < 7) {

		// center of the widget
		int iCX = width()/2-1;
		int iCY = height()/2-1;

		// size of the vehicle area
		int iW;
		int iH;
		if (iCX > PHOTO_W*iCY/PHOTO_H) {
			// empty space on the left and right
			iH = height();
			iW = PHOTO_W*iH/PHOTO_H;
		}	else {
			// empty space at top and bottom
			iW = width();
			iH = PHOTO_H*iW/PHOTO_W;
		}

		pt.setX(iCX + aiX[i]*iW/PHOTO_W);
		pt.setY(iCY + aiY[i]*iH/PHOTO_H);

	}	else {
		qWarning() << "Wrong engine index!";
		Q_ASSERT(i >= 0 && i < 7);
	}
	return pt;
}

//-----------------------------------------------------------------------------

int VehicleWidget::GetSize(int i) const
{
	// engines 0-5 have size 120 on 800 pix width
	// engine 6 has size 200 on 800 pix width

	int iW;
	if (width() > PHOTO_W*height()/PHOTO_H)
		iW = PHOTO_W*height()/PHOTO_H;
	else
		iW = width();

	if (i < 6)
		return (120*iW)/PHOTO_W;
	else
		return (205*iW)/PHOTO_W;
}

//-----------------------------------------------------------------------------

void VehicleWidget::paintEvent(QPaintEvent*)
{
	if (m_pPixVehicle == 0)
		CreateVehiclePixmap();

	QPainter P(this);

	//P.fillRect(rect(), Qt::transparent);

	P.drawPixmap(
				(width() - m_pixScaled.width())/2,
				(height() - m_pixScaled.height())/2,
				m_pixScaled
				);
}

//-----------------------------------------------------------------------------

void VehicleWidget::mousePressEvent(QMouseEvent* pME)
{
	qDebug() << "Mouse pressed at" << pME->pos();
}

//-----------------------------------------------------------------------------

void VehicleWidget::resizeEvent(QResizeEvent*)
{
	for (int i = 0; i < GAUGE_COUNT; i++) {
		if (m_apGauges[i] != 0) {
			int iW = GetSize(i);
			m_apGauges[i]->setFixedSize(iW, iW);
			// moving the center to ptCenter is like moving the topleft corner
			// to the center minus half of gauge's width and height respectively
			QPoint ptCenter = GetCenter(i);
			m_apGauges[i]->move(ptCenter.x() - iW/2, ptCenter.y() - iW/2);
		}
	}
	CreateVehiclePixmap();
}

//-----------------------------------------------------------------------------

void VehicleWidget::CreateVehiclePixmap()
{
	// create the full scale photo of vehicle
	if (m_pPixVehicle == 0) {
		// Widget for painting the original SVG file
		QPixmap pix(800, 800);
		pix.fill(Qt::transparent);

		QPainter P(&pix);
		QRectF rectW;
		rectW.setCoords(-200, 0, 1000, 900);
		QPoint pt(400, 297);
		P.translate(pt);
		P.rotate(90);
		P.translate(-pt);

		m_pSvgRender->render(&P, rectW);

		m_pPixVehicle = new QPixmap(pix.copy(125, 50, PHOTO_W, PHOTO_H));
	}
	m_pixScaled = m_pPixVehicle->scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

//-----------------------------------------------------------------------------

