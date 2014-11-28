#include "wakutcp.h"
#include "../../mainwindow.h"
#include "../nicolivemanager.h"

WakuTcp::WakuTcp(QString domain, int port, QString thread, MainWindow* mwin, NicoLiveManager* nicolivemanager)
{
  this->domain = domain;
  this->port = port;
  this->thread = thread;
  this->mwin = mwin;
  this->nicolivemanager = nicolivemanager;

  socket = new QTcpSocket(this);

  connect(socket, SIGNAL(connected()),this, SLOT(connected()));
  connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
  connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
}

void WakuTcp::doConnect()
{
  mwin->insLog("WakuTcp::doConnect");
  socket->connectToHost(domain, port);

  if(!socket->waitForConnected(5000)) {
    mwin->insLog("Error: " + socket->errorString() + "\n");
    QTimer::singleShot(30000, this, SLOT(doConnect()));
  }

  mwin->insLog();
}

void WakuTcp::connected()
{
  mwin->insLog("WakuTcp::connected");
  QByteArray send;
  opentime = QDateTime::currentDateTime();

  send.append("<thread thread=\""+thread+"\" res_from=\"-1\" version=\"20061206\" />");
  send.append('\0');

  if (socket->write(send) == -1) {
    mwin->insLog("Error: " + socket->errorString() + "\n");
    socket->close();
    QTimer::singleShot(30000, this, SLOT(doConnect()));
    return;
  }

  connect(&checkConnectionTimer,SIGNAL(timeout()),this,SLOT(checkConnection()));
  checkConnectionTimer.setInterval(30000);
  checkConnectionTimer.start();

  connectionTime.start();
  mwin->insLog();
}

void WakuTcp::disconnected()
{
}

void WakuTcp::readyRead()
{
  QList<QByteArray> rawwakus( socket->readAll().split('\0') );
  rawwakus[0].insert(0, lastRawWaku);

  for ( int i = 0; i < rawwakus.size()-1; ++i) {
    readOneRawWaku(rawwakus[i]);
  }

  lastRawWaku = rawwakus.takeLast();
}

void WakuTcp::readOneRawWaku(QByteArray& rawwaku)
{
  connectionTime.restart();
  if (rawwaku.startsWith("<thread")) {
    return;
  }

  StrAbstractor awaku(rawwaku);
  QString wakuS = awaku.midStr(">", "</chat>");

  QStringList wakur = wakuS.split(",");
  const QString& broadID = wakur.at(0);
  const QString& CommunityID = wakur.at(1);
  //	const QString& nushiID = wakur.at(2);

  //	qDebug() << CommunityID << "," << broadID;

  if(wakur.size() != 3) {
    return;
  }


  if (mwin->isNextWaku()) {
    if ( nicolivemanager->nowWaku.getCommunity() == CommunityID &&
         nicolivemanager->nowWaku.getBroadID() != broadID){

      if (mwin->isCommandNextWakuChecked()) {
        QProcess pr;
        QString cmd = mwin->getCommandNextWaku();

        cmd.replace("%wakuURL%","\"http://live.nicovideo.jp/watch/lv" + broadID + '"');

        pr.start(cmd);
        pr.waitForFinished(30000);
      }

      mwin->setHousouID(broadID);
      mwin->on_receive_clicked();
    }
  }

  foreach (QString commu, nicolivemanager->mycommunities) {
    if (commu == wakur.at(1)) {
      nicolivemanager->insertLiveWakuList(new LiveWaku(mwin, nicolivemanager, broadID));
      mwin->refleshLiveWaku();
    }
  }

}

void WakuTcp::close()
{
  socket->close();
}

bool WakuTcp::isConnected()
{
  return socket->state() != QAbstractSocket::UnconnectedState;
}

void WakuTcp::checkConnection()
{
  if (connectionTime.elapsed() > 61000) {
    mwin->insLog("alert is disconnected\n");
    socket->close();
    nicolivemanager->getRawMyLiveHTML();
    QTimer::singleShot(30000, nicolivemanager, SLOT(getRawMyLiveHTML()));
    doConnect();
  }
}
