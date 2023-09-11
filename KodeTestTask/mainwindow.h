#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDate>
#include <QDebug>
#include <QVector>
#include "object.h"
#include <qmath.h>
#include <QDesktopServices>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void ReadFile(QString file);
    void GroupByDistance(QVector <Object> obj, QString filepath);
    void GroupByName(QVector <Object> obj, QString filepath);
    void GroupByDate(QVector <Object> obj, QString filepath);
    void GroupByType(QVector <Object> obj, QString filepath);
    bool LessDist (Object o, int n);

private slots:
    void on_OpenFileButton_clicked();

    void on_Button_add_object_clicked();

    void on_Create_Groups_File_clicked();

    void on_Button_WriteFile_clicked();

private:
    Ui::MainWindow *ui;
    QVector <Object> objects;

};
#endif // MAINWINDOW_H
