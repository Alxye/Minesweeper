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
//ö�ٶ�������״̬
typedef enum GRIDSTATE {
	ncNULL,				//�յ�     0
	ncUNDOWN,		    //�������� 1
	ncMINE,				//����     2
	ncONE,				//����1    3
	ncTWO,				//����2     
	ncTHREE,			//����3
	ncFOUR,				//����4
	ncFIVE,				//����5
	ncSIX,				//����6
	ncSEVEN,			//����7
	ncEIGHT,			//����8    10
	ncFLAG,				//���     11
	ncQ,				//�ʺ�     12
	ncX,				//����     13
	ncBOMBING,			//��ը����
	ncUNFOUND			//δ����������
};
typedef enum GAMEOVERSTATE {
	ncNO,				//�յ�
	ncWIN,		    //��������
	ncLOSE,				//����
};
using namespace sf;			//SFML�е�ÿ���඼λ�ڸ������ռ�֮�£����趨sf�����ռ�Ļ�����Ӧ�ĺ���ǰ��Ҫ������������������� sf::VideoMode(width* GRIDSIZE, height* GRIDSIZE)
using namespace std;
class LEI
{
public:
	int mState;//�׵�״̬
	int mStateBackUp;//����״̬
	//bool float_state;  // whether mouse moved on
	int backup_for_moveon;
	bool onclick;  
	bool isPress;//���Ƿ񱻰���
	bool isPressBackUp;//���Ƿ񱻰���
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
	LEI mGameData[LVL3_HEIGHT][LVL3_WIDTH];//------->20*20����
	bool isGameBegin;//------->��Ϸ�Ƿ�ʼ
	int isGameOverState;//------->��Ϸ������״̬
	Vector2i mCornPoint;//��Ϸ����λ��
	int gridSize;//���С��15��
	int imgBGno, imgSkinNo;
	bool testMode;
	Texture tBackground, tTiles, tButtons, tNum, tTimer, tCounter, tGameOver;		//�����������
	Sprite	sBackground, sTiles, sButtons, sNum, sTimer, sCounter, sGameOver;		//�����������
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
	void MineSet(int Py, int Px);//����

	void Input();
	void RButtonDown(Vector2i mPoint);//------->����һ�
	void LButtonDblClk(Vector2i mPoint);//------->������һ��
	void LButtonDown(Vector2i mPoint);//------->����������
	void MouseMove(Vector2i mPoint);

	void NullClick(int j, int i);//���ҿտ�

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

