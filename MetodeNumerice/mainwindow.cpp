#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtDebug>

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

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    QMessageBox msgBox;
    msgBox.setText(tr("Închideți aplicația?"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("Da"), QMessageBox::YesRole);
    QAbstractButton* pButtonNo = msgBox.addButton(tr("Nu"), QMessageBox::NoRole);
    //No button
    pButtonNo->setMinimumSize(80,30);
    pButtonNo->setStyleSheet(
                "QAbstractButton {"
                "background-color: rgb(236, 236, 236);"
                "color: rgb(40, 46, 58);"
                "border-color: rgb(167, 171, 191);"
                "border-style:solid;"
                "border-width:1px;}"
                "QAbstractButton:hover:!pressed {"
                "background-color: rgb(255, 83, 73);}");

    //Yes button
    pButtonYes->setMinimumSize(80,30);
    pButtonYes->setStyleSheet(
                "QAbstractButton {"
                "background-color: rgb(236, 236, 236);"
                "color: rgb(40, 46, 58);"
                "border-color: rgb(167, 171, 191);"
                "border-style:solid;"
                "border-width:1px;}"
                "QAbstractButton:hover:!pressed {"
                "background-color: rgb(73, 255, 83);}");

    //msgBox
    QPixmap exportSuccess(":images/exit_32.png");
    QIcon icon(":icons/math_icon.png");
    QFont font("Consolas",14);
    msgBox.setFont(font);
    msgBox.setWindowIcon(icon);
    msgBox.setIconPixmap(exportSuccess);
    msgBox.setStyleSheet(
                "QLabel{min-width: 100px;"
                "text-align:left"
                "min-height: 60px;  }"
                "QMessageBox{"
                "background-color: rgb(236, 236, 236);"
                "color: rgb(40, 46, 58);}");

    msgBox.exec();
    if (msgBox.clickedButton()==pButtonYes)
    {
       event->accept();
    }

}


void MainWindow::on_home_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_inapoi_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_helpButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_3->setCurrentIndex(17);
}

