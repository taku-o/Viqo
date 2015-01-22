#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QtNetwork>
#include <QList>
#include <QVariant>
#include <QIODevice>
#include <QFileDialog>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDesktopServices>
#include <QClipboard>

#include "cookieread.h"
#include "usermanager.h"
#include "livedata.h"
#include "strabstractor.h"
#include "NicoLiveManager/nicolivemanager.h"
#include "settingswindow.h"
#include "settings.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void onReceiveStarted();
	void onReceiveEnded();

  void insComment(int num, bool prem, QString user, QString comm, QString date, bool is_184, bool broadcaster, bool after_open);
  int lastCommentNum();
  void insLog(QString log = "");

	void setWatchCount(QString num);
	void setHousouID(QString text);
	void refleshLiveWaku();

	UserManager* userManager;

  void getSessionFromCookie(QString cookie_name);

  SettingsWindow* settingsWindow;


  NicoLiveManager* nicolivemanager;

  void bodyClear();

  void submittedComment();

public slots:
	// ui slots
	void on_receive_clicked();
	void on_disconnect_clicked();

	void getWatchCount();

private slots:
  void on_comment_view_itemDoubleClicked(QTreeWidgetItem *item, int column);
  void on_comment_view_currentItemChanged(QTreeWidgetItem *current);
	void on_live_waku_list_activated(int index);
	void updateElapsedTime();

  void on_setting_triggered();
  void on_clear_triggered();
  void on_submit_button_clicked();
  void on_submit_text_returnPressed();
  void dropEvent(QDropEvent* event);
  void dragEnterEvent(QDragEnterEvent* event);
  void on_openBrowser_clicked();
  void on_comment_view_customContextMenuRequested(const QPoint &pos);
  void on_one_comment_view_customContextMenuRequested(const QPoint &pos);
  void on_oneCommentActionSearchByGoogle_triggered();
  void on_oneCommentActionCopy_triggered();

  void on_command_test_button_clicked();


  void on_developtest_clicked();

  void on_save_1_triggered();
  void on_save_2_triggered();
  void on_save_3_triggered();
  void on_save_4_triggered();
  void on_load_1_triggered();
  void on_load_2_triggered();
  void on_load_3_triggered();
  void on_load_4_triggered();


private:
	Ui::MainWindow* ui;

	QTimer* watch_count_timer;
	QTimer* elapsed_time_timer;

public:
  Settings settings;

};

#endif // MAINWINDOW_H
