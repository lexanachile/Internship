#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QVector>
#include <QRandomGenerator>
#include "figure.h"

class paintScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit paintScene(QObject *parent = nullptr);
    ~paintScene() override;
    void clear();
    void setPenColor(const QColor &color);
    int typeFigure() const;
    void setTypeFigure(int type);
    void saveToFile(const QString &filePath);
    void loadFromFile(const QString &filePath);
    void addBall();
    enum FigureTypes { SquareType, RombType, TriangleType };
    enum DrawMode     { ModeDraw, ModeFigure };
    void setDrawMode(DrawMode mode);
    DrawMode drawMode() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private slots:
    void moveBalls();

private:
    QPointF previousPoint;
    QColor penColor = Qt::red;
    Figure *tempFigure = nullptr;
    int m_typeFigure = SquareType;
    DrawMode m_drawMode = ModeDraw;
    QVector<Figure*> Figures;
    struct Ball {
        QGraphicsEllipseItem *item;
        QPointF velocity;
    };
    QVector<Ball> balls;
    QTimer *ballTimer = nullptr;
    void handleCollision(Ball &b1, Ball &b2);
};

#endif // PAINTSCENE_H
