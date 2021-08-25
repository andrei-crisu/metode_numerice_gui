#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include<QCloseEvent>
#include<QFileDialog>
#include "particular_interpreter.h"
#include "from_internal_to_user.h"
#define  APP_NAME "Metode Numerice"


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
    void closeEvent(QCloseEvent *event);

    void on_home_clicked();

    void on_inapoi_clicked();

    void on_helpButton_clicked();

    void on_settingButton_clicked();

    void on_metodaLuiChio_clicked();

    void on_metodaLuiGauss_clicked();

    void on_run_button_clicked();

    void on_metodaLR_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

    void on_interpolareNewton_clicked();

    void on_pushButton_11_clicked();

    void on_integrale_metoda_trapezului_button_clicked();

    void on_mas_clicked();

    void on_newtown_aproximation_clicked();

    void on_home_2_clicked();

    void on_back_button_clicked();

    void on_exit_clicked();

    void on_help_clicked();

    void on_settings_clicked();

    void on_home_3_clicked();

    void on_back_button_2_clicked();

    void on_exitButton2_clicked();

    void on_settings_2_clicked();

    void on_home_4_clicked();

    void on_back_button_3_clicked();

    void on_exit_2_clicked();
    void on_help_3_clicked();

    void on_help_2_clicked();

    void on_settings2_clicked();

    void on_from_file_button_clicked();

    void on_clear_status_window_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_14_clicked();

    void on_simpson_button_clicked();

    void on_back_button_4_clicked();

    void on_back_button_5_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
