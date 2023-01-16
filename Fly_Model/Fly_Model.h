#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtCore/qmath.h>
#include<QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Enter_conditions_button_clicked();

    void on_Draw_graph_button_clicked();

    void on_Clear_button_clicked();

private:
    Ui::MainWindow *ui;

    qreal g;
    qreal throw_angle;
    qreal start_velocity;
    qint16 X_axis_max;
    qint16 Y_axis_max;
    qint16 graphs_count = -1;
};
#endif // MAINWINDOW_H
