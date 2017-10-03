#include <QtWidgets>
#include <QGridLayout>
#include<QPushButton>
#include <QDebug>
#include <ctime>
#include <chrono>
#include <thread>
#include <QMediaPlayer>

//#include "ZorkUL.h"
#include "item.h"
#include "character.h"
#include "mainwindow.h"
//#include "ZorkUL.h"

using namespace std;


int main(int argc, char  *argv[]) {

    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}

void MainWindow::Take(){

    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Item to pick up: "), QLineEdit::Normal,
                                         tr("purplekey"), &ok);

    string item_to_take = text.toStdString();

    if (ok && !text.isEmpty()){
        int location = currentRoom->isItemInRoom(item_to_take);
        Item *itemToAdd;

        QMessageBox msgBox;
        // Location is the number of the item in the items array
        if (location  < 0 ){
            cout << "item is not in room" << endl;
            msgBox.setText(tr("Item Not In Room"));
            msgBox.exec();
        }
        else if (player->numberOfItems() < 3){
            itemToAdd = currentRoom->getItemAtLocation(location);
            player->addItem(*itemToAdd);
            currentRoom->removeItem(location); //Might call this removeItemAtLocation to suit the naming of similar methods

            // Make method to remove the item from the room
            // Get the item then remove it
            // Pass location to get the item from the room.
            cout << "item is in room" << endl;
            cout << "item taken" << endl;
            cout << endl;
            cout << currentRoom->longDescription() << endl;

            msgBox.setText(tr("Item taken"));
            msgBox.exec();
            invent();
        }
        else{
            msgBox.setText(tr("Inventory Full"));
            msgBox.exec();
        }
    }
}


void MainWindow::Put(){

    bool ok;
    QString text2 = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                          tr("Item to drop: "), QLineEdit::Normal,
                                          tr("flashlight1"), &ok);
    //      if (ok && !text.isEmpty())
    //          textLabel->setText(text);
    string item_to_put = text2.toStdString();
    Item *itemToAdd;
    QMessageBox msgBox;

    int location1 = player->isItemInCharacter(item_to_put);
    if (location1  < 0 ){
        msgBox.setText(tr("You are not carrying this item"));
        msgBox.exec();
    }
    else {
        // Location is the number of the item in the items array
        itemToAdd = player->getItemAtLocation(location1);
        // Very like getting items out of the room's inventory for get items from the player's
        currentRoom->addItem(*itemToAdd);
        player->removeItem(location1);
        msgBox.setText(tr("Item dropped"));
        msgBox.exec();

        invent();
        cout << "you're adding "  << endl;
    }
}



void MainWindow::northButton()
{


    string direction ="north";
    movePlayer(direction);
    updateImage();
    goRoomMonster();
    checkMonster();


    if(currentRoom->shortDescription() == "outside"){
        QMediaPlayer* playerw;
        playerw = new QMediaPlayer;
        // ...
        playerw->setMedia(QUrl("qrc:/audio/Outside.mp3"));
        playerw->setVolume(50);
        playerw->play();
        cout << endl;
        QMessageBox msgBox;
        msgBox.setText(tr("You made it outside! You have survived!"));
        QAbstractButton* playagain = msgBox.addButton(tr("Play again"), QMessageBox::YesRole);
        QAbstractButton* quitnow = msgBox.addButton(tr("Quit"), QMessageBox::YesRole);


        msgBox.exec();

        if (msgBox.clickedButton()==playagain) {
            qApp->quit();
            QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        }
        if (msgBox.clickedButton()==quitnow) {
            QApplication::quit();
        }

        //             chrono::milliseconds dura( 20000 );
        //             this_thread::sleep_for( dura );
        // Are we using this Paddy?

        cout << "end" << endl;
    }
}


void MainWindow::southButton()
{

    string direction ="south";
    movePlayer(direction);
    updateImage();
    goRoomMonster();
    checkMonster();
}


