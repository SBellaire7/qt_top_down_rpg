#include "widget.h"
#include "ui_widget.h"

#include <cmath>
#include <fstream>
#include <iostream>

#include <QGridLayout>
#include <QFontDatabase>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //setup init
    setup();

    //connect timers to event handlers
    connect(&masterTimer, SIGNAL(timeout()), this, SLOT(doUpdate()));

    //set ui grid layout
    QGridLayout *g;
    g = new QGridLayout;

    g->addWidget(&healthBar, 0, 0, 1, 1);
    g->addWidget(&staminaBar, 1, 0, 1, 1);
    g->addWidget(&manaBar, 2, 0, 1, 1);

    g->setRowStretch(0, 3);
    g->setRowStretch(1, 3);
    g->setRowStretch(2, 3);
    g->setRowStretch(3, 91);

    g->setColumnStretch(0, 50);
    g->setColumnStretch(1, 50);

    this->setLayout(g);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *e)
{
    //color init
    QColor white(255, 255, 255);
    QColor black(0, 0, 0);
    QColor red(255, 0, 0);
    QColor green(0, 255, 0);
    QColor blue(0, 0, 255);

    //qpainter init
    QPainter p(this);
    QBrush brush(white);
    QPen pen(black);
    p.setBrush(brush);
    p.setPen(pen);
    p.setFont(optimusPrinceps);

    //draw test level
    for(int i = 0; i < currentLevel.size; i++)
    {
        QImage img(currentLevel.tiles[i].sprite());
        int x = static_cast<int>(currentLevel.tiles[i].x() - cameraOffsetX);
        int y = static_cast<int>(currentLevel.tiles[i].y() - cameraOffsetY);

        p.drawImage(x, y, img);
    }

    //get the position to draw the player
    double x = player.x() - cameraOffsetX;
    double y = player.y() - cameraOffsetY;

    //draw the player
    if(player.attackTimer() > 0 && player.direction() == "up")
        p.drawImage(static_cast<int>(x), static_cast<int>(y - 20), player.sprite()); //if player is attacking and facing up, special case
    else if(player.attackTimer() > 0 && player.direction() == "left")
        p.drawImage(static_cast<int>(x - 20), static_cast<int>(y), player.sprite()); //if player is attacking and facing left, special case
    else p.drawImage(static_cast<int>(x), static_cast<int>(y), player.sprite()); //otherwise

    //draw rect under UI
    p.drawRect(QRect(0, 0, 640, 100));

    //draw the inventory

    //estus
    if(inventory.estusCount > 0.6 * inventory.estusCountMax) p.drawImage(340, 12, QImage("inventory_images/estus_full.png"));
    else if(inventory.estusCount > 0.25 * inventory.estusCountMax) p.drawImage(340, 12, QImage("inventory_images/estus_60.png"));
    else if(inventory.estusCount > 0) p.drawImage(340, 12, QImage("inventory_images/estus_25.png"));
    else p.drawImage(340, 12, QImage("inventory_images/estus_empty.png"));
    p.drawText(QPoint(410, 92), QString(QString::number(inventory.estusCount)));

    if(inventory.ashenEstusCount > 0.6 * inventory.ashenEstusCountMax) p.drawImage(440, 12, QImage("inventory_images/ashen_estus_full.png"));
    else if(inventory.ashenEstusCount > 0.25 * inventory.ashenEstusCountMax) p.drawImage(440, 12, QImage("inventory_images/ashen_estus_60.png"));
    else if(inventory.ashenEstusCount > 0) p.drawImage(440, 12, QImage("inventory_images/ashen_estus_25.png"));
    else p.drawImage(440, 12, QImage("inventory_images/ashen_estus_empty.png"));
    p.drawText(QPoint(510, 92), QString(QString::number(inventory.ashenEstusCount)));

    p.drawImage(540, 12, QImage("inventory_images/green_blossom.png"));
    p.drawText(QPoint(610, 92), QString(QString::number(inventory.greenBlossomCount)));
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_W)
    {
        player.setIsMovingRight(false);
        player.setIsMovingLeft(false);
        player.setIsMovingDown(false);
        player.setIsMovingUp(true);
        player.setDirection("up");
    }
    if(e->key() == Qt::Key_A)
    {
        player.setIsMovingRight(false);
        player.setIsMovingLeft(true);
        player.setIsMovingDown(false);
        player.setIsMovingUp(false);
        player.setDirection("left");
    }
    if(e->key() == Qt::Key_S)
    {
        player.setIsMovingRight(false);
        player.setIsMovingLeft(false);
        player.setIsMovingDown(true);
        player.setIsMovingUp(false);
        player.setDirection("down");
    }
    if(e->key() == Qt::Key_D)
    {
        player.setIsMovingRight(true);
        player.setIsMovingLeft(false);
        player.setIsMovingDown(false);
        player.setIsMovingUp(false);
        player.setDirection("right");
    }
    if(e->key() == Qt::Key_Space && player.attackCooldown() == 0)
    {
        player.setAttackTimer(player.attackSpeed());
        player.setAttackCooldown(2 * player.attackSpeed());
        swordSound->play();
    }
    if(e->key() == Qt::Key_H && player.estusCooldown() == 0 && inventory.estusCount > 0)
    {
        player.setEstusTimer(player.estusSpeed());
        player.setEstusCooldown(6 * player.estusSpeed());
        estusSound->play();
        inventory.estusCount--;
    }
    if(e->key() == Qt::Key_M && player.estusCooldown() == 0 && inventory.ashenEstusCount > 0)
    {
        player.setAshenEstusTimer(player.estusSpeed());
        player.setEstusCooldown(6 * player.estusSpeed());
        estusSound->play();
        inventory.ashenEstusCount--;
    }
    if(e->key() == Qt::Key_F && player.estusCooldown() == 0 && player.greenBlossomTimer() == 0 && inventory.greenBlossomCount > 0)
    {
        player.setGreenBlossomTimer(12 * player.estusSpeed());
        player.setEstusCooldown(6 * player.estusSpeed());
        player.setStaminaRegen(player.staminaRegen() + 1);
        blossomSound->play();
        inventory.greenBlossomCount--;
    }
}

