#include <iostream>
#include <windows.h>
#include <ctime>
#include <vector>
using namespace std;


void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}


class bomba
{
private:
    bool bom1 = false, bomb1 = false, game = false;
    time_t start;
    time_t interval;
    time_t ex1, ex2;
    int bx1, by1, ai;
public:
    bomba(int a, int b, int c) :bx1(a), by1(b), ai(c)
    {
        time(&start);
    }
    void check(char A[][19], int vx, int vy, int aix, int aiy)
    {
        A[vy][vx] = 'O';
        if (A[by1][bx1] != '*')
            A[by1][bx1] = '@';
        time(&interval);
        double dif = difftime(interval, start);
        if (dif >= 3)
        {
            if (bomb1 == false)
            {
                A[by1][bx1] = '*';
                bool up = false, down = false, left = false, right = false;
                for (int i = 1; i < 3; i++)
                {
                    if (A[by1 + i][bx1] == 'X')
                        down = true;
                    if (A[by1 + i][bx1] == 'O' && down == false)
                    {
                        game = true;
                    }
                    if (by1 + i == aiy && bx1 == aix && down == false)
                    {
                        game = true;
                    }
                    if ((A[by1 + i][bx1] == ' ' || A[by1 + i][bx1] == '+') && down == false)
                    {
                        A[by1 + i][bx1] = '*';
                    }

                    if (A[by1 - i][bx1] == 'X')
                        up = true;
                    if (A[by1 - i][bx1] == 'O' && up == false)
                    {
                        game = true;
                    }
                    if (by1 - i == aiy && bx1 == aix && down == false)
                    {
                        game = true;
                    }
                    if ((A[by1 - i][bx1] == ' ' || A[by1 - i][bx1] == '+') && up == false)
                    {
                        A[by1 - i][bx1] = '*';
                    }

                    if (A[by1][bx1 - i] == 'X')
                        left = true;
                    if (A[by1][bx1 - i] == 'O' && left == false)
                    {
                        game = true;
                    }
                    if (by1 == aiy && bx1 - i == aix && down == false)
                    {
                        game = true;
                    }
                    if ((A[by1][bx1 - i] == ' ' || A[by1][bx1 - i] == '+') && left == false)
                    {
                        A[by1][bx1 - i] = '*';
                    }

                    if (A[by1][bx1 + i] == 'X')
                        right = true;
                    if (A[by1][bx1 + i] == 'O' && right == false)
                    {
                        game = true;
                    }
                    if (by1 == aiy && bx1 + i == aix && down == false)
                    {
                        game = true;
                    }
                    if ((A[by1][bx1 + i] == ' ' || A[by1][bx1 + i] == '+') && right == false)
                    {
                        A[by1][bx1 + i] = '*';
                    }

                }
                time(&ex1);
                bomb1 = true;
            }
            else if (bomb1 == true)
            {
                time(&ex2);
                double tarp = difftime(ex2, ex1);
                if (tarp >= 1)
                {
                    for (int i = 1; i < 3; i++)
                    {
                        if (A[by1 + i][bx1] == '*')
                        {
                            A[by1 + i][bx1] = ' ';
                        }
                        if (A[by1 - i][bx1] == '*')
                        {
                            A[by1 - i][bx1] = ' ';
                        }
                        if (A[by1][bx1 - i] == '*')
                        {
                            A[by1][bx1 - i] = ' ';
                        }
                        if (A[by1][bx1 + i] == '*')
                        {
                            A[by1][bx1 + i] = ' ';
                        }
                    }
                    A[by1][bx1] = ' ';
                    bx1 = -1;
                    by1 = -1;
                    bomb1 = false;
                }
            }
        }
        A[vy][vx] = ' ';
    }
    bool pab()
    {
        if (bx1 == -1)
            return true;
        else return false;
    }
    bool gameo()
    {
        if (game)
            return true;
        else return false;
    }
    bool pabai()
    {
        if (ai == 1 && bx1 == -1)
            return true;
        else return false;
    }
};

class robot
{
private:
    bool aibomb = false;
    vector <bomba> x;
public:
    friend class bomba;

