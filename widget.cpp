#include "widget.h"
#include <QGridLayout>

widget::widget(QWidget *parent)
    : QWidget(parent)
{
    fileOpenButton = new QPushButton("Open file", this);
    fileSaveButton = new QPushButton("Save file", this);
    connect(fileOpenButton, SIGNAL(clicked()), SLOT(onClickedFileOpenButton()));
    connect(fileSaveButton, SIGNAL(clicked()), SLOT(onClickedFileSaveButton()));

    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox = new QHBoxLayout();

    hbox->addWidget(fileOpenButton, 1, Qt::AlignRight);
    hbox->addWidget(fileSaveButton, 0);

    vbox->addStretch(1);
    vbox->addLayout(hbox);
}

widget::~widget()
{
}

void widget::mousePressEvent(QMouseEvent *)
{}

void widget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton))
    {
        QPoint point = event->pos();
        color_of_points.push_back(color);
        points.push_back(point);
        width_of_points.push_back(tthickness);
        update();
    }
}

void widget::mouseReleaseEvent(QMouseEvent *)
{
    color_of_points.push_back(color);
    width_of_points.push_back(tthickness);
    points.push_back({-1,-1});

}

void widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    fileOpenButton->setFixedHeight(0.05 * height());
    fileSaveButton->setFixedHeight(0.05 * height());
    int imageWidth = width();
    int imageHeight = height();
    painter.drawTiledPixmap(START_X_COORDINATE, START_Y_COORDINATE, imageWidth, imageHeight, backgroundImage);
    for (int i = 0; i < (int)points.size() - 1; i++) {
        if (points[i] == QPointF(-1, -1) || points[i + 1] == QPointF(-1, -1)){
            continue;
        }
        QPen pen(color_of_points[i],3);
        if(tthickness!=3 && 1<=tthickness){
        pen.setWidth(width_of_points[i]);
        }
        painter.setPen(pen);
        painter.drawLine(points[i].x(),points[i].y(),points[i+1].x(),points[i+1].y());
        }
}

void widget::onClickedFileOpenButton() {
    points.clear();
    color_of_points.clear();
    width_of_points.clear();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"),"", tr("Images (*.png *.xpm *.jpg)"));
    QImage imageFromFile;
    imageFromFile.load(fileName);
    backgroundImage = QPixmap::fromImage(imageFromFile);
    int imageWidth = width();
    int imageHeight = height();
    backgroundImage = backgroundImage.scaled(imageWidth, imageHeight);
}

void widget::onClickedFileSaveButton() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"), "untitled.png",tr("Images(*.png * .xpm * .jpg"));
    int nameEndPosition = fileName.lastIndexOf('.');
    ++nameEndPosition;
    int nameLength = fileName.length() - nameEndPosition;
    QString format = fileName.right(nameLength);
    int imageWidth = width();
    int imageHeight = height();
    QPixmap imageForSave = QPixmap::grabWidget(this, START_X_COORDINATE, START_Y_COORDINATE, imageWidth, imageHeight);
    imageForSave.save(fileName, format.toUpper().toUtf8());
}