void Widget::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_W)
    {
        player.setIsMovingUp(false);
    }
    if(e->key() == Qt::Key_A)
    {
        player.setIsMovingLeft(false);
    }
    if(e->key() == Qt::Key_S)
    {
        player.setIsMovingDown(false);
    }
    if(e->key() == Qt::Key_D)
    {
        player.setIsMovingRight(false);
    }
}

void Widget::setup()
{
    //setup levels
    currentLevel = createLevel("levels/testLevel2.txt");

    //init player vars
    QImage img("entity_images/link_front.png");

    player.setHp(10);
    player.setMana(10);
    player.setSprite(img);
    player.moveTo(200, 200);

    staminaDrained = false;

    //create player ui
    setupUi();

    //start master event timer
    masterTimer.start(17);

    //init sounds
    estusSound = new QSound("audio/itemuse/estus.wav");
    swordSound = new QSound("audio/combat/sword_swing.wav");
    blossomSound = new QSound("audio/itemuse/green_blossom.wav");

    //inventory
    inventory.estusCount = 5;
    inventory.estusCountMax = 5;
    inventory.estusUpgrades = 0;
    inventory.ashenEstusCount = 5;
    inventory.ashenEstusCountMax = 5;
    inventory.ashenEstusUpgrades = 0;
    inventory.greenBlossomCount = 5;

    //fonts
    optimusPrinceps.setFamily(QFontDatabase::applicationFontFamilies(
                                  QFontDatabase::addApplicationFont("fonts/OptimusPrinceps.ttf")).at(0));
    optimusPrinceps.setPointSize(25);
}

