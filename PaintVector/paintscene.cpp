#include "paintscene.h"
#include "square.h"
#include "romb.h"
#include "triangle.h"
#include <QFile>
#include <QTextStream>
#include <QBrush>
#include <QPen>
#include <QtMath>

static constexpr int BALL_SIZE = 30;
static constexpr int FRAME_RATE = 16;

paintScene::paintScene(QObject *parent)
    : QGraphicsScene(parent)
{
    ballTimer = new QTimer(this);
    connect(ballTimer, &QTimer::timeout, this, &paintScene::moveBalls);
    ballTimer->start(FRAME_RATE);
}

void paintScene::clear()
{
    for (auto &b : balls) {
        removeItem(b.item);
        delete b.item;
    }
    balls.clear();
    qDeleteAll(Figures);
    Figures.clear();
    if (tempFigure) {
        removeItem(tempFigure);
        delete tempFigure;
        tempFigure = nullptr;
    }
    QGraphicsScene::clear();
    if (!ballTimer->isActive())
        ballTimer->start(16);
}

paintScene::~paintScene()
{
    clear();
    delete ballTimer;
}


void paintScene::setPenColor(const QColor &color) {
    penColor = color;
}
int paintScene::typeFigure() const {
    return m_typeFigure;
}
void paintScene::setTypeFigure(int type) {
    m_typeFigure = type;
}
void paintScene::setDrawMode(DrawMode mode) {
    m_drawMode = mode;
}
paintScene::DrawMode paintScene::drawMode() const {
    return m_drawMode;
}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (m_drawMode == ModeDraw) {
        addEllipse(event->scenePos().x()-5, event->scenePos().y()-5, 10, 10, QPen(Qt::NoPen), QBrush(penColor));
        previousPoint = event->scenePos();
    } else {
        if (tempFigure) { removeItem(tempFigure); delete tempFigure; }
        switch (m_typeFigure) {
        case SquareType:   tempFigure = new Square(event->scenePos()); break;
        case RombType:     tempFigure = new Romb(event->scenePos()); break;
        case TriangleType: tempFigure = new Triangle(event->scenePos()); break;
        }
        if (tempFigure) {
            tempFigure->setStartPoint(event->scenePos());
            tempFigure->setEndPoint(event->scenePos());
            tempFigure->setPenColor(penColor);
            addItem(tempFigure);
        }
    }
}

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (m_drawMode == ModeDraw) {
        addLine(previousPoint.x(), previousPoint.y(), event->scenePos().x(), event->scenePos().y(),
                QPen(penColor,10,Qt::SolidLine,Qt::RoundCap));
        previousPoint = event->scenePos();
    } else if (tempFigure) {
        tempFigure->setEndPoint(event->scenePos());
    }
}

void paintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (m_drawMode == ModeFigure && tempFigure) {
        tempFigure->setEndPoint(event->scenePos());
        Figures.push_back(tempFigure);
        tempFigure = nullptr;
    }
}

void paintScene::saveToFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    for (auto &f : Figures) {
        out << f->metaObject()->className() << " "
            << f->startPoint().x() << " " << f->startPoint().y() << " "
            << f->endPoint().x()   << " " << f->endPoint().y()   << " "
            << f->WhatCa().name()  << "\n";
    }
    for (const auto &b : balls) {
        QPointF pos = b.item->pos();
        QPointF v   = b.velocity;
        QColor c    = b.item->brush().color();
        out << "Ball" << " "
            << pos.x() << " " << pos.y() << " "
            << v.x()   << " " << v.y()   << " "
            << c.red() << "," << c.green() << "," << c.blue()
            << "\n";
    }

    file.close();
}