    void ah(char A[][19],int &vy,int &vx,int &aiy,int &aix, bool &gameover)
    {
    A[vy][vx] = 'O';
    int distdown = 100, inc = 0, distup = 100, distleft = 100, distright = 100;

    /// bombu deliojimas
    if (A[aiy + 1][aix] == 'O' && aibomb == false)
    {
        bomba poof(aix, aiy, 1);
        x.push_back(poof);
        aibomb = true;
    }
    /*if ((A[aiy + 1][aix] == 'O' || A[aiy + 1][aix] == '/') && aibomb == false)
    {
        bomba poof(aix, aiy, 1);
        x.push_back(poof);
        aibomb = true;
    }*/
    if (A[aiy - 1][aix] == 'O' && aibomb == false)
    {
        bomba poof(aix, aiy, 1);
        x.push_back(poof);
        aibomb = true;
    }
    if (A[aiy][aix + 1] == 'O' && aibomb == false)
    {
        bomba poof(aix, aiy, 1);
        x.push_back(poof);
        aibomb = true;
    }
    if (A[aiy][aix - 1] == 'O' && aibomb == false)
    {
        bomba poof(aix, aiy, 1);
        x.push_back(poof);
        aibomb = true;
    }
    /// bomb planting^

    while (A[aiy + inc][aix] != 'X')
    {
        if (A[aiy + inc][aix] == '@')
            distdown = inc;
        if (distdown < 5)
        {
            int r = rand() % 3;
            if (r == 0 && A[aiy - 1][aix] == ' ')
            {
                aiy--;
            }
            if (r == 1 && A[aiy][aix - 1] == ' ')
                aix--;
            if (r == 2 && A[aiy][aix + 1] == ' ')
                aix++;
            break;
        }
        inc++;
    }
    inc = 0;
    while (A[aiy - inc][aix] != 'X')
    {
        if (A[aiy - inc][aix] == '@')
            distup = inc;
        if (distup < 5)
        {
            int r = rand() % 3;
            cout << r;
            if (r == 0 && A[aiy + 1][aix] == ' ')
            {
                aiy++;
            }
            if (r == 1 && A[aiy][aix - 1] == ' ')
                aix--;
            if (r == 2 && A[aiy][aix + 1] == ' ')
            {
                aix++;
            }
            break;
        }
        inc++;
    }
    inc = 0;
    while (A[aiy][aix - inc] != 'X')
    {
        if (A[aiy][aix - inc] == '@')
            distleft = inc;
        if (distleft < 5)
        {
            int r = rand() % 3;
            if (r == 0 && A[aiy][aix + 1] == ' ')
                aix++;
            if (r == 1 && A[aiy - 1][aix] == ' ')
                aiy--;
            if (r == 2 && A[aiy + 1][aix] == ' ')
                aiy++;
            break;
        }
        inc++;
    }
    inc = 0;
    while (A[aiy][aix + inc] != 'X')
    {
        if (A[aiy][aix + inc] == '@')
            distright = inc;
        if (distright < 5)
        {
            int r = rand() % 3;
            if (r == 0 && A[aiy][aix - 1] == ' ')
                aix--;
            if (r == 1 && A[aiy - 1][aix] == ' ')
                aiy--;
            if (r == 2 && A[aiy + 1][aix] == ' ')
                aiy++;
            break;
        }
        inc++;
    }


    if (vy < aiy && A[aiy - 1][aix] == ' ' && distup > 4)
    {
        aiy--;
    }
    else if (vx < aix && A[aiy][aix - 1] == ' ' && distleft > 4)
    {
        aix--;
    }
    else if (vy > aiy && A[aiy + 1][aix] == ' ' && distdown > 4)
    {
        aiy++;
    }
    else if (vx > aix && A[aiy][aix + 1] == ' ' && distright > 4)
    {
        aix++;
    }
    /* DistanceToPlayer = (vy-aiy)*(vy-aiy)+(vx-aix)*(vx-aix);
       DistanceToAI1 = (aiy1-aiy)*(aiy1-aiy)+(aix1-aix)*(aix1-aix);
       if(DistanceToPlayer < DistanceToAI1)
       {
        if (vy < aiy && A[aiy - 1][aix] == ' ' && distup > 4)
        {
            aiy--;
        }
        else if (vx < aix && A[aiy][aix - 1] == ' ' && distleft > 4)
        {
            aix--;
        }
        else if (vy > aiy && A[aiy + 1][aix] == ' ' && distdown > 4)
        {
            aiy++;
        }
        else if (vx > aix && A[aiy][aix + 1] == ' ' && distright > 4)
        {
            aix++;
        }
       }
       else
       {
         if (aiy1 < aiy && A[aiy - 1][aix] == ' ' && distup > 4)
        {
            aiy--;
        }
        else if (aix1 < aix && A[aiy][aix - 1] == ' ' && distleft > 4)
        {
            aix--;
        }
        else if (aiy1 > aiy && A[aiy + 1][aix] == ' ' && distdown > 4)
        {
            aiy++;
        }
        else if (aix1 > aix && A[aiy][aix + 1] == ' ' && distright > 4)
        {
            aix++;
        }
       }
    */

    else if (aibomb == false) {
        bomba poof(aix, aiy, 1);
        x.push_back(poof);
        aibomb = true;
    }
    A[vy][vx] = ' ';
    if (aibomb == true)
    {
        if (x[0].gameo())
        {
            gameover = true;
        }
        x[0].check(A, vx, vy, aix, aiy);
        if (x[0].pabai())
            aibomb = false;
        if (x[0].pab())
            x.erase(x.begin());
    }
    Sleep(30);
    }
};