void Widget::setupUi()
{
    //create the health bar
    healthBar.setStyleSheet(
                "QProgressBar:horizontal {"
                "border: 1px solid gray;"
                "border-radius: 3px;"
                "background: white;"
                "height: 19px;"
                "padding: 1px;"
                "}"
                "QProgressBar::chunk:horizontal {"
                "background: red;"
                "}"
                );
    healthBar.setTextVisible(false);
    healthBar.setMinimum(0);
    healthBar.setMaximum(player.maxHp());
    healthBar.setOrientation(Qt::Horizontal);
    healthBar.setValue(static_cast<int>(player.hp()));

    //create the stamina bar
    staminaBar.setStyleSheet(
                "QProgressBar:horizontal {"
                "border: 1px solid gray;"
                "border-radius: 3px;"
                "background: white;"
                "height: 19px;"
                "padding: 1px;"
                "}"
                "QProgressBar::chunk:horizontal {"
                "background: green;"
                "}"
                );
    staminaBar.setTextVisible(false);
    staminaBar.setMinimum(0);
    staminaBar.setMaximum(player.maxStamina());
    staminaBar.setOrientation(Qt::Horizontal);
    staminaBar.setValue(static_cast<int>(player.stamina()));

    //create the mana bar
    manaBar.setStyleSheet(
                "QProgressBar:horizontal {"
                "border: 1px solid gray;"
                "border-radius: 3px;"
                "background: white;"
                "height: 19px;"
                "padding: 1px;"
                "}"
                "QProgressBar::chunk:horizontal {"
                "background: blue;"
                "}"
                );
    manaBar.setTextVisible(false);
    manaBar.setMinimum(0);
    manaBar.setMaximum(player.maxMana());
    manaBar.setOrientation(Qt::Horizontal);
    manaBar.setValue(static_cast<int>(player.mana()));
}

Level Widget::createLevel(std::string fileName)
{
    //create string of tiles
    std::string tileStr = "";

    //set up filestream
    std::ifstream levelFile;
    levelFile.open(fileName, std::fstream::in);

    //read in level data
    if(levelFile.is_open())
    {
        std::string str;
        levelYDim = 0;
        while(getline(levelFile, str))
        {
            tileStr = tileStr + str;
            levelYDim++;
        }
        levelXDim = static_cast<int>(str.length()); //set x dim
        levelFile.close();
    }

    //init new level
    Level newLevel;
    newLevel.size = static_cast<int>(tileStr.length());
    newLevel.tiles = new Tile[newLevel.size];

    //copy std str to c str
    char *tileChar = new char[newLevel.size];
    strcpy(tileChar, tileStr.c_str());

    //for all characters, create a corresponding tile
    for(int i = 0; i < newLevel.size; i++)
    {
        //load image
        QImage img;

        //grass
        if(tileChar[i] == '.')
        {
            img.load("tile_images/grass.png");
            newLevel.tiles[i] = Tile(64 * (i % levelXDim), 100 + 64 * (i / levelXDim), 64, img, true, false, false);
        }

        //wall
        else if(tileChar[i] == '#')
        {
            img.load("tile_images/wall.png");
            newLevel.tiles[i] = Tile(64 * (i % levelXDim), 100 + 64 * (i / levelXDim), 64, img, false, true, false);
        }

        //water
        else if(tileChar[i] == '~')
        {
            img.load("tile_images/water.png");
            newLevel.tiles[i] = Tile(64 * (i % levelXDim), 100 + 64 * (i / levelXDim), 64, img, false, false, false);
        }

        //door
        else if(tileChar[i] == 'D')
        {
            img.load("tile_images/door.png");
            newLevel.tiles[i] = Tile(64 * (i % levelXDim), 100 + 64 * (i / levelXDim), 64, img, true, false, true);
        }

        //stairs
        else if(tileChar[i] == 'S')
        {
            img.load("tile_images/stairs.png");
            newLevel.tiles[i] = Tile(64 * (i % levelXDim), 100 + 64 * (i / levelXDim), 64, img, true, false, true);
        }
    }

    return newLevel;
}

