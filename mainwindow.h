#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include<QDialog>
#include<QTextEdit>
#include<QPushButton>
#include<QVBoxLayout>
#include "command.h"
#include "character.h"
#include "Parser.h"
#include "room.h"
#include "item.h"
#include "flashlight.h"
#include "door.h"

#include "key.h"
//#include "ZorkUL.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class QGridLayout;
class QMessageBox;
class QListWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void northButton();
private:
    QPushButton *north;



private slots:
    void southButton();
    void eastButton();
    void westButton();
    void mapButton();
    void Take();
    void Put();
    void Use();
    void invent();
    void roomdetails();
private:
    QPushButton *south;
    QPushButton *east;
    QPushButton *west;
    QPushButton *map;
    Room *currentRoom;
    void goNorth();
    void goSouth();
//    void createRooms();
    Parser parser;
    //Room *currentRoom;
    Room *monsterRoom;
    Room *currentRoomMonsterCheck;

    Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *w, *y, *z;
    Character *player;
    Character *monster;
    bool finished;
//	void createRooms();
    void createRoomsMonster();
    void printWelcome();
    bool processCommand(Command command);
    void printHelp();
    void goRoom(Command command);
    void goRoomMonster();
    void createItems();
    void displayItems();
    void Monster();
    void checkMonster();
    void updateImage();
    void movePlayer(string direction);
//    void Take();
    QGridLayout *vlay;
    QWidget * widget;
    QLabel *myimage;
    QDockWidget *dockMap, *dockInvent,*dockRoom;
    bool *firstTime;
    void restart();


private:
    void createStatusBar();
    void createMapDock();
     void createMapDock2();

    QTextEdit *textEdit;
    QListWidget *customerList;
    QListWidget *paragraphsList;

    QMenu *viewMenu;



public:
    MainWindow();
    void createRooms();
    //void startZork();
//    ZorkUL();
//    ZorkUL2();
    //void play();
    string go(string direction);
    //void goNorth();
    //void goSouth();
    //void startZork();
    //void createRooms();






protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

private slots:

    void quit();
//    void save();
//    void print();
//    void undo();
//    void redo();
//    void cut();
//    void copy();
//    void paste();
//    void bold();
//    void italic();
//    void leftAlign();
//    void rightAlign();
//    void justify();
//    void center();
//    void setLineSpacing();
//    void setParagraphSpacing();
    void about();


private:
    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
    QActionGroup *alignmentGroup;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *boldAct;
    QAction *italicAct;
    QAction *leftAlignAct;
    QAction *rightAlignAct;
    QAction *justifyAct;
    QAction *centerAct;
    QAction *setLineSpacingAct;
    QAction *setParagraphSpacingAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QLabel *infoLabel;

};


#endif