void MainWindow::mapButton()
{
    bool static placedonce = false;
    QDockWidget *dockMap = new QDockWidget(tr("Map"), this);
    dockMap->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    customerList = new QListWidget(dockMap);
    customerList->addItems(QStringList()
                           << "          [outside]   "
                           << "              |       "
                           << " [p]---[q]   [r]   [s]"
                           << "  |     |     |     | "
                           << "  |     |     |     | "
                           << " [l]---[m]---[n]---[o]"
                           << "        |     |     | "
                           << "        |     |     | "
                           << "       [i]---[j]---[k]"
                           << "              |     | "
                           << "              |     | "
                           << "             [g]---[h]"
                           << "              |       "
                           << "              |       "
                           << "       [c]-[spawn]-[b]"
                           << "        |     |     | "
                           << "        |     |     | "
                           << "       [d]---[e]   [f]" );
    dockMap->setWidget(customerList);
    dockMap->setFont(QFont("courier"));
    if(placedonce)
        removeDockWidget(dockMap);

    addDockWidget(Qt::RightDockWidgetArea, dockMap);
    placedonce = true;
    cout << "docky dooooooooooo" << dockInvent << endl;   // Alright there Scooby Doo
}

void MainWindow::invent()
{
    bool static placedonce = false;
    static QDockWidget *previousInvent;
    if(placedonce)
        removeDockWidget(previousInvent);
    QDockWidget *dockInvent = new QDockWidget(tr("Inventory"), this);
    paragraphsList = new QListWidget(dockInvent);
    string invent(player->listItems());
    paragraphsList->addItems(QStringList()
                             << invent.c_str() );
    dockInvent->setWidget(paragraphsList);
    addDockWidget(Qt::RightDockWidgetArea, dockInvent);
    previousInvent = dockInvent;
    placedonce = true;
}

void MainWindow::roomdetails()
{

    bool ok;
    QString text2 = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                          tr("Flashlight Name: "), QLineEdit::Normal,
                                          tr("flashlight1"), &ok);

    bool static placedonce = false;
    string item_to_put = text2.toStdString();
    Item *itemToUse;
    QMessageBox msgBox;
    QString outputStr;
    int location1 = player->isItemInCharacter(item_to_put);
    if (location1  < 0 ){
        msgBox.setText(tr("You are not carrying this item"));
        msgBox.exec();
    }
    else {
        // Very like getting items out of the room's inventory for get items from the player's
        // Location is the number of the item in the items array
        itemToUse = player->getItemAtLocation(location1);
        if (itemToUse->getUses() < 1){
            string output = itemToUse->getShortDescription() + " has no uses left.";
            outputStr.append(output.c_str());
            msgBox.setText(outputStr);
            msgBox.exec();
        }
        else {
           itemToUse->useLight();

            string arrayNum[4] = {"north","south","east","west"};
            for(int dir =0; dir <4; dir = dir+1){
                currentRoomMonsterCheck = currentRoom;
                string direction = arrayNum[dir];

                Room* nextRoom = currentRoomMonsterCheck->nextRoom(direction);
                if(nextRoom == monsterRoom){
                    cout << "The Monster Lurks near " << nextRoom->shortDescription() << " " << direction << endl;
                    outputStr = "The Monster Lurks near to the ";
                    outputStr.append(direction.c_str());
                    msgBox.setText(outputStr);
                    msgBox.exec();
                    dir =5; // Is this line not a game breaking disaster just waiting to happen?
                }
            }

            static QDockWidget *previousDock;
            if(placedonce)
                removeDockWidget(previousDock);

            QDockWidget *dockRoom = NULL;
                    dockRoom = new QDockWidget(tr("Room"), this);
            paragraphsList = new QListWidget(dockRoom);
            string str(currentRoom->longDescription() );
            string str2( "Flashlight uses left: " + to_string( itemToUse->getUses() ) );
            QStringList longerList = (QStringList() << str.c_str() << str2.c_str() );
            paragraphsList->addItems(longerList);
            dockRoom->setWidget(paragraphsList);
            addDockWidget(Qt::LeftDockWidgetArea, dockRoom);
            previousDock = dockRoom;
            placedonce = true;
        }
    }

}