void Widget::moveEntity(Entity &e)
{
    //save previous position
    double prevX = e.x();
    double prevY = e.y();

    //move
    if(e.isMovingUp()) e.move(0, -e.moveSpeed() / 60.0);
    if(e.isMovingDown()) e.move(0, e.moveSpeed() / 60.0);
    if(e.isMovingLeft()) e.move(-e.moveSpeed() / 60.0, 0);
    if(e.isMovingRight()) e.move(e.moveSpeed() / 60.0, 0);

    //create hitbox for entity
    QRectF entityBox = e.sprite().rect();
    entityBox.moveTo(e.x(), e.y());

    QRectF tileBox;

    //check for entity collision with non walkable tiles
    for(int i = 0; i < currentLevel.size; i++)
    {
        if(!currentLevel.tiles[i].isWalkable())
        {
            Tile t = currentLevel.tiles[i];
            tileBox = t.sprite().rect();
            tileBox.moveTo(t.x(), t.y());

            //if entity is on non walkable tile, revert to prev position
            if(tileBox.intersects(entityBox))
            {
                e.moveTo(prevX, prevY);
                break;
            }
        }
    }
}

void Widget::cameraUpdate()
{
    //camera x offset
    if(player.x() < 305) cameraOffsetX = 0;
    else if(player.x() > levelXDim * 64 - 335) cameraOffsetX = levelXDim * 64 - 640;
    else cameraOffsetX = player.x() - 305;

    //camera y offset
    if(player.y() < 405) cameraOffsetY = 0;
    else if(player.y() > levelYDim * 64 - 235) cameraOffsetY = levelYDim * 64 - 640;
    else cameraOffsetY = player.y() - 405;
}

void Widget::doPlayerUpdate()
{
    //do attack cooldown
    if(player.attackCooldown() > 0) player.decAttackCooldown();

    //do estus cooldown
    if(player.estusCooldown() > 0) player.decEstusCooldown();

    //if attacking
    if(player.attackTimer() > 0)
    {
        //decrement attack timer and stamina
        player.decAttackTimer();
        player.incStamina(static_cast<double>(-player.staminaCost()) / player.attackSpeed());

        QImage img;

        //determine player sprite
        if(player.direction() == "up") img.load("entity_images/link_attack_up.png");
        if(player.direction() == "down") img.load("entity_images/link_attack_down.png");
        if(player.direction() == "left") img.load("entity_images/link_attack_left.png");
        if(player.direction() == "right") img.load("entity_images/link_attack_right.png");

        player.setSprite(img);
    }
    //if player is not attacking
    else
    {
        QImage img;

        //keep stamina drained for longer if it is all used
        if(player.stamina() < 0.01 && !staminaDrained)
        {
            player.setAttackCooldown(player.attackCooldown() + 4 * player.attackSpeed());
            staminaDrained = true;
        }

        //inc stamina if not attacking
        if(player.stamina() < player.maxStamina() && player.attackCooldown() == 0)
        {
            player.incStamina(player.staminaRegen());
            if(staminaDrained) staminaDrained = false;
        }

        //determine player sprite
        if(player.direction() == "up") img.load("entity_images/link_back.png");
        if(player.direction() == "down") img.load("entity_images/link_front.png");
        if(player.direction() == "left") img.load("entity_images/link_left.png");
        if(player.direction() == "right") img.load("entity_images/link_right.png");

        player.setSprite(img);

        //move the player
        moveEntity(player);
    }

    //healing and mana regen

    //estus heal
    if(player.estusTimer() > 0)
    {
        player.decEstusTimer();
        player.incHp(static_cast<double>(30 + (10 * inventory.estusUpgrades)) / player.estusSpeed());
    }

    //passive heal
    player.incHp(player.hpRegen());

    //green blossom
    if(player.greenBlossomTimer() > 0)
    {
        player.decGreenBlossomTimer();
        if(player.greenBlossomTimer() == 0) player.setStaminaRegen(player.staminaRegen() - 1);
    }

    //ashen estus mana regen
    if(player.ashenEstusTimer() > 0)
    {
        player.decAshenEstusTimer();
        player.incMana(static_cast<double>(30 + (10 * inventory.ashenEstusUpgrades)) / player.estusSpeed());
    }
    //passive mana regen
    player.incMana(player.manaRegen());
}

void Widget::doUpdate()
{
    //update player
    doPlayerUpdate();

    //update the ui
    healthBar.setValue(static_cast<int>(player.hp()));
    staminaBar.setValue(static_cast<int>(player.stamina()));
    manaBar.setValue(static_cast<int>(player.mana()));

    //camera updates
    cameraUpdate();

    repaint();
}
