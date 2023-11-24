#ifndef SCORE_H
#define SCORE_H
#include "shapes.h"

class Score
{
    private:
    int score;
    int level;
    SDL_Texture *score_texture;
    SDL_Texture *level_texture;
    int score_width;
    int score_height;
    int level_width;
    int level_height;
    SDL_Point score_position;
    SDL_Point level_position;

    public:
    Score();
    Score(int score_x, int score_y, int level_x, int level_y);
    ~Score();

    //setters
    void set_score(int score);
    void set_level();
    void set_score_position(int x, int y);
    void set_level_position(int x, int y);

    //getters
    int get_score();
    int get_level();
    int get_score_position_x();
    int get_score_position_y();
    int get_level_position_x();
    int get_level_position_y();


    //miscellaneous
    bool load_score_media();
    void render_score(int x, int y, SDL_Rect *clip = NULL);
};

bool init_score_media();
extern Score score_obj;
void update_score();



#endif // !SCORE_H