void MainWindow::Use()
{

    bool ok;
    QString text3 = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                          tr("Key to use: "), QLineEdit::Normal,
                                          tr("purplekey"), &ok);
    // Rather than putting in purplekey, it may have been handier for the user if we checked the inventory
    // an Item with 'key' in Item description and popped the first result in as a guess. =/   Ah well
    string item_to_use = text3.toStdString();

    int location2 = player->isItemInCharacter(item_to_use);
    int code, doorNumber;
    Item *itemToUse;
    Door *doorToUnlock;
    QMessageBox msgBox;
    if (location2 < 0){
        msgBox.setText(tr("You are not carrying this item"));
        msgBox.exec();
    }

    else {
        // We may have to add doors to rooms which will require certain keys or items to unlock.
        // I don't know if the monster should be allowed pass through, but this is a step for later on
        // The door object can have a property or value the is for that
        // Considering the items already have a value we could use that for the comparison. With the name as key.
        // Maybe a have a Key type that inherits from Item

        itemToUse = player->getItemAtLocation(location2);
        code = itemToUse->getCode();
        doorNumber = currentRoom->isDoorInRoom(code);
        if(doorNumber >= 0)
        {
            doorToUnlock = currentRoom->getDoorAtLocation(doorNumber);

            string direction = doorToUnlock->getDirection();
            Room *destRoom = doorToUnlock->getDestinationRoom();

            // direction must be "north", "south", "east" or "west"
            if(direction == "north"){
                currentRoom->setExit("north", destRoom);
                destRoom->setExit("south", currentRoom);
            }
            if(direction == "south"){
                currentRoom->setExit("south", destRoom);
                destRoom->setExit("north", currentRoom);
            }
            if(direction == "east"){
                currentRoom->setExit("east", destRoom);
                destRoom->setExit("west", currentRoom);
            }
            if(direction == "west"){
                currentRoom->setExit("west", destRoom);
                destRoom->setExit("east", currentRoom);
            }
            // This will set the exit for the room to the other and for the other to the current. a -> b and b -> a.
            // Very like getting items out of the room's inventory for get items from the player's
            cout << "Door unlocked" << endl;
            msgBox.setText(tr("Door Unlocked"));
            msgBox.exec();
            player->removeItem(location2);
            currentRoom->removeDoor(doorNumber);
            doorToUnlock->destroyDoor();
            updateImage();
            // Kill the item and the door
            // Sounds rather violent...

            cout << currentRoom->longDescription() << endl;
        }
        else
        {
            msgBox.setText(tr("You are not carrying the right key for the door."));
            msgBox.exec();
        }
    }
}

void MainWindow::eastButton()
{
    string direction ="east";
    movePlayer(direction);
    updateImage();
    goRoomMonster();
    checkMonster();
}
void MainWindow::westButton()
{
    string direction ="west";
    movePlayer(direction);
    updateImage();
    goRoomMonster();
    checkMonster();

}

void MainWindow::movePlayer(string direction){

    Room* nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL)
        cout << "underdefined input"<< endl;
    else {
        currentRoom = nextRoom;
        cout << currentRoom->longDescription() << endl;
    }

}

void MainWindow::goRoomMonster() {
    cout << "go monster room" << endl;
    string arrayNum[4] = {"north","south","east","west"};
    srand(time(NULL));
    int RandIndex = rand() % 4;
    cout << "random room " <<arrayNum[RandIndex] << endl;
    string direction = arrayNum[RandIndex];

    Room* nextRoom = monsterRoom->nextRoom(direction);

    if (nextRoom == NULL)
        cout << "Monster waited"<< endl;
    else {
        monsterRoom = nextRoom;
        cout <<  "Monster Moved" << monsterRoom->shortDescription() << endl;
    }
    //currentRoom2 = nextRoom;


}

