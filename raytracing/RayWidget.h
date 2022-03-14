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

#define WALL_COUNT 10

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
