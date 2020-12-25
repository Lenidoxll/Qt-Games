#include "snake.h"
#include "ui_snake.h"
#include <QPainter>
#include <QTime>

Snake::Snake(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Snake)
{
    setStyleSheet("background-color:black;");
    leftDirection = false;
    rightDirection = false;
    upDirection = false;
    downDirection = false;
    inGame = true;

    resize(B_WIDTH, B_HEIGTH);
    loadImages();
    initGame();

    ui->setupUi(this);
}

Snake::~Snake()
{
    delete ui;
}

void Snake::loadImages() {
    dot.load("dot.png");
    head.load("head.png");
    apple.load("apple.png");
}

void Snake::initGame() {
    dots = 3;
    for (int z = 0; z < dots; z++) {
        x[z] = 50 - z*10;
        y[z] = 50;
    }
    locateApple();
    timerId = startTimer(DELAY);
}

void Snake::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);
    doDrawing();
}

void Snake::doDrawing() {
    QPainter painter(this);

    if (inGame) {
        painter.drawImage(x_apple, y_apple, apple);
        for (int z = 0; z < dots; z++) {
            if (z == 0)
                painter.drawImage(x[z], y[z], head);
            else
                painter.drawImage(x[z], y[z], dot);
        }
    } else
        gameOver(painter);
}

void Snake::gameOver(QPainter& painter) {
    QString message = "Game over!";
    QFont font("Courier", 20, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    painter.setPen(QColor(Qt::white));
    painter.setFont(font);
    int h = height();
    int w = width();

    painter.translate(QPoint(w/2, h/2));
    painter.drawText(-textWidth/2, 0, message);
}

void Snake::checkApple() {
    if ((x[0] == x_apple) && (y[0] == y_apple)) {
        dots++;
        locateApple();
    }
}

void Snake::move() {
    for (int z = dots; z > 0; z--) {
        x[z] = x[z-1];
        y[z] = y[z-1];
    }

    if (leftDirection)
        x[0] -= DOT_SIZE;
    if (rightDirection)
        x[0] += DOT_SIZE;
    if (upDirection)
        y[0] -= DOT_SIZE;
    if (downDirection)
        y[0] += DOT_SIZE;
}

void Snake::checkCollision() {
    for (int z = dots; z > 3; z--) {
        if ((x[0] == x[z]) && (y[0] == y[z]))
            inGame = false;
    }
    if ((y[0] >= B_HEIGTH) | (y[0] < 0) | (x[0] >= B_WIDTH) | (x[0] < 0))
        inGame = false;
    if (!inGame)
        killTimer(timerId);
}

void Snake::locateApple() {
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());
    int r = qrand() % RAND_POS;
    x_apple = (r * DOT_SIZE);
    r = qrand() % RAND_POS;
    y_apple = (r * DOT_SIZE);
}

void Snake::timerEvent(QTimerEvent* e) {
    Q_UNUSED(e);
    if(inGame) {
        checkApple();
        checkCollision();
        move();
    }
    repaint();
}

void Snake::keyPressEvent(QKeyEvent* e) {
    int key = e->key();

    if ((key == Qt::Key_Left) && (!rightDirection)) {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }
    if ((key == Qt::Key_Right) && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }
    if ((key == Qt::Key_Up) && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }
    if ((key == Qt::Key_Down) && (!upDirection)) {
        downDirection = true;
        leftDirection = false;
        rightDirection = false;
    }
    QWidget::keyPressEvent(e);
}
