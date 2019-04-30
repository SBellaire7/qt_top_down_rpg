#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QPainter>
#include <QBrush>
#include <QPen>

#include "entity.h"
#include "tile.h"
#include "player.h"

#include <QKeyEvent>
#include <QProgressBar>
#include <QTimer>

#include <QSound>

struct Level
{
    Tile* tiles;
    int size;
};

struct Inventory
{
    int estusCount;
    int estusCountMax;
    int estusUpgrades;

    int ashenEstusCount;
    int ashenEstusCountMax;
    int ashenEstusUpgrades;

    int greenBlossomCount;
};

typedef struct Level Level;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    //level variables
    Level currentLevel;
    int levelXDim;
    int levelYDim;

    //camera positioning
    double cameraOffsetX;
    double cameraOffsetY;

    //player UI
    QProgressBar healthBar;
    QProgressBar staminaBar;
    QProgressBar manaBar;
    Inventory inventory;

    //event timing
    QTimer masterTimer;

    //entities
    Player player;

    //player variables
    bool staminaDrained;

    //fonts
    QFont optimusPrinceps;

    //sounds
    QSound *estusSound;
    QSound *swordSound;
    QSound *blossomSound;

    //event handlers
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

    void setup();
    void setupUi();
    Level createLevel(std::string fileName);
    void moveEntity(Entity &e);
    void cameraUpdate();
    void doPlayerUpdate();

private:
    Ui::Widget *ui;

private slots:
    void doUpdate();
};

#endif // WIDGET_H