void MainWindow::updateImage(){

    string direction_south = "south";
    string direction_north = "north";
    string direction_east = "east";
    string direction_west = "west";
    cout << "update image part here " << currentRoom->longDescription() << endl;



    QWidget * widget = new QWidget(this);


    QGridLayout *vlay = new QGridLayout(widget);

    Room* nextRoom_north = currentRoom->nextRoom(direction_north);
    if (nextRoom_north != NULL){
        QPushButton *north = new QPushButton("North",this);
        vlay->addWidget(north,0,1);
        connect(north, SIGNAL (released()), this, SLOT (northButton()));
    }

    Room* nextRoom_east = currentRoom->nextRoom(direction_east);
    if (nextRoom_east != NULL){
        QPushButton *east = new QPushButton("East",this);
        vlay->addWidget(east,1,2);
        connect(east, SIGNAL (released()), this, SLOT (eastButton()));
    }


    Room* nextRoom_west = currentRoom->nextRoom(direction_west);
    if (nextRoom_west != NULL){
        QPushButton *west = new QPushButton("West");
        vlay->addWidget(west,1,0);
        connect(west, SIGNAL (released()), this, SLOT (westButton()));
    }


    Room* nextRoom_south = currentRoom->nextRoom(direction_south);
    if (nextRoom_south != NULL){
        QPushButton *south = new QPushButton("South");
        vlay->addWidget(south,2,1);
        connect(south, SIGNAL (released()), this, SLOT (southButton()));
    }

    QPushButton *put = new QPushButton("Put / Drop");
    vlay->addWidget(put,3,0);
    QPushButton *take = new QPushButton("Take");
    vlay->addWidget(take,3,1);
    QPushButton *map = new QPushButton("Map");
    vlay->addWidget(map,4,1);
    QPushButton *invent = new QPushButton("Inventory");
    vlay->addWidget(invent,4,0);
    QPushButton *roomdetails = new QPushButton("Shine Flashlight");
    vlay->addWidget(roomdetails,4,2);
    QPushButton *use = new QPushButton("Unlock Door");
    vlay->addWidget(use,3,2);


    widget->setLayout(vlay);
    setCentralWidget(widget);
    widget->setLayout(vlay);
    setCentralWidget(widget);



    connect(take, SIGNAL (released()), this, SLOT (Take()));
    connect(put, SIGNAL (released()), this, SLOT (Put()));
    connect(map, SIGNAL (released()), this, SLOT (mapButton()));
    connect(use, SIGNAL (released()), this, SLOT (Use()));
    connect(invent, SIGNAL (released()), this, SLOT (invent()));
    connect(roomdetails, SIGNAL (released()), this, SLOT (roomdetails()));

}

