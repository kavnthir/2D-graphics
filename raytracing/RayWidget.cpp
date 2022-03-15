#include "RayWidget.h"

bool onSegment(QPointF p, QPointF q, QPointF r) {
    if (q.x() <= std::max(p.x(), r.x()) && q.x() >= std::min(p.x(), r.x()) &&
        q.y() <= std::max(p.y(), r.y()) && q.y() >= std::min(p.y(), r.y())) return true;
    return false;
}

RayWidget::RayWidget(QWidget * parent): QWidget(parent){

	// cursor position is null
	pos = QPointF();

	// seed random number generator
	srand(time(0));

	// randomly spawn walls
	
	int width = QDesktopWidget().width() * 0.7;
	int height = QDesktopWidget().height() * 0.7;

	for(int i = 0; i < WALL_COUNT; i++){
		int start_x = rand() % width;
		int start_y = rand() % height;
		int end_x = rand() % width;
		int end_y = rand() % height;

		walls.push_back(QLine(QPoint(start_x, start_y), QPoint(end_x, end_y)));
	}

}

void RayWidget::updatePos(){
	// if cursor has moved, redraw
	if(pos == QCursor::pos() - frameGeometry().topLeft())
		return;
	pos = QCursor::pos() - frameGeometry().topLeft();
	this->update();
}

void RayWidget::paintEvent(QPaintEvent *event){

	QDesktopWidget desktop;
	QPainter painter(this);

	QPen pen(Qt::white);
	pen.setWidthF(RAY_WIDTH);

	QPen penWalls(Qt::gray);
	penWalls.setWidthF(WALL_WIDTH);

	painter.setPen(pen);
	for(double i = 0; i < 2 * M_PI; i+= 2 * M_PI / RAY_COUNT){

		// convert from polar form
		double x = desktop.width() * 2 * cos(i); 
		double y = desktop.width() * 2 * sin(i); 

		QLineF ray(pos, QPointF(x, y));	
		QPointF intersect;

		for(int j = 0;  j < WALL_COUNT; j++){

			// return point at which ray intersects line
			double x1 = ray.x1();
			double x2 = ray.x2();
			double x3 = walls[j].x1();
			double x4 = walls[j].x2();

			double y1 = ray.y1();
			double y2 = ray.y2();
			double y3 = walls[j].y1();
			double y4 = walls[j].y2();

			double xN = (x1*y2 - y1*x2)*(x3 - x4) - (x1 -x2)*(x3*y4 - y3*x4);
			double yN = (x1*y2 - y1*x2)*(y3 - y4) - (y1 -y2)*(x3*y4 - y3*x4);
			double D = ( x1 - x2 )*( y3 - y4 ) - ( y1 - y2 )*( x3 - x4 );	

			QPointF temp = QPointF( xN / D, yN / D );

			// check if the point lives on the line segment defined by the wall
			if(!onSegment(walls[j].p1(), temp, walls[j].p2()))
				continue;
			if(!onSegment(pos, temp, QPointF(x,y)))
				continue;

			// if current wall intersection is closer than previous ones, it is the new intersect
			QLineF min_ray(intersect, pos);
			QLineF current_ray(temp, pos);
			if(intersect.isNull() || min_ray.length() > current_ray.length())
				intersect = temp;

		}

		// if ray intersects wall, draw that point, otherwise draw max length line
		if(!intersect.isNull())
			painter.drawLine(pos, intersect);
		else
			painter.drawLine(pos, QPointF(x, y));
}

	// draw walls
	painter.setPen(penWalls);
	for(int i = 0; i < WALL_COUNT; i++)
		painter.drawLine(walls[i]);
	
}

