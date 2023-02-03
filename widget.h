#ifndef WIDGET_H
#define WIDGET_H

#include <QPainter>
#include <QMouseEvent>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QColorDialog>
#include <QFileDialog>

constexpr int START_X_COORDINATE = 0;
constexpr int START_Y_COORDINATE = 0;

class widget : public QWidget
{
    Q_OBJECT

public:
    widget(QWidget *parent = nullptr);
    ~widget();
    void setColor(const QColor& color_) {color=color_;}
    void setThickness(int thickness_) {tthickness=thickness_;}
protected:

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

protected slots:
    void onClickedFileOpenButton();
    void onClickedFileSaveButton();

private:
    int tthickness=3;
    QColor color;
    QPainter *painter;
    std::vector<QPoint> points;
    std::vector<QColor> color_of_points;
    std::vector<int> width_of_points;
    QPushButton* fileOpenButton;
    QPushButton* fileSaveButton;
    QPixmap backgroundImage;
};
#endif // WIDGET_H