MainWindow::MainWindow()
{

    createRooms();

    QWidget * widget = new QWidget(this);

    // maybe use q button group, image needs to go to right grid layout may not work
    //splitting window would be handy
    QGridLayout *vlay = new QGridLayout(widget);

    string direction_south = "south";
    string direction_north = "north";
    string direction_east = "east";
    string direction_west = "west";

    Room* nextRoom_north = currentRoom->nextRoom(direction_north);
    if (nextRoom_north != NULL){
        QPushButton *north = new QPushButton("North",this);
        vlay->addWidget(north,0,1);
        connect(north, SIGNAL (released()), this, SLOT (northButton()));
    }

    Room* nextRoom_east = currentRoom->nextRoom(direction_east);
    if (nextRoom_east != NULL){
        QPushButton *east = new QPushButton("East",this);
        vlay->addWidget(east,1,2);
        connect(east, SIGNAL (released()), this, SLOT (eastButton()));
    }

    Room* nextRoom_west = currentRoom->nextRoom(direction_west);
    if (nextRoom_west != NULL){
        QPushButton *west = new QPushButton("West");
        vlay->addWidget(west,1,0);
        connect(west, SIGNAL (released()), this, SLOT (westButton()));
    }

    Room* nextRoom_south = currentRoom->nextRoom(direction_south);
    if (nextRoom_south != NULL){
        QPushButton *south = new QPushButton("South");
        vlay->addWidget(south,2,1);
        connect(south, SIGNAL (released()), this, SLOT (southButton()));
    }

    QPushButton *put = new QPushButton("Put / Drop");
    vlay->addWidget(put,3,0);

    QPushButton *take = new QPushButton("Take");
    vlay->addWidget(take,3,1);

    QPushButton *map = new QPushButton("Map");
    vlay->addWidget(map,4,1);

    QPushButton *invent = new QPushButton("Inventory");
    vlay->addWidget(invent,4,0);

    QPushButton *roomdetails = new QPushButton("Shine Flashlight");
    vlay->addWidget(roomdetails,4,2);

    QPushButton *use = new QPushButton("Unlock Door");
    vlay->addWidget(use,3,2);

    widget->setLayout(vlay);
    setCentralWidget(widget);


    connect(put, SIGNAL (released()), this, SLOT (Put()));
    connect(map, SIGNAL (released()), this, SLOT (mapButton()));
    connect(take, SIGNAL (released()), this, SLOT (Take()));
    connect(use, SIGNAL (released()), this, SLOT (Use()));
    connect(invent, SIGNAL (released()), this, SLOT (invent()));
    connect(roomdetails, SIGNAL (released()), this, SLOT (roomdetails()));


    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    createActions();
    createMenus();

    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);

    setWindowTitle(tr("Outside"));
    setMinimumSize(480, 320);
    resize(480, 320);



}
void MainWindow::createMapDock()
{
    //    this->close();



}

void MainWindow::createMapDock2(){
    cout << "deleting" << endl;


}

void MainWindow::createRooms()  {
    // All Rooms
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m, *n, *o, *p, *q, *r, *s;
    player = new Character("Player");

    // All Items
    Door *Bluedoor, *Purpledoor, *Greendoor, *Orangedoor;
    Key *Bluekey;
    Key *Purplekey;
    Key *Greenkey;
    Key *Orangekey;
    Bluekey = new Key("bluekey", 12);
    Purplekey = new Key("purplekey", 13);
    Greenkey = new Key("greenkey", 14);
    Orangekey = new Key("orangekey", 15);


    Flashlight *fl1, *fl2, *fl3, *fl4;
    fl1 = new Flashlight("flashlight1");  // 6 by default (using default values)
    fl2 = new Flashlight("flashlight2");
    fl3 = new Flashlight("flashlight3", 4);
    fl4 = new Flashlight("flashlight4", 5);

    player->addItem(fl1);

    a = new Room("a");
        a->addItem(Purplekey);
    b = new Room("b");
    c = new Room("c");
    d = new Room("d");
    e = new Room("e");
        e->addItem(fl2);
    f = new Room("f");
        f->addItem(Bluekey);
    g = new Room("g");
    h = new Room("h");
    i = new Room("i");
    j = new Room("j");
    k = new Room("k");
    l = new Room("l");
        l->addItem(Orangekey);
    m = new Room("m");
    n = new Room("n");
    o = new Room("o");
    p = new Room("p");
    q = new Room("q");
        q->addItem(Greenkey);
        q->addItem(fl3);
    r = new Room("outside");
    s = new Room("s");
        s->addItem(fl4);


    //             (N, E, S, W)
    a->setExits(NULL, b, e, c);
    b->setExits(NULL, NULL, NULL, a);
    c->setExits(NULL, a, d, NULL);
    d->setExits(c, e, NULL, NULL);
    e->setExits(a, NULL, NULL, d);
    f->setExits(NULL, NULL, NULL, NULL);
    g->setExits(j, h, NULL, NULL);
    h->setExits(k, NULL, NULL, g);
    i->setExits(m, j, NULL, NULL);
    j->setExits(n, k, g, i);
    k->setExits(o, NULL, h, j);
    l->setExits(p, m, NULL, NULL);
    m->setExits(q, NULL, i, l);
    n->setExits(NULL, o, j, NULL);
    o->setExits(s, NULL, k, n);
    p->setExits(NULL, q, l, NULL);
    q->setExits(NULL, NULL, m, p);
    r->setExits(NULL, NULL, NULL, NULL);
    s->setExits(NULL, NULL, o, NULL);

    currentRoom = a;
    monsterRoom = j;

    //*Door = new Door("Sample", code value, "south", e) template.
    Purpledoor = new Door("Purpledoor", 13, "south", f);
    Bluedoor = new Door("Bluedoor", 12, "north", g);
    Greendoor = new Door("Greendoor", 14, "east", n);
    Orangedoor = new Door("Orangrdoor", 15, "north", r);
    b->addDoor(Purpledoor);
    a->addDoor(Bluedoor);
    m->addDoor(Greendoor);
    n->addDoor(Orangedoor);

}

