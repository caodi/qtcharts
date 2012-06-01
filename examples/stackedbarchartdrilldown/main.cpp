/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui/QApplication>
#include <QMainWindow>
#include <QChartView>
#include <QBarSet>
#include <QLegend>
#include "drilldownseries.h"
#include "drilldownchart.h"

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
//! [1]
    QApplication a(argc, argv);
    QMainWindow window;
//! [1]

//! [2]
    DrilldownChart* drilldownChart =  new DrilldownChart();
    drilldownChart->setTheme(QChart::ChartThemeBlueIcy);
    drilldownChart->setAnimationOptions(QChart::SeriesAnimations);
//! [2]

//! [3]
    // Define categories
    QStringList months;
    months << "May" << "Jun" << "Jul" << "Aug" << "Sep";
    QStringList weeks;
    weeks << "week 1" << "week 2" << "week 3" << "week 4";
    QStringList plants;
    plants << "Habanero" << "Lemon Drop" << "Starfish" << "Aji Amarillo";
//! [3]

//! [4]
    // Create drilldown structure
    DrilldownBarSeries* seasonSeries = new DrilldownBarSeries(months, drilldownChart);
    seasonSeries->setName("Crop by month - Season");

    // Each month in season series has drilldown series for weekly data
    for (int month=0; month < months.count(); month++) {

        // Create drilldown series for every week
        DrilldownBarSeries* weeklySeries = new DrilldownBarSeries(weeks, drilldownChart);
        seasonSeries->mapDrilldownSeries(month, weeklySeries);

        // Drilling down from weekly data brings us back to season data.
        for (int week=0; week < weeks.count(); week++) {
            weeklySeries->mapDrilldownSeries(week, seasonSeries);
            weeklySeries->setName(QString("Crop by week - " + months.at(month)));
        }

        // Use right click signal to implement drilldown
        QObject::connect(weeklySeries, SIGNAL(clicked(QBarSet*,int)), drilldownChart, SLOT(handleClicked(QBarSet*,int)));
    }

    // Enable drilldown from season series using right click.
    QObject::connect(seasonSeries, SIGNAL(clicked(QBarSet*,int)), drilldownChart, SLOT(handleClicked(QBarSet*,int)));
//! [4]

//! [5]
    // Fill monthly and weekly series with data
    foreach (QString plant, plants) {
        QBarSet* monthlyCrop = new QBarSet(plant);
        for (int month=0; month<months.count(); month++) {
            QBarSet* weeklyCrop = new QBarSet(plant);
            for (int week=0; week<weeks.count(); week++) {
                *weeklyCrop << (qrand() % 20);
            }
            // Get the drilldown series from season series and add crop to it.
            seasonSeries->drilldownSeries(month)->append(weeklyCrop);
            *monthlyCrop << weeklyCrop->sum();
        }
        seasonSeries->append(monthlyCrop);
    }
//! [5]

//! [6]
    // Show season series in initial view
    drilldownChart->changeSeries(seasonSeries);
    drilldownChart->setTitle(seasonSeries->name());
//! [6]

//! [7]
    drilldownChart->axisX()->setGridLineVisible(false);
    drilldownChart->axisY()->setNiceNumbersEnabled(true);
    drilldownChart->legend()->setVisible(true);
    drilldownChart->legend()->setAlignment(Qt::AlignBottom);
//! [7]

    QChartView *chartView = new QChartView(drilldownChart);
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}

