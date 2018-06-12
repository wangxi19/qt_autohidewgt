#ifndef AUTOHIDEWIDGET_H
#define AUTOHIDEWIDGET_H

#include <QWidget>

class QEvent;
class QPoint;
class QLabel;
class QIcon;

class AutoHideWidget : public QWidget
{
    Q_OBJECT

    enum EndDirection {
        Up,
        Left,
        Right,
        None
    };

friend class AutoHideWidgetHandler;

public:
    explicit AutoHideWidget(QWidget *parent = nullptr);
    ~AutoHideWidget();
signals:

public slots:
    void hideWidget();
    void showWidget();
protected:
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    EndDirection mEndDirection;
    int mDesktopWidth = 0;
    bool mIsAutoHide = true;
    bool mMouseLeftPressed = false;
    bool mOntheEdge = false;
    bool mIsHided = false;
    QPoint mOldPos;
    AutoHideWidgetHandler *mHandler = nullptr;
};

class AutoHideWidgetHandler : public QWidget
{
    Q_OBJECT

public:
    explicit AutoHideWidgetHandler(QWidget *iHandleWidget, const QIcon &iIcon = QIcon(), const QString &iText = QString());
    ~AutoHideWidgetHandler();
protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;
private:
    QWidget *mHandWgt = nullptr;
    QLabel *mIconLabel = nullptr;
    QLabel *mTextLabel = nullptr;

    bool mMouseLeftPressed = false;
};

#endif // AUTOHIDEWIDGET_H
