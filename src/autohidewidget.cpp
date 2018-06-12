#include "autohidewidget.h"
#include <QEvent>
#include <QPropertyAnimation>
#include <QDesktopWidget>
#include <QApplication>
#include <QMutex>
#include <QMouseEvent>
#include <QLabel>
#include <QIcon>
#include <QDebug>

AutoHideWidget::AutoHideWidget(QWidget *parent)
    : QWidget(parent)
{
    mDesktopWidth = QApplication::desktop()->width();
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    mHandler = new QLabel(QString("TopCam"));
    mHandler->setMaximumSize(50, 20);
    mHandler->setWindowFlags(Qt::FramelessWindowHint /*| Qt::WindowStaysOnTopHint*/);

}

AutoHideWidget::~AutoHideWidget()
{
    mHandler->deleteLater();
}

void AutoHideWidget::hideWidget()
{
    //get the widget's lefttop point map to global
    QPoint globalPos = mapToGlobal(QPoint(0, 0));
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    animation->setStartValue(QRect(globalPos, size()));

    QRect rcEnd;
    if (mEndDirection == Up)
    {
        rcEnd = QRect(globalPos.x(), -height() + 2, width(), height());
        qDebug().noquote() << "__Hide_Up__";
    }
    else if (mEndDirection == Left)
    {
        rcEnd = QRect(-width() + 2, globalPos.y(), width(), height());
        qDebug().noquote() << "__Hide_Left__";
    }
    else if (mEndDirection == Right)
    {
        rcEnd = QRect(mDesktopWidth - 2, globalPos.y(), width(), height());
        qDebug().noquote() << "__Hide_Right__";
    }
    animation->setEndValue(rcEnd);
    animation->start();
}

void AutoHideWidget::showWidget()
{
    QPoint globalPos = mapToGlobal(QPoint(0, 0));

    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    animation->setStartValue(QRect(globalPos, size()));

    QRect rcEnd;
    if (mEndDirection == Up)
    {
        qDebug().noquote() << "__Show_Up__";
        rcEnd = QRect(globalPos.x(), 0, width(), height());
    }
    else if (mEndDirection == Left)
    {
        qDebug().noquote() << "__Show_Left__";
        rcEnd = QRect(0, globalPos.y(), width(), height());
    }
    else if (mEndDirection == Right)
    {
        qDebug().noquote() << "__Show_Right__";
        rcEnd = QRect(mDesktopWidth - width(), globalPos.y(), width(), height());
    }
    animation->setEndValue(rcEnd);
    animation->start();
}

void AutoHideWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    if (mOntheEdge && mIsAutoHide)
    {
        hideWidget();
        mIsHided = true;
        if (mEndDirection == Up) {
            mHandler->setGeometry(mapToGlobal(QPoint(0, 0)).x() + width() / 2 - mHandler->width() / 2, 0, mHandler->width(), mHandler->height());
            mHandler->show();
        }
    }
}

void AutoHideWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    if (mIsHided)
    {
        showWidget();
        mIsHided = false;
    }
}

void AutoHideWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (mMouseLeftPressed) {
        QMutex mutex;
        mutex.lock();

        move(x() + (event->globalPos() - mOldPos).x(), y() + (event->globalPos() - mOldPos).y());
        mOldPos = event->globalPos();

        if (event->globalX() == 0) {
            mOntheEdge = true;
            mEndDirection = Left;
        } else if (event->globalX() == (mDesktopWidth - 1)) {
            mOntheEdge = true;
            mEndDirection = Right;
        } else if (event->globalY() == 0) {
            mOntheEdge = true;
            mEndDirection = Up;
        } else {
            mOntheEdge = false;
            mEndDirection = None;
        }

        mutex.unlock();
    }
}

void AutoHideWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) {
        QMutex mutex;
        mutex.lock();

        mMouseLeftPressed = true;
        mOldPos = event->globalPos();

        mutex.unlock();
    }
}

void AutoHideWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) {
        QMutex mutex;
        mutex.lock();

        mMouseLeftPressed = false;

        mutex.unlock();
    }
}

AutoHideWidgetHandler::AutoHideWidgetHandler(QWidget *iHandleWidget, const QIcon &iIcon, const QString &iText)
{
    mHandWgt = iHandleWidget;
    installEventFilter(mHandWgt);
    mIconLabel = new QLabel;
    mIconLabel->setPixmap(iIcon.pixmap(30, 20));

    mTextLabel = new QLabel;
    mTextLabel->setText(iText);
}

AutoHideWidgetHandler::~AutoHideWidgetHandler()
{

}

bool AutoHideWidgetHandler::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == mHandWgt) {
        if (event->type() == QEvent::MouseMove) {

        } else if (event->type() == QEvent::MouseButtonPress) {

        } else if (event->type() == QEvent::MouseButtonRelease) {

        } else if (event->type() == QEvent::Enter) {

        } else if (event->type() == QEvent::Leave) {

        }
    }
    return false;
}

void AutoHideWidgetHandler::layOn()
{

}