void MainWindow::checkMonster() {
    cout << "Check monster hit" << endl;
    cout << currentRoom->shortDescription() << endl;
    cout << monsterRoom->shortDescription() << endl;
    // We could remove this now

    //parser.getCommand("quit");
    if(currentRoom->shortDescription() == monsterRoom->shortDescription()){
        cout << "YOU HAVE BEEN EATEN" << endl;

        QMessageBox msgBox;
        msgBox.setText(tr("YOU HAVE BEEN EATEN!"));
        QAbstractButton* playagain = msgBox.addButton(tr("Play again"), QMessageBox::YesRole);
        QAbstractButton* quitnow = msgBox.addButton(tr("Quit"), QMessageBox::YesRole);

        msgBox.exec();

        if (msgBox.clickedButton()==playagain) {
            qApp->quit();
            QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        }
        if (msgBox.clickedButton()==quitnow) {
            QApplication::quit();
        }

    }


    // I want to delete this - Will

//    string arrayNum[4] = {"north","south","east","west"};
//    for(int dir =0; dir <4; dir = dir+1){
//        currentRoomMonsterCheck = currentRoom;
//        string direction = arrayNum[dir];

//        Room* nextRoom = currentRoomMonsterCheck->nextRoom(direction);
//        if(nextRoom == monsterRoom){
//            cout << "The Monster Lurks near " << nextRoom->longDescription() << " " << direction << endl;
//            QMessageBox msgBox;
//            msgBox.setText(tr("The Monster Lurks near"));
//            msgBox.exec();
//            dir =5;
//        }

//    }

}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(cutAct);
    menu.addAction(copyAct);

    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

void MainWindow::restart()
{
    //infoLabel->setText(tr("Invoked <b>File|New</b>"));
    cout << "restart" << endl;
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}


void MainWindow::quit()
{
    // infoLabel->setText(tr("Invoked <b>File|Open</b>"));
    QApplication::quit();
}

void MainWindow::about()
{
    //    infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("PanQ presents Outside"),
                       tr("This Project has been lovingly hand-crafted by Patrick Cumiskey and William Flaherty."));
}



void MainWindow::createActions()
{
    newAct = new QAction(tr("&Restart"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Restart Game"));
    connect(newAct, &QAction::triggered, this, &MainWindow::restart);

    openAct = new QAction(tr("&Quit"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Quit the game"));
    connect(openAct, &QAction::triggered, this, &MainWindow::quit);


    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    cutAct = new QAction(tr("Restart"), this);
    connect(cutAct, &QAction::triggered, this, &MainWindow::restart);

    copyAct = new QAction(tr("Quit"), this);
    connect(copyAct, &QAction::triggered, this, &MainWindow::quit);

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Options"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    //    helpMenu->addAction(aboutQtAct);

}