void MainWindow::on_settingButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_metodaLuiChio_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_metodaLuiGauss_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_run_button_clicked()
{
    QString str="",str1="",str2="",str3="",str4="";
    ui->outputWindow->clear();
    int index=-1;
    index=ui->stackedWidget_2->currentIndex();
    bool runStatus=false;
    QString message="",result="";

    switch (index)
    {
    case 0:
        str=ui->chio_input->toPlainText();
        runStatus=chio_interpreter(str,message,result);
        ui->chio_input->setText(str);
        break;

    case 1:
        str=ui->gauss_input->toPlainText();
        runStatus=gauss_interpreter(str,message,result);
        ui->gauss_input->setText(str);
        break;

    case 2:
        str=ui->lr_input->toPlainText();
        runStatus=lr_factorization_interpreter(str,message,result);
        ui->lr_input->setText(str);
        break;

    case 3:
        str=ui->jacobi_iterative_matrix_input->toPlainText();
        str1=ui->jacobi_iterative_initsolution_input->toPlainText();
        str2=ui->jacobi_iterative_precision_input->toPlainText();
        str3=ui->jacobi_iteration_input->toPlainText();
        runStatus=jacobi_iterative_method(str,str1,str2,str3,message,result);
        ui->jacobi_iterative_matrix_input->setText(str);
        ui->jacobi_iterative_initsolution_input->setText(str1);
        ui->jacobi_iterative_precision_input->setText(str2);
        ui->jacobi_iteration_input->setText(str3);
        break;

    case 4:
        str=ui->seidel_gauss_iterative_matrix_input->toPlainText();
        str1=ui->seidel_gauss_iterative_initsolution_input->toPlainText();
        str2=ui->seidel_gauss_iterative_precision_input->toPlainText();
        str3=ui->seidel_gauss_iteration_input->toPlainText();
        runStatus=seidel_gauss_iterative_method(str,str1,str2,str3,message,result);
        ui->seidel_gauss_iterative_matrix_input->setText(str);
        ui->seidel_gauss_iterative_initsolution_input->setText(str1);
        ui->seidel_gauss_iterative_precision_input->setText(str2);
        ui->seidel_gauss_iteration_input->setText(str3);
        break;

    case 5:
        str=ui->krylov_matrix_input->toPlainText();
        str1=ui->krylov_vector_input->toPlainText();
        runStatus=krylov_interpreter(str,str1,message,result);
        ui->krylov_matrix_input->setText(str);
        ui->krylov_vector_input->setText(str1);
        break;

    case 6:
        str=ui->fadeev_input->toPlainText();
        runStatus=fadeev_interpreter(str,message,result);
        ui->fadeev_input->setText(str);
        break;

    case 7:
        str=ui->lagrange_points_input->toPlainText();
        str1=ui->lagrange_known_x_input->toPlainText();
        runStatus=lagrange_interpolation_interpreter(str,str1,message,result);
        ui->lagrange_points_input->setText(str);
        ui->lagrange_known_x_input->setText(str1);
        break;

    case 8:
        str=ui->newton_points_input->toPlainText();
        str1=ui->newton_known_x_input->toPlainText();
        runStatus=newton_interpolation_interpreter(str,str1,message,result);
        ui->newton_points_input->setText(str);
        ui->newton_known_x_input->setText(str1);
        break;

    case 9:
        str=ui->spline_points_input->toPlainText();
        str1=ui->spline_known_x_input->toPlainText();
        runStatus=spline_interpolation_interpreter(str,str1,message,result);
        ui->spline_points_input->setText(str);
        ui->spline_known_x_input->setText(str1);
        break;

    case 10:
        str=ui->mas_fct_input->toPlainText();
        str1=ui->mas_initial_x->toPlainText();
        str2=ui->mas_iteration->toPlainText();
        str3= ui->mas_precision->toPlainText();
        runStatus=mas_method_interpreter(str,str3,str1,str2,message,result);
        ui->mas_fct_input->setText(str);
        ui->mas_initial_x->setText(str1);
        ui->mas_iteration->setText(str2);
        ui->mas_precision->setText(str3);
        break;

    case 11:
        str=ui->newton_approx_fct_input->toPlainText();
        str1=ui->newton_approx_initial_x->toPlainText();
        str2=ui->newton_approx_iteration->toPlainText();
        str3= ui->newton_approx_precision->toPlainText();
        runStatus=newton_approximation_interpreter(str,str3,str1,str2,message,result);
        ui->newton_approx_fct_input->setText(str);
        ui->newton_approx_initial_x->setText(str1);
        ui->newton_approx_iteration->setText(str2);
        ui->newton_approx_precision->setText(str3);
        break;

    case 12:
        str=ui->function_input->text();
        str1=ui->up_limit->text();
        str2=ui->down_limit->text();
        str3=ui->error_box->text();
        runStatus=integral_trapezoidal_rule_interpreter(str,str3,str2,str1,message,result);
        ui->function_input->setText(str);
        ui->up_limit->setText(str1);
        ui->down_limit->setText(str2);
        ui->error_box->setText(str3);
        break;

    case 13:
        str=ui->function_input_2->text();
        str1=ui->up_limit_2->text();
        str2=ui->down_limit_2->text();
        str3=ui->error_box_2->text();
        runStatus=simpson_rule_interpreter(str,str3,str2,str1,message,result);
        ui->function_input_2->setText(str);
        ui->up_limit_2->setText(str1);
        ui->down_limit_2->setText(str2);
        ui->error_box_2->setText(str3);
        break;

    case 14:
        str=ui->dbl_int_fct_input->toPlainText();
        str1=ui->dbl_int_triangle_input->toPlainText();
        runStatus=double_integration_interpreter(str,str1,message,result);
        ui->dbl_int_fct_input->setText(str);
        ui->dbl_int_triangle_input->setText(str1);
        break;

    case 15:
        str=ui->euler_points_input->toPlainText();
        str1=ui->euler_it_input->toPlainText();
        str2=ui->euler_initvalue_input->toPlainText();
        str3=ui->euler_fct_input->toPlainText();
        str4=ui->euler_eps_input->toPlainText();
        runStatus=euler_cauchy_interpreter(str,str1,str2,str3,str4,message,result);
        ui->euler_eps_input->setText(str4);
        ui->euler_fct_input->setText(str3);
        ui->euler_initvalue_input->setText(str2);
        ui->euler_it_input->setText(str1);
        ui->euler_points_input->setText(str);
        break;

    case 16:
        str=ui->runge_kutta_points_input->toPlainText();
        str1=ui->runge_kutta_it_input->toPlainText();
        str2=ui->runge_kutta_initvalue_input->toPlainText();
        str3=ui->runge_kutta_fct_input->toPlainText();
        str4=ui->runge_kutta_eps_input->toPlainText();
        runStatus=runge_kutta_interpreter(str,str1,str2,str3,str4,message,result);
        ui->runge_kutta_eps_input->setText(str4);
        ui->runge_kutta_fct_input->setText(str3);
        ui->runge_kutta_initvalue_input->setText(str2);
        ui->runge_kutta_it_input->setText(str1);
        ui->runge_kutta_points_input->setText(str);
        break;

    default :
        break;
    }

    if(runStatus==EXTRACTION_SUCCESSUFUL)
    {
        printStatus(ui->statusWindow,message,KELLY_GREEN);
        printOutput(ui->outputWindow,result,DARK_BLUE);
    }
    else
    {
        printStatus(ui->statusWindow,message,DARK_RED);
    }

}

