#include "pform.h"
#include "ui_pform.h"
#include <QDebug>
#include<QSizePolicy>
#include<QHeaderView>
pForm::pForm(Mysql_Establish *establish, privilege *test, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pForm),
    tk(test)
{
    ui->setupUi(this);
    en=establish;
    database=en->data();
//Model
    model= new QSqlTableModel(this,database);
    model->setTable("person");
    model->select();
    model->removeColumn(4);
    model->removeColumn(3);
    model->removeColumn(2);

    // specifics privileges:
        if(test->e_hum()==true){

            page1 = new QWidget;
            page2 = new QWidget;

            center = new QGridLayout;
            tabbar = new QTabWidget(this);
           {
                //checkBox:
                student = new QCheckBox(page1);
                professor = new QCheckBox(page1);
                admin = new QCheckBox(page1);
            //Widget
                name = new QLineEdit(page1);
                phone = new QLineEdit(page1);
                email = new QLineEdit(page1);
                birth = new QLineEdit(page1);

                in = new QLabel("name",page1);
                ip = new QLabel("Phone",page1);
                ie = new QLabel("Email",page1);
                ib = new QLabel("Birth",page1);

               // name->setReadOnly(true);


            //View
                mapper = new QDataWidgetMapper;
                mapper->setModel(model);
                stu = new QTableView(page1);
                stu->setModel(model);


                //To highlight the entire row, insteads of a signal cell;
                stu->setSelectionBehavior(QAbstractItemView::SelectRows);
                stu->setSelectionMode(QAbstractItemView::SingleSelection);


            //Layout
                glayout = new QGridLayout;
                vlayout = new QVBoxLayout;
                hlayout = new QHBoxLayout;
                vlayoutc = new QVBoxLayout;

                vlayoutc->addWidget(professor);
                vlayoutc->addWidget(student);
                vlayoutc->addWidget(admin);


                glayout->addWidget(in,1,1);
                glayout->addWidget(ib,1,3);
                glayout->addWidget(name,1,2);
                glayout->addWidget(birth,1,4);

                glayout->addWidget(ie,2,1);
                glayout->addWidget(ip,2,3);
                glayout->addWidget(email,2,2);
                glayout->addWidget(phone,2,4);

                hlayout->addLayout(glayout);
                hlayout->addLayout(vlayoutc);

                vlayout->addWidget(stu);
                vlayout->addLayout(hlayout);

                page1->setLayout(vlayout);
                //   tab = new QTabWidget(page1);


                mapper->addMapping(name,0);
                mapper->addMapping(birth,1);
                mapper->addMapping(email,2);
                mapper->addMapping(phone,3);
                mapper->toFirst();
            }
            tabbar->addTab(page1,"View");
            center->addWidget(tabbar);
            this->setLayout(center);
        }
else{
//checkBox:
    student = new QCheckBox(this);
    professor = new QCheckBox(this);
    admin = new QCheckBox(this);
//Widget
    name = new QLineEdit(this);
    phone = new QLineEdit(this);
    email = new QLineEdit(this);
    birth = new QLineEdit(this);

    in = new QLabel("name",this);
    ip = new QLabel("Phone",this);
    ie = new QLabel("Email",this);
    ib = new QLabel("Birth",this);

    name->setReadOnly(true);
    phone->setReadOnly(true);
    email->setReadOnly(true);
    birth->setReadOnly(true);



//View
    mapper = new QDataWidgetMapper;
    mapper->setModel(model);
    stu = new QTableView(this);
    stu->setModel(model);


    //To highlight the entire row, insteads of a signal cell;
    stu->setSelectionBehavior(QAbstractItemView::SelectRows);
    stu->setSelectionMode(QAbstractItemView::SingleSelection);

    // set readonly
    stu->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //size
//    stu->resizeColumnsToContents();
//    stu->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    stu->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    stu->horizontalHeader()->setStretchLastSection(true);



//Layout
    glayout = new QGridLayout;
    vlayout = new QVBoxLayout;
    hlayout = new QHBoxLayout;
    vlayoutc = new QVBoxLayout;

    vlayoutc->addWidget(professor);
    vlayoutc->addWidget(student);
    vlayoutc->addWidget(admin);


    glayout->addWidget(in,1,1);
    glayout->addWidget(ib,1,3);
    glayout->addWidget(name,1,2);
    glayout->addWidget(birth,1,4);

    glayout->addWidget(ie,2,1);
    glayout->addWidget(ip,2,3);
    glayout->addWidget(email,2,2);
    glayout->addWidget(phone,2,4);

    hlayout->addLayout(glayout);
    hlayout->addLayout(vlayoutc);

    vlayout->addWidget(stu);
    vlayout->addLayout(hlayout);

    this->setLayout(vlayout);
    //   tab = new QTabWidget(this);


    mapper->addMapping(name,0);
    mapper->addMapping(birth,1);
    mapper->addMapping(email,2);
    mapper->addMapping(phone,3);

    mapper->toFirst();
}
        //Clicked Slot:
            connect(stu,SIGNAL(clicked(QModelIndex )),mapper,SLOT(setCurrentModelIndex(QModelIndex )));
        //    connect(stu,SIGNAL(clicked(QModelIndex )),stu,SLOT())
            connect(stu,SIGNAL(clicked(QModelIndex )),this,SLOT(table_highlight(QModelIndex)));

}

pForm::~pForm()
{
    delete ui;
}
void pForm::table_highlight(QModelIndex lm){
    qDebug()<<lm.column();
}


