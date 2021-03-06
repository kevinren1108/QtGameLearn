#include "Game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "Enemy.h"
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>
#include <QMediaPlaylist>

Game::Game(QWidget *parent)
{
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,400,800); // make the scene 800x600 instead of infinity by infinity (default)

    setBackgroundBrush(QBrush(QImage(":/images/bg.png")));

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(400,800);

    // create the player
    player = new Player();
    //player->setRect(0,0,100,100); // change the rect from 0x0 (default) to 100x100 pixels
    player->setPos(150,700); // TODO generalize to always be in the middle bottom of screen
    // make the player focusable and set it to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // add the player to the scene
    scene->addItem(player);

    // create the score/health
    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);

    // spawn enemies
    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(2000);

    /*QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/bgsound.mp3"));
    //music->play();

    while(music->state() == QMediaPlayer::StoppedState)
    {
        music->play();
    }*/

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/bgsound.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();

    show();
}