void MainWindow::on_metodaLR_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(4);
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(5);
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(6);
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(7);
}

void MainWindow::on_interpolareNewton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(8);
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(9);
}


void MainWindow::on_mas_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(10);
}

void MainWindow::on_newtown_aproximation_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(11);
}

void MainWindow::on_integrale_metoda_trapezului_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(12);
}

void MainWindow::on_home_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_exit_clicked()
{
    close();
}

void MainWindow::on_help_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_3->setCurrentIndex(17);
}

void MainWindow::on_settings_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_home_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_back_button_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_exitButton2_clicked()
{
    close();
}

void MainWindow::on_settings_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_home_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_back_button_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_exit_2_clicked()
{
    close();
}


void MainWindow::on_help_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_3->setCurrentIndex(17);
}

void MainWindow::on_help_2_clicked()
{
    int currentIndex=17;
    currentIndex=ui->stackedWidget_2->currentIndex();
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_3->setCurrentIndex(currentIndex);
}

void MainWindow::on_settings2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_from_file_button_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        int index=-1;
        index=ui->stackedWidget_2->currentIndex();
        switch (index) {
        case 0:
            ui->chio_input->setText(in.readAll());
            break;

        case 1:
            ui->gauss_input->setText(in.readAll());
            break;

        case 2:
            ui->lr_input->setText(in.readAll());
            break;

        case 3:
            ui->jacobi_iterative_matrix_input->setText(in.readAll());
            break;

        case 4:
            ui->seidel_gauss_iterative_matrix_input->setText(in.readAll());
            break;

        case 5:
            ui->krylov_matrix_input->setText(in.readAll());
            break;

        case 6:
            ui->fadeev_input->setText(in.readAll());
            break;

        case 7:
            ui->lagrange_points_input->setText(in.readAll());
            break;

        case 8:
            ui->newton_points_input->setText(in.readAll());
            break;

        case 9:
            ui->spline_points_input->setText(in.readAll());
            break;

        default:
            QString message="Aceasta fereastra nu accepta incarcarea din fisier!";
            message+=HTML_ENTER;
            message+="Incarcarea din fisier este destinata doar ferestrelor care necesita matrice!";
            printStatus(ui->statusWindow,message,DARK_RED);
            break;

        }
        file.close();
    }

}

void MainWindow::on_clear_status_window_clicked()
{
    ui->statusWindow->clear();
}

void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(14);
}

void MainWindow::on_pushButton_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(15);
}

void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(16);
}

void MainWindow::on_simpson_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(13);
}

void MainWindow::on_back_button_4_clicked()
{
    int currentIndex=0;
    currentIndex=ui->stackedWidget_3->currentIndex();
    currentIndex--;
    if(currentIndex<0)
        currentIndex=17;
    ui->stackedWidget_3->setCurrentIndex(currentIndex);
}

void MainWindow::on_back_button_5_clicked()
{int currentIndex=0;
    currentIndex=ui->stackedWidget_3->currentIndex();
    currentIndex++;
    currentIndex=currentIndex%18;
    ui->stackedWidget_3->setCurrentIndex(currentIndex);

}
