#include "YLWSUN.h"

using namespace std;

int board_sx = 900;
int board_sy = 900;

//Starship class used in combat
class Starship
{
private:

    double x_vel;
    double y_vel;

    //Starship's stats
    int s_hit; //Health
    int s_eng; //Acceleration
    int s_dmg; //Damage

public:

    //Starship's position
    int x_pos;
    int y_pos;
    int rotation;

    Starship()
    {
        //Set postion and rotation to a random number, because why not
        x_pos = (rand() % board_sx);
        y_pos = (rand() % board_sy);
        rotation = 0;

        //Set Health, Speed, and Damage to a random number
        s_hit = (rand() % 256 + 16);
        s_eng = (rand() % 16);
        s_dmg = (rand() % 16);
    }

    int shipAccel()
    {
        //Turn the degree of rotation into Radians
        double r = rotation * 3.14 / 180;
        //These return the current velocity that should be added to the current position, while also gradually increasing the velocity and taking into account the ship's engine stat, because trigonometry
        x_vel = sin(r) + (x_vel + (static_cast<double>(s_eng) * 0.01));
        y_vel = -1*cos(r) + (y_vel + (static_cast<double>(s_eng) * 0.01));

        cout << rotation << endl << x_vel << endl << y_vel;

        return 0;
    }

    int shipDeccel()
    {
        if (x_vel >= 0) {x_vel -= 0.1;}
        if (x_vel <= 0) {x_vel += 0.1;}
        if (y_vel >= 0) {y_vel -= 0.1;}
        if (y_vel <= 0) {y_vel += 0.1;}

        //cout << rotation << endl << x_vel << endl << y_vel;

        return 0;
    }

    int shipMove()
    {
        if (x_pos > board_sx) {x_pos = 0;}
        if (x_pos < 0) {x_pos = board_sx;}

        if (y_pos > board_sy) {y_pos = 0;}
        if (y_pos < 0) {y_pos = board_sy;}

        x_pos += x_vel;
        y_pos += y_vel;

        return 0;
    }

    int shipRotate(int i)
    {
        rotation += i;
        if (rotation > 360) {rotation = 0;}
        if (rotation < 0) {rotation = 360;}

        return 0;
    }

};

int main()
{
    srand(time(0));
    cout << "Yellow Sun v000 - Deep Winter Studios" << endl;
    initGUI(board_sx, board_sy);

    Starship playerShip;
    Starship enemyShip;

    bool exit = false;



    while (exit == false)
    {
        char *keyGet = refreshGUI(playerShip.x_pos, playerShip.y_pos,playerShip.rotation,0,0,0);
        if (keyGet[0] == 1) {
            playerShip.shipRotate(-4);
            //printf("Left\n");
        }
        if (keyGet[1] == 1) {
            playerShip.shipRotate(4);
            //printf("Right\n");
        }
        if(keyGet[2] == 1) {
            //printf("Up\n");
            playerShip.shipAccel();
        } else {playerShip.shipDeccel();}

        playerShip.shipMove();
    }

    return 0;
}
