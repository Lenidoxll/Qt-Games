#pragma once
#include <QWidget>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Snake; }
QT_END_NAMESPACE

class Snake : public QWidget
{
public:
    Snake(QWidget *parent = nullptr);
    ~Snake();
protected:
    void paintEvent(QPaintEvent* e);
    void timerEvent(QTimerEvent* e);
    void keyPressEvent(QKeyEvent* e);
private:
    QImage dot;
    QImage head;
    QImage apple;

    static const int B_WIDTH = 300; //ширина игрового поля
    static const int B_HEIGTH = 300; //высота игрового поля
    static const int DOT_SIZE = 10; //размеры одной части игрового поля
    static const int ALL_DOTS = 900; //максимальное кол-во возможных точек на доске
    static const int RAND_POS = 29; //используется для вычисления случайной позиции яблока
    static const int DELAY = 140; //определяет скорость игры

    int timerId;
    int dots;
    int x_apple;
    int y_apple;

    int x[ALL_DOTS]; //координаты х частей тела змейки
    int y[ALL_DOTS]; //координаты у частей тела змейки

    bool leftDirection;
    bool rightDirection;
    bool upDirection;
    bool downDirection;
    bool inGame;

    void loadImages();
    void initGame();
    void locateApple();
    void checkApple();
    void checkCollision();
    void move();
    void doDrawing();
    void gameOver(QPainter&);

    Ui::Snake *ui;
};
