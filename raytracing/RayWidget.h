#ifndef RAYWIDGET_H
#define RAYWIDGET_H

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QPainter>
#include <QCursor>
#include <QLine>

#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include <ctime>

#define WALL_COUNT 10
#define WALL_WIDTH 2
#define RAY_COUNT 5000
#define RAY_WIDTH .1

class RayWidget: public QWidget {
  Q_OBJECT

public:
	RayWidget(QWidget * parent = nullptr);

protected:
	virtual void paintEvent(QPaintEvent *event);

public slots:
	void updatePos();

private:
	QPointF pos;
	QPainter painter;
	std::vector<QLine> walls;
};

#endif
