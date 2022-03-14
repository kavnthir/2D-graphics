#include "RayWidget.h"

bool onSegment(QPointF p, QPointF q, QPointF r) {
    if (q.x() <= std::max(p.x(), r.x()) && q.x() >= std::min(p.x(), r.x()) &&
        q.y() <= std::max(p.y(), r.y()) && q.y() >= std::min(p.y(), r.y())) return true;
    return false;
}

RayWidget::RayWidget(QWidget * parent): QWidget(parent){
	QDesktopWidget desktop;
	int width = desktop.width() * 0.7;
	int height = desktop.height() * 0.7;

	pos = QPointF();

	for(int i = 0; i < WALL_COUNT; i++){
		int start_x = rand() % width;
		int start_y = rand() % height;
		int end_x = rand() % width;
		int end_y = rand() % height;

		walls.push_back(QLine(QPoint(start_x, start_y), QPoint(end_x, end_y)));
	}

}

void RayWidget::updatePos(){
	if(pos == QCursor::pos() - frameGeometry().topLeft())
		return;

	pos = QCursor::pos() - frameGeometry().topLeft();

	this->update();
}

void RayWidget::paintEvent(QPaintEvent *event){

	QDesktopWidget desktop;
	QPainter painter(this);
	QPen pen(Qt::white);
	pen.setWidthF(1);
	painter.setPen(pen);
	QPen penWalls(Qt::gray);
	penWalls.setWidthF(5);

	for(double i = 0; i < 360; i+=.5){

		double x = desktop.width() * 2 * cos(i); 
		double y = desktop.width() * 2 * sin(i); 

		QLineF ray(pos, QPointF(x, y));	
		QPointF intersect;

		for(int j = 0;  j < WALL_COUNT; j++){
			double x1 = ray.x1();
			double x2 = ray.x2();
			double x3 = walls[j].x1();
			double x4 = walls[j].x2();
			double y1 = ray.y1();
			double y2 = ray.y2();
			double y3 = walls[j].y1();
			double y4 = walls[j].y2();

			double D = ( x1 - x2 )*( y3 - y4 ) - ( y1 - y2 )*( x3 - x4 );	

			double xN = (x1*y2 - y1*x2)*(x3 - x4) - (x1 -x2)*(x3*y4 - y3*x4);
			double yN = (x1*y2 - y1*x2)*(y3 - y4) - (y1 -y2)*(x3*y4 - y3*x4);

			QPointF temp = QPointF( xN / D, yN / D );

			if(!onSegment(walls[j].p1(), temp, walls[j].p2()) || !onSegment(pos, temp, QPointF(x,y))){
				continue;
			}

			QLineF calc(intersect, pos);
			QLineF calc2(temp, pos);
			if(intersect.isNull() || calc.length() > calc2.length()){
				intersect = temp;
			}

		}

		if(!intersect.isNull()){
			painter.drawLine(pos, intersect);
			continue;
		}
		painter.drawLine(pos, QPointF(x, y));
	}

	painter.setPen(penWalls);
	painter.resetTransform();
	for(int i = 0; i < WALL_COUNT; i++){
		painter.drawLine(walls[i]);
	}
	
}


