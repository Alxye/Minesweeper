#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <windows.h>
#include <iostream>
#include <list>
#include <sstream>
using namespace std;
using namespace sf;
#define gridsize 34
#define level_1_width 9
#define level_1_height 9
#define level_1_mine_amount 10      // the amount of mine in level 1
#define level_2_width 16
#define level_2_height 16
#define level_2_mine_amount 40
#define level_3_width 30
#define level_3_height 16
#define level_3_mine_amount 99
//define grid state
typedef enum gridtype {
	nc_bg_null,             // blank area
	nc_bg_sqr,              // background grid
	nc_mine,                // mine
	nc_one,                 // number 1
	nc_two,                 // number 2
	nc_there,               // number 3
	nc_four,                // number 4
	nc_five,                // number 5
	nc_six,                 // number 6
	nc_seven,               // number 7
	nc_eight,               // number 8
	nc_flag,                // sign
	nc_question_mark,       // question mark
	nc_backup,              // this one is used for backup
	nc_bombing_mine,        // mine that is found
	nc_unfound_mine         // mine that is not found
};
typedef enum gameover_state {
	nc_gameover_false,      // game has not over
	nc_game_win,            // win the game
	nc_game_lose            // lose the game
};

class class_mine
{
public:
	int grid_state;         // the state of mine(grid)
	int grid_state_backup;  // back the state of mine(grid) up
	bool is_press_grid;     // judge whether the mine(grid) is clicked or not

private:

};
class Game{
public:
	sf::RenderWindow window;
	Game();
	~Game();
	bool start_animator,gameover,gamequit,gamebegin;
	int change_time_number;
	int counter[30][30];
	int window_width, window_height, stage_width, stage_height;
	int grid_mine_amount, grid_flag_calulate;
	int game_level, mines_amount; // set game difficulty & time count
	int is_gameover_state;        // the state of gameover
	int grid_size;                // the size of each grid
	int game_time;                // the counter of each round
	int image_background_No, image_skin_No;
	class_mine game_data[level_3_height][level_3_width];  // set the most difficult stage size as array
	Vector2i stage_cornpoint;    // the coordinate of Left Vertex in stage
	Vector2i p1, p2;
	Texture texture_background, texture_tile, texture_buttoms, texture_number, texture_timer, texture_counter, texture_gameover; // create texture objects
	Sprite sprite_background, sprite_tile, sprite_buttoms, sprite_number, sprite_timer, sprite_counter, sprite_gameover;   // create sprite objects
	IntRect button_easy, button_normal, button_hard,button_background,button_skin,button_restart,button_quit; // create button objects
	SoundBuffer sound_buffer_win, sound_buffer_boom;
	Sound sound_win, sound_boom;
	Music background_music;
	Clock mouse_click_timer,game_clock;	 // a clock start counting as soon as its created
	void Temp_Animator_one(int X_Y_to_color,int _x, int _y,int limit_number);
	void Run();
	
	void Initial();
	void Initial_Data();
	void Initial_Media_Data();
	void Initial_Load_Image(Texture& texture, Sprite& sprite, string filename, float originX, float originY, float factorX, float factorY);
	void Initial_Load_Sound(Sound& sound, SoundBuffer& soundbuffer, string filename);
	void Initial_Load_Music(Music& music, string filename);
	void Mine_Set(int Py,int Px);     // set mine

	void Input();
	void Right_Buttom_Down(Vector2i mPoint);
	void Left_Buttom_Down(Vector2i mPoint);
	void Left_Buttom_DoubleClick(Vector2i mPoint);

	void Logic();
	void Logic_Is_Win();
	void Logic_Uncover();

	void Draw();
	void Draw_Grid();
	void Draw_Button();
	void Draw_Button_Locate(IntRect& button, Vector2i left_corner, int locate_info, Sprite sprite_buttoms, int deta_X, int button_width, int button_height);
	void Draw_Score();
	void Draw_Timer();
	void Draw_Game_End();
	void Draw_Grid_Animator();
};
//�����ܹ�Ϊ�������Animation
class Animator{
public:
	//creat structure,this one can creat&store animation then add it to sprite
	struct Animation {
		std::string m_Name;
		std::string m_TextureName;
		std::vector<sf::IntRect> m_Frames;
		sf::Time m_Duration;
		bool m_looping;
		Animation(std::string const& name, std::string const& textureName, sf::Time const& duration, bool looping) : m_Name(name), m_TextureName(textureName), m_Duration(duration), m_looping(looping) {}
		//AddFrames() �����ܹ���ͼƬ����ˮƽ�����и��ÿһ֡����m_Frames��
		void AddFrames(sf::Vector2i const& startFrom, sf::Vector2i const& frameSize, unsigned int frames) {
			sf::Vector2i current = startFrom;
			for (unsigned int i = 0; i < frames; i++) {
				m_Frames.push_back(sf::IntRect(current.x, current.y, frameSize.x, frameSize.y));
				current.x += frameSize.x;
			}
		}
	};

	Animator(sf::Sprite& sprite);
	//Animator::CreateAnimation() ͨ�������Ĳ�������һ������Ч����
	
	Animator::Animation& CreateAnimation(std::string const& name,std::string const& textureName, sf::Time const& duration, bool loop = false);
	
	//Animation�ǻ���ʱ��仯�ģ�������Ҫһ��Animatot::Update()����ȥ����
	void Update(sf::Time const& dt);

	// �Ƿ��л��ɹ�
	bool SwitchAnimation(std::string const& name);

	std::string GetCurrentAnimationName() const;
private:
	// ͨ�����ֲ����Ѿ���ӹ��Ķ���Ч�� Animation
	Animator::Animation* FindAnimation(std::string const& name);
	
	//Animator::SwitchAnimation()�ܹ��л�����Ч��
	void SwitchAnimation(Animator::Animation* animation);

	// sprite ������(���ͣ�Sprite ���Ƕ����� Animitor �����ʵ������һ�����á�����ζ�����ǵľ��������ⲿ����ģ�Ȼ���� Animitor �Ĺ��췽���л�ȡ������ã�
	sf::Sprite& m_Sprite;
	
	sf::Time m_CurrentTime;//m_CurrentTime ��ʱ���ۼ��������ø�ǰ���ᵽ��һ����m_Animations ���������ж���Ч�������ﲻ�� vector ������ list ����Ϊ vector ���ܲ��ܱ���ָ�������������
	std::list<Animator::Animation> m_Animations;
	Animator::Animation* m_CurrentAnimation;
};
/**
 * ��Դ������
 */
#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include <map>
#include <assert.h>
class AssetManager
{
public:
	AssetManager();

	static sf::Texture& GetTexture(std::string const& filename);

private:
	std::map<std::string, sf::Texture> m_Textures;

	static AssetManager* sInstance;
};
#endif