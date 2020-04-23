#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <windows.h>
#include <iostream>
#include <sstream>
#define  GRIDSIZE 25
#define  LVL1_WIDTH 9
#define  LVL1_HEIGHT 9
#define  LVL1_NUM 10
#define  LVL2_WIDTH 16
#define  LVL2_HEIGHT 16
#define  LVL2_NUM 40
#define  LVL3_WIDTH 30
#define  LVL3_HEIGHT 16
#define  LVL3_NUM 99
//枚举定义网格状态
typedef enum GRIDSTATE {
	ncNULL,				//空地     0
	ncUNDOWN,		    //背景方块 1
	ncMINE,				//地雷     2
	ncONE,				//数字1    3
	ncTWO,				//数字2     
	ncTHREE,			//数字3
	ncFOUR,				//数字4
	ncFIVE,				//数字5
	ncSIX,				//数字6
	ncSEVEN,			//数字7
	ncEIGHT,			//数字8    10
	ncFLAG,				//标记     11
	ncQ,				//问号     12
	ncX,				//备用     13
	ncBOMBING,			//爆炸的雷
	ncUNFOUND			//未检测出来的雷
};
typedef enum GAMEOVERSTATE {
	ncNO,				//空地
	ncWIN,		    //背景方块
	ncLOSE,				//地雷
};
using namespace sf;			//SFML中的每个类都位于该命名空间之下，不设定sf命名空间的话，相应的函数前需要用作用域解析符，例如 sf::VideoMode(width* GRIDSIZE, height* GRIDSIZE)
using namespace std;
class LEI
{
public:
	int mState;//雷的状态
	int mStateBackUp;//备份状态
	//bool float_state;  // whether mouse moved on
	int backup_for_moveon;
	bool onclick;  
	bool isPress;//雷是否被按下
	bool isPressBackUp;//雷是否被按下
};

class Game
{
public:
	sf::RenderWindow window;
	Game();
	~Game();
	int change_time_number;
	int counter[30][30];
	bool gameOver, gameQuit;
	int Window_width, Window_height, stageWidth, stageHeight, mMineNum, mFlagCalc;
	int gameLvL, mTime;
	LEI mGameData[LVL3_HEIGHT][LVL3_WIDTH];//------->20*20的雷
	bool isGameBegin;//------->游戏是否开始
	int isGameOverState;//------->游戏结束的状态
	Vector2i mCornPoint;//游戏区域位置
	int gridSize;//块大小（15）
	int imgBGno, imgSkinNo;
	bool testMode;
	Texture tBackground, tTiles, tButtons, tNum, tTimer, tCounter, tGameOver;		//创建纹理对象
	Sprite	sBackground, sTiles, sButtons, sNum, sTimer, sCounter, sGameOver;		//创建精灵对象
	IntRect ButtonRectEasy, ButtonRectNormal, ButtonRectHard, ButtonRectBG, ButtonRectSkin, ButtonRectRestart, ButtonRectQuit;
	//Font font;
	//Text text;
	SoundBuffer sbWin, sbBoom;
	Sound soundWin, soundBoom;
	Music bkMusic;
	// A Clock starts counting as soon as it's created
	sf::Clock gameClock, mouseClickTimer;
	bool mouse_left_pressed;
	bool mouse_right_pressed;
	void Run();

	void Initial();
	void IniData();
	void LoadMediaData();
	void Initial_Load_Image(Texture& texture, Sprite& sprite, string filename, float originX, float originY, float factorX, float factorY);
	void Initial_Load_Sound(Sound& sound, SoundBuffer& soundbuffer, string filename);
	void Initial_Load_Music(Music& music, string filename);
	void MineSet(int Py, int Px);//布雷

	void Input();
	void RButtonDown(Vector2i mPoint);//------->鼠标右击
	void LButtonDblClk(Vector2i mPoint);//------->鼠标左击一下
	void LButtonDown(Vector2i mPoint);//------->鼠标左击两下
	void MouseMove(Vector2i mPoint);

	void NullClick(int j, int i);//查找空块

	void Logic();
	void Logic_Grid_officialize();
	void isWin();
	void unCover();

	void Draw();
	void DrawGrid();
	void DrawButton();
	void DrawScore();
	void DrawTimer();
	void DrawGameEnd();
};

