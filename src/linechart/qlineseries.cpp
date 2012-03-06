#include "qlineseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QLineSeries
    \brief The QLineSeries class is used for making line charts.

    \mainclass

	A line chart is used to show information as a series of data points
	connected by straight lines.

	\image linechart.png

	Creating basic line chart is simple:
	\code
	QLineSeries* series = new QLineSeries();
	series->add(0, 6);
	series->add(2, 4);
	...
	chartView->addSeries(series);
    \endcode
*/

/*!
    \fn virtual QSeriesType QLineSeries::type() const
    \brief Returns type of series.
    \sa QSeries, QSeriesType
*/

/*!
   \fn bool QLineSeries::pointsVisible() const
   \brief  Returns if the points are drawn for this series.
    \sa setPointsVisible()
*/

/*!
   \fn QPen QLineSeries::linePen() const
   \brief  Returns the pen used to draw line connecting points.
    \sa setPen()
*/

/*!
    Constructs empty series object which is a child of \a parent.
    When series object is added to QChartView or QChart instance ownerships is transfered.
*/
QLineSeries::QLineSeries(QObject* parent):QXYSeries(parent),
m_pointsVisible(false)
{

}
/*!
    Destroys the object. Series added to QChartView or QChart instances are owned by those,
    and are deleted when mentioned object are destroyed.
*/
QLineSeries::~QLineSeries()
{
}

/*!
    Sets \a pen used for drawing line connecting points.
*/
void QLineSeries::setLinePen(const QPen& pen)
{
    if(pen!=m_pen){
    m_pen=pen;
    emit updated();
    }
}

/*!
    Sets if data points are \a visible and should be drawn on line.
*/
void QLineSeries::setPointsVisible(bool visible)
{
    if(m_pointsVisible!=visible){
    m_pointsVisible=visible;
    emit updated();
    }
}


QDebug operator<< (QDebug debug, const QLineSeries series)
{
    Q_ASSERT(series.m_x.size() == series.m_y.size());

    int size = series.m_x.size();

    for (int i=0;i<size;i++) {
    debug.nospace() << "(" << series.m_x.at(i) << ','<< series.m_y.at(i) << ") ";
    }
    return debug.space();
}

#include "moc_qlineseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
