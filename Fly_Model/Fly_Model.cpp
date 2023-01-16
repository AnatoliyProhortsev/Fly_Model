#include "Fly_Model.h"
#include "ui_Fly_Model.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Enter_conditions_button_clicked()
{
    try {
        this->g = ui->Gravity_edit->text().toDouble();
        this->throw_angle = ui->Angle_edit->text().toDouble();
        this->start_velocity = ui->Speed_edit->text().toDouble();
        this->X_axis_max = ui->X_axis_max_edit->text().toInt();
        this->Y_axis_max = ui->Y_axis_max_edit->text().toInt();

        if(this->g == 0 || this->throw_angle == 0 || this->start_velocity == 0
                || this->X_axis_max == 0
                || this->Y_axis_max == 0)
            throw "error";
    }  catch (...) {
        QMessageBox errMsgBox;
        errMsgBox.setWindowTitle("Ошибка!");
        errMsgBox.setText("Неверные начальные значения.");
        errMsgBox.exec();
        return;
    }
    this->throw_angle = qDegreesToRadians(throw_angle);

    ui->plot_view->xAxis->setRange(0, this->X_axis_max);
    ui->plot_view->yAxis->setRange(0, this->Y_axis_max);
    ui->plot_view->replot();

    ui->Draw_graph_button->setEnabled(true);
    ui->Get_info_button->setEnabled(true);
    ui->Clear_button->setEnabled(true);
}

void MainWindow::on_Draw_graph_button_clicked()
{
    ui->plot_view->addGraph();
    graphs_count++;

    QPointF point;
    qreal fly_time = 2 * this->start_velocity * qSin(throw_angle) / g / 100;
    for(int i = 0; i <= 100; i++)
    {
        point.setX(this->start_velocity * (i*fly_time) * qCos(this->throw_angle));
        point.setY((this->start_velocity * (i*fly_time) * qSin(this->throw_angle) - (this->g / 2 * (i*fly_time) * (i*fly_time))));
        qDebug() << "X: " + QString::number(point.x()) + " | Y: " + QString::number(point.y());

        ui->plot_view->graph(graphs_count)->addData(point.x(), point.y());
    }

    ui->plot_view->graph(graphs_count)->setPen(QPen(Qt::red));

    ui->plot_view->replot();

    ui->label->setText("Макс. высота полёта: " + QString::number(this->start_velocity * this->start_velocity * qSin(throw_angle)* qSin(throw_angle) / 2 / this->g));
    ui->label_3->setText("Время полёта: " + QString::number(fly_time));
    ui->label_2->setText("Длина полёта:");
}

void MainWindow::on_Clear_button_clicked()
{
    if(graphs_count >= 0)
    {
        ui->plot_view->removeGraph(graphs_count--);
        ui->plot_view->replot();
    }
    else
    {
        QMessageBox errMsgBox;
        errMsgBox.setWindowTitle("Ошибка!");
        errMsgBox.setText("Не осталось графиков для удаления.");
        errMsgBox.exec();
    }
}
