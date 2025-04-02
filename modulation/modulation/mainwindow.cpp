#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    s.f = 110.00;
    s.fd = 1000;

    s.symbol_speed = 10;

    s.set_phase_states(4);

    // size_t samples_size = 1000;

    // auto v = s({1,1,0,1,1,0,1,1,0,1,1,0});
    auto v = s({1,1, 1,1, 0,0, 1,1, 1,1, 0,0, 1,1, 1,1, 0,0, 1,1});

    // std::vector<short> v(samples_size);

    size_t samples_size = v.size();

    QVector<double> vx(samples_size);
    QVector<double> vy(samples_size);

    for (auto i = 0; i < vx.size(); ++i)
    {
        // s.f = 110 + double(i)*(220-110)/vx.size();

        // v[i] = s();
        vy[i] = v[i];
        vx[i] = i;
    }

    auto g = ui->widget->addGraph();
        ui->widget_2->addGraph();
        ui->widget_3->addGraph();
        ui->widget_4->addGraph();
        ui->widget_5->addGraph();
        ui->widget_6->addGraph();
        ui->widget_7->addGraph();

        QCPMarginGroup* group = new QCPMarginGroup(ui->widget);

        ui->widget->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight,group);
        ui->widget_2->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight,group);
        ui->widget_3->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight,group);
        ui->widget_4->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight,group);
        ui->widget_5->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight,group);
        ui->widget_6->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight,group);


        QSharedPointer<QCPAxisTicker> ticker(new QCPAxisTickerPi());
        ui->widget_4->graph(0)->valueAxis()->setTicker(ticker);

        // g->addData(vx,vy,true);
        // ui->widget->xAxis2->
        ui->widget->yAxis->setLabel("Модулированный сигнал");
        ui->widget_2->yAxis->setLabel("I компонента");
        ui->widget_3->yAxis->setLabel("Q компонента");
        ui->widget_4->yAxis->setLabel("Фаза сигнала");
        ui->widget_5->yAxis->setLabel("Сигнал ошибки");
        ui->widget_6->yAxis->setLabel("Сигнал ошибки (большой масштаб)");

        ui->widget_7->yAxis->setLabel("Q компонента");
        ui->widget_7->xAxis->setLabel("I компонента");

        ui->widget_7->graph(0)->setLineStyle(QCPGraph::LineStyle::lsNone);
        ui->widget_7->graph(0)->setScatterStyle(QCPScatterStyle::ssCross);


    g->rescaleAxes();


    // ui->widget->replot();
    // ui->widget_2->replot();


    // WAVHEADER wh(1000);
    // wh.sampleRate = 1000;

    // std::ofstream str("audio.wav");
    // wh.write(str);

    // for (auto i = 0 ; i < vy.size(); ++i)
    //     str.write((char*)(&v[i]),2);
    // str.close();

    connect(&timer,SIGNAL(timeout()),this,SLOT(timer_event()));
    timer.setInterval(1000/120);
    timer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timer_event(){

    static double phase_offset = 0.0;
    s.phase = 0;
    s.phase += phase_offset;

    phase_offset +=0.001;
    phase_offset = fmod(phase_offset,2*M_PI);

    s.set_phase_states(get_PM_size());

    auto v = s(get_message());

    size_t samples_size = v.size();

    QVector<double> vx(samples_size);
    QVector<double> vy(samples_size);

    for (auto i = 0; i < vx.size(); ++i)
    {
        vy[i] = v[i];
        vx[i] = i;
    }

    static PM_demodulator d;

    d.f = 110.0;
    d.fd = 1000;
    d.bit_speed = 10;

    auto v_ = d(v.begin(),v.end());

    QVector<double> vx_2(v_[0].size());
    QVector<double> vy_2(v_[0].size());
    QVector<double> vy_3(v_[0].size());
    QVector<double> vy_4(v_[0].size());
    QVector<double> vy_5(v_[0].size());

    for (auto i = 0; i < v_[0].size(); ++i)
    {
        vy_2[i] = v_[0][i];
        vy_3[i] = v_[1][i];
        vy_4[i] = atan2(v_[0][i],v_[1][i]);
        vy_5[i] = v_[1][i]*v_[0][i] / double(std::numeric_limits<int>::max());
        vx_2[i] = i;
    }

    double v__ = vy_5[5];
    error_with_time.push_back(v__);

    QVector<double> vy_6(error_with_time.begin(),error_with_time.begin() + error_with_time.size());
    QVector<double> vx_6(error_with_time.size());
    std::iota(vx_6.begin(),vx_6.end(),1);

    auto g = ui->widget->graph(0);
    g->setData(vx,vy,true);
    g->rescaleKeyAxis();
    g->rescaleValueAxis(true);
    ui->widget->replot();

    g = ui->widget_2->graph(0);
    g->setData(vx_2,vy_2,true);
    g->rescaleKeyAxis(false);
    g->rescaleValueAxis(true);
    g->setPen(QPen(Qt::GlobalColor::darkGreen));
    ui->widget_2->replot();


    g = ui->widget_3->graph(0);
    g->setData(vx_2,vy_3,true);
    g->rescaleKeyAxis(false);
    g->rescaleValueAxis(true);
    g->setPen(QPen(Qt::GlobalColor::darkGreen));
    ui->widget_3->replot();

    g = ui->widget_4->graph(0);
    g->setData(vx_2,vy_4,true);
    g->rescaleKeyAxis(false);
    g->rescaleValueAxis(true);
    g->valueAxis()->setRange(-M_PI,M_PI);
    ui->widget_4->replot();

    g = ui->widget_5->graph(0);
    g->setData(vx_2,vy_5,true);
    g->rescaleKeyAxis(false);
    g->rescaleValueAxis(true);
    g->valueAxis()->setRange(-1,1);
    ui->widget_5->replot();

    g = ui->widget_6->graph(0);
    g->setData(vx_6,vy_6);
    g->rescaleKeyAxis(false);
    g->rescaleValueAxis(true);
    g->valueAxis()->setRange(-1,1);
    g->setPen(QPen(Qt::GlobalColor::red));
    ui->widget_6->replot();

    g = ui->widget_7->graph(0);
    g->setData(vy_2,vy_3);
    // g->rescaleKeyAxis(true);
    // g->rescaleValueAxis(true);
    g->keyAxis()->setRange(4*std::numeric_limits<short>::min(),4*std::numeric_limits<short>::max());
    g->valueAxis()->setRange(4*std::numeric_limits<short>::min(),4*std::numeric_limits<short>::max());
    ui->widget_7->replot();


    ui->LineEdit_2->setText(QString::number(phase_offset));
    ui->LineEdit_3->setText(QString::number(d.phase));
}

std::vector<bool> MainWindow::get_message()
{
    auto s = ui->LineEdit->text();

    std::vector<bool> v(s.size());

    for (auto i = 0; i < s.size(); ++i)
    {
        v[i] = (s[i] == '1')? 1:0;
    }

    return v;
}

int MainWindow::get_PM_size()
{
    auto v = ui->radioButton->isChecked();

    return v? 2:4;
}