void paintScene::loadFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    clear();
    qDeleteAll(Figures);
    Figures.clear();
    balls.clear();

    while (!in.atEnd()) {
        auto parts = in.readLine().split(' ');
        if (parts.size() == 6 && parts[0] == "Ball") {
            double x  = parts[1].toDouble();
            double y  = parts[2].toDouble();
            double vx = parts[3].toDouble();
            double vy = parts[4].toDouble();
            QStringList rgb = parts[5].split(',');
            int r = rgb.value(0).toInt();
            int g = rgb.value(1).toInt();
            int b = rgb.value(2).toInt();

            QGraphicsEllipseItem *item = new QGraphicsEllipseItem(0, 0, BALL_SIZE, BALL_SIZE);
            item->setBrush(QBrush(QColor(r, g, b)));
            item->setPen(QPen(Qt::black));
            addItem(item);
            item->setPos(x, y);
            Ball ball;
            ball.item     = item;
            ball.velocity = QPointF(vx, vy);
            balls.append(ball);
        }
        else if (parts.size() == 6 && (parts[0] == "Square" || parts[0] == "Romb" || parts[0] == "Triangle")) {
            QPointF st(parts[1].toDouble(), parts[2].toDouble()),
                en(parts[3].toDouble(), parts[4].toDouble());
            QColor col(parts[5]);
            Figure *fig = nullptr;
            if      (parts[0] == "Square")   fig = new Square(st);
            else if (parts[0] == "Romb")     fig = new Romb(st);
            else if (parts[0] == "Triangle") fig = new Triangle(st);
            if (fig) {
                fig->setStartPoint(st);
                fig->setEndPoint(en);
                fig->setPenColor(col);
                addItem(fig);
                Figures.push_back(fig);
            }
        }
    }

    file.close();
}

void paintScene::addBall() {
    QGraphicsEllipseItem *item=new QGraphicsEllipseItem(0,0,BALL_SIZE,BALL_SIZE);
    item->setBrush(QBrush(penColor));
    item->setPen(QPen(Qt::black));
    addItem(item);
    QRectF sc=sceneRect();
    double rx=QRandomGenerator::global()->generateDouble();
    double ry=QRandomGenerator::global()->generateDouble();
    item->setPos(sc.left()+rx*(sc.width()-BALL_SIZE), sc.top()+ry*(sc.height()-BALL_SIZE));
    Ball b;
    double angle=QRandomGenerator::global()->generateDouble()*2*M_PI;
    double speed=2.0+QRandomGenerator::global()->generateDouble()*3.0;
    b.item=item;
    b.velocity=QPointF(qCos(angle)*speed,qSin(angle)*speed);
    balls.append(b);
}

void paintScene::moveBalls() {
    if (balls.isEmpty()) return;
    QRectF sc=sceneRect();
    for (auto &b:balls) {
        QPointF pos=b.item->pos()+b.velocity;
        double x=pos.x(), y=pos.y();
        if (x<sc.left()||x+BALL_SIZE>sc.right()) b.velocity.setX(-b.velocity.x());
        if (y<sc.top()||y+BALL_SIZE>sc.bottom()) b.velocity.setY(-b.velocity.y());
        b.item->setPos(qBound(sc.left(),x,sc.right()-BALL_SIZE), qBound(sc.top(),y,sc.bottom()-BALL_SIZE));
    }
    int n=balls.size();
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            handleCollision(balls[i],balls[j]);
        }
    }
}

void paintScene::handleCollision(Ball &b1,Ball &b2){
    QPointF c1=b1.item->pos()+QPointF(BALL_SIZE/2,BALL_SIZE/2);
    QPointF c2=b2.item->pos()+QPointF(BALL_SIZE/2,BALL_SIZE/2);
    QPointF delta=c2-c1;
    double dist=qSqrt(delta.x()*delta.x()+delta.y()*delta.y());
    if(dist<=BALL_SIZE&&dist>0){
        QPointF nvec=delta/dist;
        QPointF tvec(-nvec.y(),nvec.x());
        double v1n=QPointF::dotProduct(b1.velocity,nvec);
        double v1t=QPointF::dotProduct(b1.velocity,tvec);
        double v2n=QPointF::dotProduct(b2.velocity,nvec);
        double v2t=QPointF::dotProduct(b2.velocity,tvec);

        //v1n *= -1; v2n *= -1;
        double tmp=v1n; v1n=v2n; v2n=tmp;

        b1.velocity=v1n*nvec+v1t*tvec;
        b2.velocity=v2n*nvec+v2t*tvec;
        double overlap=BALL_SIZE-dist;
        QPointF shift=nvec*(overlap/2+0.5);
        b1.item->moveBy(-shift.x(),-shift.y());
        b2.item->moveBy( shift.x(), shift.y());
    }
}