class bomber
{
private:
    int vx = 1, vy = 1, bx1 = -1, by1 = -1, bombkiek = 0, aiy = 11, aix = 17;
    bool gameover = false, bom1 = false, bomb1 = false, aibomb = false;
    time_t start;
    time_t interval;
    time_t ex1, ex2;
    vector <bomba> bombos;
    robot ai1;
    char A[13][19] = { 'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',
                       'X',' ',' ','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','X',
                       'X',' ','X','+','X','+','X','+','X','+','X','+','X','+','X','+','X','+','X',
                       'X','+',' ',' ','+','+','+','+','+','+','+','+','+','+','+',' ',' ','+','X',
                       'X','+','X',' ','X','+','X','+','X',' ','X','+','X','+','X','+','X','+','X',
                       'X','+',' ',' ','+',' ','+','+','+',' ','+','+','+','+','+','+','+','+','X',
                       'X','+','X','+','X','+','X','+','X',' ','X','+','X','+','X','+','X','+','X',
                       'X','+','+','+','+',' ',' ',' ',' ',' ','+','+',' ','+','+','+','+','+','X',
                       'X','+','X','+','X','+','X',' ','X',' ','X','+','X','+','X','+','X','+','X',
                       'X','+','+','+','+','+','+','+',' ',' ','+',' ',' ',' ','+',' ',' ','+','X',
                       'X','+','X','+','X','+','X','+','X','+','X','+','X','+','X','+','X',' ','X',
                       'X','+',' ',' ','+','+','+','+','+','+','+','+','+','+','+','+',' ',' ','X',
                       'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X' };
public:
    bomber() {

    }
    ~bomber() {}
    friend class bomba;
    void map()
    {
        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 19; j++)
            {
                if (i == vy && j == vx)
                    cout << "O";
                else if (i == aiy && j == aix)
                {
                    cout << "?";
                }
                else cout << A[i][j];
            }
            cout << endl;
        }
    }
    void inp()
    {
        if (GetKeyState(VK_UP) < 0 && (A[vy - 1][vx] == ' '))
        {
            vy--;
            Sleep(13);
        }
        if (GetKeyState(VK_UP) < 0 && A[vy - 1][vx] == '*')
        {
            gameover = true;
        }
        if (GetKeyState(VK_DOWN) < 0 && (A[vy + 1][vx] == ' '))
        {
            vy++;
            Sleep(13);
        }
        if (GetKeyState(VK_DOWN) < 0 && A[vy + 1][vx] == ' *')
        {
            gameover = true;
        }
        if (GetKeyState(VK_LEFT) < 0 && (A[vy][vx - 1] == ' '))
        {
            vx--;
        }
        if (GetKeyState(VK_LEFT) < 0 && A[vy][vx - 1] == '*')
        {
            gameover = true;
        }
        if (GetKeyState(VK_RIGHT) < 0 && (A[vy][vx + 1] == ' '))
        {
            vx++;
        }
        if (GetKeyState(VK_RIGHT) < 0 && A[vy][vx + 1] == '*')
        {
            gameover = true;
        }
    }

    /*void AI()
    {
        A[vy][vx] = 'O';
        int distdown = 100, inc = 0, distup = 100, distleft = 100, distright = 100;
        if (A[aiy + 1][aix] == 'O' && aibomb == false)
        {
            bomba poof(aix, aiy, 1);
            bombos.push_back(poof);
            aibomb = true;
        }
        if (A[aiy - 1][aix] == 'O' && aibomb == false)
        {
            bomba poof(aix, aiy, 1);
            bombos.push_back(poof);
            aibomb = true;
        }
        if (A[aiy][aix + 1] == 'O' && aibomb == false)
        {
            bomba poof(aix, aiy, 1);
            bombos.push_back(poof);
            aibomb = true;
        }
        if (A[aiy][aix - 1] == 'O' && aibomb == false)
        {
            bomba poof(aix, aiy, 1);
            bombos.push_back(poof);
            aibomb = true;
        }
        while (A[aiy + inc][aix] != 'X')
        {
            if (A[aiy + inc][aix] == '@')
                distdown = inc;
            if (distdown < 5)
            {
                int r = rand() % 3;
                if (r == 0 && A[aiy - 1][aix] == ' ')
                {
                    aiy--;
                }
                if (r == 1 && A[aiy][aix - 1] == ' ')
                    aix--;
                if (r == 2 && A[aiy][aix + 1] == ' ')
                    aix++;
                break;
            }
            inc++;
        }
        inc = 0;
        while (A[aiy - inc][aix] != 'X')
        {
            if (A[aiy - inc][aix] == '@')
                distup = inc;
            if (distup < 5)
            {
                int r = rand() % 3;
                if (r == 0 && A[aiy + 1][aix] == ' ')
                {
                    aiy++;
                }
                if (r == 1 && A[aiy][aix - 1] == ' ')
                    aix--;
                if (r == 2 && A[aiy][aix + 1] == ' ')
                    aix++;
                break;
            }
            inc++;
        }
        inc = 0;
        while (A[aiy][aix - inc] != 'X')
        {
            if (A[aiy][aix - inc] == '@')
                distleft = inc;
            if (distleft < 5)
            {
                int r = rand() % 3;
                if (r == 0 && A[aiy][aix + 1] == ' ')
                    aix++;
                if (r == 1 && A[aiy - 1][aix] == ' ')
                    aiy--;
                if (r == 2 && A[aiy + 1][aix] == ' ')
                    aiy++;
                break;
            }
            inc++;
        }
        inc = 0;
        while (A[aiy][aix + inc] != 'X')
        {
            if (A[aiy][aix + inc] == '@')
                distright = inc;
            if (distright < 5)
            {
                int r = rand() % 3;
                if (r == 0 && A[aiy][aix - 1] == ' ')
                    aix--;
                if (r == 1 && A[aiy - 1][aix] == ' ')
                    aiy--;
                if (r == 2 && A[aiy + 1][aix] == ' ')
                    aiy++;
                break;
            }
            inc++;
        }
        if (vy < aiy && A[aiy - 1][aix] == ' ' && distup > 4)
        {
            aiy--;
        }
        else if (vx < aix && A[aiy][aix - 1] == ' ' && distleft > 4)
        {
            aix--;
        }
        else if (vy > aiy && A[aiy + 1][aix] == ' ' && distdown > 4)
        {
            aiy++;
        }
        else if (vx > aix && A[aiy][aix + 1] == ' ' && distright > 4)
        {
            aix++;
        }
        else if (aibomb == false) {
            bomba poof(aix, aiy, 1);
            bombos.push_back(poof);
            aibomb = true;
        }
        A[vy][vx] = ' ';
        Sleep(30);

    }*/

    void engine()
    {
        while (!gameover)
        {
            clearscreen();
            map();
            inp();
            //AI();
            //robot ai1;
            ai1.ah(A,vy,vx,aiy,aix,gameover);
           
            if (GetKeyState(VK_SPACE) < 0)
            {
                bomba poof(vx, vy, 0);
                bombos.push_back(poof);
            }
            for (int i = 0; i < bombos.size(); i++)
            {
                bombos[i].check(A, vx, vy, aix, aiy);
                if (bombos[i].gameo())
                {
                    gameover = true;
                }
                if (bombos[i].pabai())
                    aibomb = false;
                if (bombos[i].pab())
                    bombos.erase(bombos.begin() + i);
            }
            Sleep(30);
        }
        system("cls");
        map();
        cout << "Zaidimas baigesi" << endl;
        int n;
        cin >> n;
    }
    void clearscreen()
    {
        HANDLE hOut;
        COORD Position;

        hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        Position.X = 0;
        Position.Y = 0;
        SetConsoleCursorPosition(hOut, Position);
    }
};

int main()
{
    ShowConsoleCursor(false);
    cout << "Spauskite Enter, jeigu norite pradeti arba Esc, jeigu norite iseiti" << endl;
    while (true)
    {
        if (GetKeyState(VK_ESCAPE) < 0)
        {
            return 0;
        }
        if (GetKeyState(VK_RETURN) < 0)
        {
            break;
        }
    }
    
    bomber x;
    system("cls");
    x.engine();
}