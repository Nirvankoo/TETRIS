#ifndef SCORE_H
#define SCORE_H
#include "shapes.h"

class Score
{
    private:
    int score;
    int level;

    public:
    Score();
    ~Score();

    //setters
    void set_score(int score);
    void set_level();

    //getters
    int get_score();
    int get_level();

    //miscellaneous
    void show_score_on_screen(int x, int y);
};

extern Score score_obj;



#endif // !SCORE_H
