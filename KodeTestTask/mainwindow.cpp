#include "mainwindow.h"
#include "ui_mainwindow.h"


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

void MainWindow::ReadFile(QString FilePath)
{
    QFile file(FilePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            qDebug() << "can't open account list";
     else
    {
        while (!file.atEnd())
        {
                QByteArray line = file.readLine();
                objects.append(Object(line));
        }
    }
}



void MainWindow::GroupByDistance(QVector<Object> obj, QString filepath)
{
    QFile file(filepath);
    file.open(QIODevice::WriteOnly);

    file.write("---------------Вывод групп по растоянию---------------\n");
    int k = 100;
    for (int j = 0; j < 3; j++)
    {
        bool flag = true;
        for (int i = 0; i < obj.size(); i++)
        {
            if(LessDist(obj[i], k))
            {
               if(flag)
               {
                   flag = false;
                   file.write("\n<" + QString::number(k).toUtf8() +":\n");
               }
               file.write(obj[i].ObjectToString().toUtf8()+ '\n');
            }
        }
        k*=10;
    }

    bool flag = true;
    for (int i = 0; i < obj.size(); i++)
    {
        if(!LessDist(obj[i], 10000))
        {
            if(flag)
            {
                flag = false;
                file.write("\nДалеко:\n");
            }
           file.write(obj[i].ObjectToString().toUtf8() + '\n');
        }
    }

    file.close();
}

void MainWindow::GroupByName(QVector<Object> obj, QString filepath)
{
    QFile file(filepath);
    file.open(QIODevice::Append);

    qSort(obj.begin(), obj.end(), [](Object& a, Object& b) { return (a.getName()[0].toLower() < b.getName()[0].toLower()); } );

    file.write("\n---------------Группы по первой букве---------------\n");
    QString chapter = " ";

    for (int i = 0; i < obj.size(); i++)
    {
        if(chapter[0].toUpper() != obj[i].getName()[0].toUpper())
        {
            chapter = obj[i].getName()[0].toUpper();
            file.write("\nГруппа на букву " + chapter.toUtf8() + ": \n");
        }

        file.write(obj[i].ObjectToString().toUtf8() + '\n');
    }
    file.close();

}

void MainWindow::GroupByDate(QVector<Object> obj, QString filepath)
{
    QFile file(filepath);
    file.open(QIODevice::Append);
    file.write("\n---------------Группы по дате---------------\n");
    QDateTime dateTime = QDateTime::currentDateTime();
    bool flag = true;

    for (int i = 0; i < obj.size(); i++)
    {  
        if(obj[i].getTime().date() == dateTime.date())
        {
            if(flag)
            {
                file.write("\nСегодня:\n");
                flag = false;
            }
            file.write(obj[i].ObjectToString().toUtf8() + '\n');
        }
    }

    flag = true;
    for (int i = 0; i < obj.size(); i++)
    {
        if(obj[i].getTime().date() == dateTime.date().addDays(-1))
        {
            if(flag)
            {
                file.write("\nВчера:\n");
                flag = false;
            }
            file.write(obj[i].ObjectToString().toUtf8() + '\n');
        }
    }

    flag = true;
    for (int i = 0; i < obj.size(); i++)
    {
        if(obj[i].getTime().date() >= dateTime.date().addDays(-7) && obj[i].getTime().date() <= dateTime.date())
        {
            if(flag)
            {
                file.write("\nНа этой неделе:\n");
                flag = false;
            }
            file.write(obj[i].ObjectToString().toUtf8() + '\n');
        }
    }

    flag = true;
    for (int i = 0; i < obj.size(); i++)
    {
        if(obj[i].getTime().date().month() == dateTime.date().month())
        {
            if(flag)
            {
                file.write("\nВ этом месяце:\n");
                flag = false;
            }
            file.write(obj[i].ObjectToString().toUtf8() + '\n');
        }
    }

    flag = true;
    for (int i = 0; i < obj.size(); i++)
    {
        if(obj[i].getTime().date().year() == dateTime.date().year())
        {
            if(flag)
            {
                file.write("\nВ этом году:\n");
                flag = false;
            }
            file.write(obj[i].ObjectToString().toUtf8() + '\n');
        }
    }

    flag = true;
    for (int i = 0; i < obj.size(); i++)
    {
        if(obj[i].getTime().date().year() < dateTime.date().year())
        {
            if(flag)
            {
                file.write("\nРанее:\n");
                flag = false;
            }
            file.write(obj[i].ObjectToString().toUtf8() + '\n');
        }
    }



    file.close();
}

void MainWindow::GroupByType(QVector<Object> obj, QString filepath)
{
    QFile file(filepath);
    file.open(QIODevice::Append);
    file.write("\n---------------Группы по типу---------------\n");
    qSort(obj.begin(), obj.end(), [](Object& a, Object& b) { return (a.getType().toLower() < b.getType().toLower()); } );
    QVector <Object> other = {};
    QVector <Object> current = {};
    int n = ui->spinBox->value();

    QString name = "";
    current.append(obj[0]);
    for(int i = 1; i < obj.size(); i++)
    {
        if(obj[i].getType() == current[0].getType())
            current.append(obj[i]);
        else
        {
            if(current.size() >= n)
            {
                file.write("\nТип " + current[0].getType().toUtf8() + ":\n");

                for(int j = 0; j < current.size(); j++)
                {
                    file.write(current[j].ObjectToString().toUtf8() + '\n');
                }
            }
            else
            {
                for(int j = 0; j < current.size(); j++)
                {
                    other.append(current[j]);
                }
            }

            current.clear();
            current.append(obj[i]);
        }
    }
    if(current.size() > 0)
    {
        if(current.size() >= n)
        {
            file.write("\nТип " + current[0].getType().toUtf8() + ":\n");
            for(int i = 0; i < current.size(); i++)
            {
                file.write(current[i].ObjectToString().toUtf8() + '\n');
            }
        }
        else
        {
            for(int j = 0; j < current.size(); j++)
            {
                other.append(current[j]);
            }
        }
    }
    if(other.size() != 0)
        file.write("\nДругие типы:\n");
    for(int i = 0; i < other.size(); i++)
    {
        file.write(other[i].ObjectToString().toUtf8() + '\n');
    }

    file.close();
}

bool MainWindow::LessDist(Object o, int n)
{
    if(sqrt(o.getX()*o.getX()+o.getY()*o.getY()) < n)
        return true;
    else
        return false;
}


void MainWindow::on_OpenFileButton_clicked()
{
    ReadFile(QFileDialog::getOpenFileName(this, "Выбрать файл"));

    for(int i= 0; i < objects.size(); i++)//выводим вектор в UI
    {
        ui->Text_ShowFile->append(objects[i].ObjectToString());
    }
}

void MainWindow::on_Button_add_object_clicked()
{
    QString name = ui->Text_Name->toPlainText().trimmed();
    QString x = ui->Text_X->toPlainText().trimmed();
    QString y = ui->Text_Y->toPlainText().trimmed();
    QString type = ui->Text_Type->toPlainText().trimmed();
    QDateTime time = ui->DateEdit->dateTime();
    objects.append(Object(name,x.toDouble(),y.toDouble(),type,time));
    ui->Text_ShowFile->append(objects[objects.size()-1].ObjectToString());//выводим в UI
}

void MainWindow::on_Create_Groups_File_clicked()
{
    QString mfile = "MyFile.txt";

    GroupByDistance(objects, mfile);//запись груп по раст
    GroupByName(objects, mfile);//дозапись груп по имени
    GroupByDate(objects, mfile);//дозапись груп по дате
    GroupByType(objects, mfile);//дозапись груп по типу

    QDesktopServices::openUrl(QUrl(mfile, QUrl::TolerantMode));

}


