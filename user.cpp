#include <QDir>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>

#include "user.h"
#include "constants.h"


User::User(const QString &psurName, const QString &pname, const QString &psecondName, const QDate &pdate, QObject *parent):
    QObject(parent)
  , results(new MotivationReliefQuizResult)
  , surName(psurName)
  , name(pname)
  , secondName(psecondName)
  , birthDate(pdate)
{

}

void User::setInfo(const QString &surName, const QString &name, const QString &secondName, const QDate &date)
{
    this -> surName = surName;
    this -> name = name;
    this -> secondName = secondName;
    this -> birthDate = date;
}

QString User::getSurname() const
{
    return surName;
}

QString User::getName() const
{
    return name;
}

QString User::getSecondName() const
{
    return secondName;
}


void User::saveToFile()
{
    QDir dir;

    if(!dir.exists(FOLDER_NAME)){
        dir.mkpath(FOLDER_NAME);
    }
    dir.cd(FOLDER_NAME);

    //int count = 1;
    QString fileName = dir.path() + "/" + this->surName + " " + this->name + " " + this->secondName + ".txt";
    //qDebug() << fileName <<"\n";
    int count = 1;
    while(QFile::exists(fileName + QString::number(count))){
        fileName = fileName + QString::number(count++);
    }

    QFile newFile(fileName);
    if(!newFile.open(QIODevice::WriteOnly | QIODevice::Text)){
    //    qDebug() << "file not opened\n";
        return ;
    }

    QTextStream textStream(&newFile);

    for(size_t quizIndex = 0; quizIndex<this->results->resultsValue.size(); quizIndex++){
        for(size_t i = 0;i < QUIZ_VALUES_NAMES[quizIndex].size(); i++) {
            textStream << this->results->resultsValue[quizIndex][QUIZ_VALUES_NAMES[quizIndex][i]] << SEPARATOR_SYMBOL;
      //      qDebug() << this->results->resultsValue[quizIndex][QUIZ_VALUES_NAMES[quizIndex][i]] << SEPARATOR_SYMBOL;
        }
        textStream << "\n";
    }

    for(size_t quizIndex = 0; quizIndex<this->results->resultsAccess.size(); quizIndex++){
        for(size_t i = 0;i < QUIZ_VALUES_NAMES[quizIndex].size(); i++) {
            textStream << this->results->resultsAccess[quizIndex][QUIZ_VALUES_NAMES[quizIndex][i]] << SEPARATOR_SYMBOL;
      //      qDebug() << this->results->resultsAccess[quizIndex][QUIZ_VALUES_NAMES[quizIndex][i]] << SEPARATOR_SYMBOL;
        }
        textStream << "\n";
    }

    results->resultsValue.clear();
    results->resultsValue.resize(QUIZ_VALUES_NAMES.size());

    results->resultsAccess.clear();
    results->resultsAccess.resize(QUIZ_VALUES_NAMES.size());
}
