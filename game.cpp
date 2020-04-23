#include "game.h"
/**
 * change string to lpcwstr
 */
LPCWSTR string_To_LPCWSTR(string _string) {
	size_t origsize = _string.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* _LPCWSTR = (wchar_t*)malloc(sizeof(wchar_t) * (_string.length() - 1));
	mbstowcs_s(&convertedChars, _LPCWSTR, origsize, _string.c_str(), _TRUNCATE);
	return _LPCWSTR;
}
void cout_out() {

	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
	cout << "yeyeyeyeyeyeyeyeyeyey?????????" << endl;
}
Game::Game()
{
	/*	if(w>= LVL3_WIDTH)
			Window_width = w * GRIDSIZE;
		else
			Window_width = LVL3_WIDTH * GRIDSIZE;
		if(h >= LVL3_HEIGHT)
			Window_height = h * GRIDSIZE;
		else
			Window_height = LVL3_HEIGHT * GRIDSIZE;*/

	Window_width = 860;
	Window_height = 600;
	testMode = false;
	gameLvL = 3;
	imgBGno = 1;
	imgSkinNo = 1;
	window.create(sf::VideoMode(Window_width, Window_height), L"MineSweeper by ZXX");
}


Game::~Game()
{
}

void Game::Initial()
{
	window.setFramerateLimit(60);	//ÿ������Ŀ��֡��

	gridSize = GRIDSIZE;//---->�����λ�õĿ�Ĵ�С

	switch (gameLvL)
	{
	case 1:
		stageWidth = LVL1_WIDTH;
		stageHeight = LVL1_HEIGHT;
		mMineNum = LVL1_NUM;//��ʼ���׵ĸ���
		break;
	case 2:
		stageWidth = LVL2_WIDTH;
		stageHeight = LVL2_HEIGHT;
		mMineNum = LVL2_NUM;//��ʼ���׵ĸ���
		break;
	case 3:
		stageWidth = LVL3_WIDTH;
		stageHeight = LVL3_HEIGHT;
		mMineNum = LVL3_NUM;//��ʼ���׵ĸ���
		break;
	default:
		break;
	}
	change_time_number = 1;     // start interface variable to constraint grid animator
	gameOver = false;
	gameQuit = false;
	isGameOverState = ncNO;
	mFlagCalc = 0;//��ʼ�����ӵ�����
	isGameBegin = false;//��ʼ����Ϸ�Ƿ�ʼ
	mTime = 0;

	mCornPoint.x = (Window_width - stageWidth * GRIDSIZE) / 2;
	mCornPoint.y = (Window_height - stageHeight * GRIDSIZE) / 2;
	IniData();//��ʼ������
	LoadMediaData();//�����ز�
}
void Game::Initial_Load_Sound(Sound& sound, SoundBuffer& soundbuffer, string filename) {
	if (!soundbuffer.loadFromFile(filename)) {
		int result = MessageBox(NULL, string_To_LPCWSTR("Invalid Path , audio is missing : " + filename), TEXT("Error ! Failed to load !"), MB_RETRYCANCEL);
		switch (result) {
		case IDRETRY:
			return Initial_Load_Sound(sound, soundbuffer, filename);
		case IDCANCEL:
			exit(0);
		}
	}
	else {
		cout << "��Ƶ���سɹ�" << endl;
		sound.setVolume(50);
		cout << "��Ƶ���뻺��ɹ�" << endl;
		sound.setBuffer(soundbuffer);
	}
}
void Game::Initial_Load_Music(Music& music, string filename) {
	if (!music.openFromFile(filename)) {
		int result = MessageBox(NULL, string_To_LPCWSTR("Invalid Path , audio is missing : " + filename), TEXT("Error ! Failed to load !"), MB_RETRYCANCEL);
		switch (result) {
		case IDRETRY:
			return Initial_Load_Music(music, filename);
		case IDCANCEL:
			exit(0);
		}
	}
	else {
		cout << "��Ƶ���سɹ�" << endl;
		music.setVolume(20);
		music.play();
		music.setLoop(true);
	}
}
void Game::Initial_Load_Image(Texture& texture, Sprite& sprite, string filename, float originX, float originY, float factorX, float factorY) {
	if (!texture.loadFromFile(filename)) {
		int result = MessageBox(NULL, string_To_LPCWSTR("Invalid Path , image is missing : " + filename), TEXT("Error ! Failed to load !"), MB_RETRYCANCEL);
		switch (result) {
		case IDRETRY:
			return Initial_Load_Image(texture, sprite, filename, originX, originY, factorX, factorY);
		case IDCANCEL:
			exit(0);
		}
	}
	else {
		cout << "��ͼ���سɹ�" << endl;
		sprite.setTexture(texture);
		sprite.setOrigin(originX, originY);
		//sprite.setScale(factorX, factorY);
	}
}

void Game::LoadMediaData()
{
	stringstream ss;
	ss << "data/images/BK0" << imgBGno << ".jpg";
	Initial_Load_Image(tBackground, sBackground, ss.str(), 0, 0, 1, 1);
	ss.str("");           // clear ss
	//ss << "data/test/blue_whole0" << image_skin_No << ".png";
	ss << "data/images/Game" << imgSkinNo << ".jpg";
	Initial_Load_Image(tTiles, sTiles, ss.str(), 0, 0, 1, 1);
	//Initial_Load_Image(texture_tile, sprite_tile,"data/test/blue_whole.png", 0, 0, 1, 1);
	Initial_Load_Image(tNum, sNum, "data/images/num.jpg", 0, 0, 1, 1);
	Initial_Load_Image(tTimer, sTimer, "data/images/jishiqi.jpg", 0, 0, 1, 1);
	Initial_Load_Image(tCounter, sCounter, "data/images/jishuqi.jpg", 0, 0, 1, 1);
	Initial_Load_Image(tButtons, sButtons, "data/images/button.jpg", 0, 0, 1, 1);
	Initial_Load_Image(tGameOver, sGameOver, "data/images/gameover.jpg", 0, 0, 1, 1);

}
void Game::IniData()
{
	int i, j;

	for (j = 0; j < stageHeight; j++)//���п���Ϊ����δ���
		for (i = 0; i < stageWidth; i++)
		{
			mGameData[j][i].mState = ncUNDOWN;
			mGameData[j][i].isPress = false;
			mGameData[j][i].onclick = false;
		}
}
void Game::MineSet(int Py, int Px)//����
{
	int mCount, i, j, k, l;
	mCount = 0;

	//srand(time(NULL));               //�õ�ǰϵͳʱ����Ϊ�����������������
	for (j = 0; j < stageHeight; j++)//���п���Ϊ����δ���
		for (i = 0; i < stageWidth; i++)
		{
			mGameData[j][i].mStateBackUp = 0;
			mGameData[j][i].backup_for_moveon = 0;
		}
	//�������
	do {//��һ������ͬһ��λ�ã���������������������
		k = rand() % stageHeight;//���������
		l = rand() % stageWidth;
		if (((k -Py)* (k - Py)+ (l - Px)* (l - Px))<=2)
		//if (k>=Py-1&&k<=Py+1&&1>=Px-1&&1<=Px-1)
			continue;//���������Ϊ��ǰ��һ�ε����λ�ã�����������
		if (mGameData[k][l].mState == ncUNDOWN)
		{
			mGameData[k][l].mState = ncMINE;
			mGameData[k][l].mStateBackUp = ncMINE;//����״̬
			mCount++;
		}
		else if (mGameData[k][l].mState == ncFLAG || mGameData[k][l].mState == ncQ) {
			mGameData[k][l].mStateBackUp = ncMINE;//����״̬
			mCount++;
		}
	} while (mCount != mMineNum);

	//����ֵ	
	for (i = 0; i < stageHeight; i++)
		for (j = 0; j < stageWidth; j++)
		{
			if (mGameData[i][j].mState != ncMINE &&!(mGameData[i][j].mStateBackUp == ncMINE&& mGameData[i][j].mState == ncQ || mGameData[i][j].mState == ncFLAG))
			{
				mCount = 0;
				for (k = i - 1; k < i + 2; k++)
					for (l = j - 1; l < j + 2; l++)
						if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth)
						{
							if (mGameData[k][l].mState == ncMINE)
								mCount++;
						}//����(i,j)��Χ�׵���Ŀ
				if (mGameData[i][j].mState == ncFLAG || mGameData[i][j].mState == ncQ) {
					int temp = mGameData[i][j].mState;
					mGameData[i][j].mState = mGameData[i][j].mStateBackUp;
					mGameData[i][j].mStateBackUp = temp;
				}
				switch (mCount)//����״̬
				{
				case 0:
					mGameData[i][j].mState = ncNULL;
					break;
				case 1:
					mGameData[i][j].mState = ncONE;
					break;
				case 2:
					mGameData[i][j].mState = ncTWO;
					break;
				case 3:
					mGameData[i][j].mState = ncTHREE;
					break;
				case 4:
					mGameData[i][j].mState = ncFOUR;
					break;
				case 5:
					mGameData[i][j].mState = ncFIVE;
					break;
				case 6:
					mGameData[i][j].mState = ncSIX;
					break;
				case 7:
					mGameData[i][j].mState = ncSEVEN;
					break;
				case 8:
					mGameData[i][j].mState = ncEIGHT;
					break;
				}
				if (mGameData[i][j].mStateBackUp == ncFLAG || mGameData[i][j].mStateBackUp == ncQ) {
					int temp = mGameData[i][j].mState;
					mGameData[i][j].mState = mGameData[i][j].mStateBackUp;
					mGameData[i][j].mStateBackUp = temp;
				}
			}
		}
}
void Game::Input()
{
	sf::Event event;//event types ����Window��Keyboard��Mouse��Joystick��4����Ϣ
					//ͨ��  bool Window :: pollEvent��sf :: Event��event�� �Ӵ���˳��ѯ�ʣ� polled ���¼��� 
					//�����һ���¼��ȴ������ú���������true�������¼���������䣨filled���¼����ݡ� 
					//������ǣ���ú�������false�� ͬ����Ҫ����Ҫע�⣬һ�ο����ж���¼�; ������Ǳ���ȷ������ÿ�����ܵ��¼��� 
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();		//���ڿ����ƶ���������С����С�����������Ҫ�رգ���Ҫ�Լ�ȥ����close()����
			gameQuit = true;
		}

		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			window.close();		//���ڿ����ƶ���������С����С�����������Ҫ�رգ���Ҫ�Լ�ȥ����close()����
			gameQuit = true;
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			mouse_left_pressed = true;
			if (isGameOverState == ncNO)
			{
				if (mouseClickTimer.getElapsedTime().asMilliseconds() > 500) {
					LButtonDown(Mouse::getPosition(window));	//�����ε���ļ������600���룬���ж�Ϊ��굥��
				}
				else {
					LButtonDblClk(Mouse::getPosition(window));	//�����ε���ļ��С��600���룬���ж�Ϊ���˫��
				}
				//std::cout << "Elapsed time since previous frame(microseconds): " << clock.getElapsedTime().asMilliseconds() << std::endl;//
			}
		}
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			mouse_left_pressed = false;
			if (isGameOverState == ncNO)
			{
				mouseClickTimer.restart();//SFML��clock�����������getElapsedTime()��restart()�����򵥣�
				//��ť�ж�
				if (isGameBegin == false)
				{
					if (ButtonRectEasy.contains(event.mouseButton.x, event.mouseButton.y))
					{
						gameLvL = 1;
						Initial();//��ʱˢ����̨
					}
					if (ButtonRectNormal.contains(event.mouseButton.x, event.mouseButton.y))
					{
						gameLvL = 2;
						Initial();//��ʱˢ����̨
					}
					if (ButtonRectHard.contains(event.mouseButton.x, event.mouseButton.y))
					{
						gameLvL = 3;
						Initial();//��ʱˢ����̨
					}
				}

			}
			if (ButtonRectBG.contains(event.mouseButton.x, event.mouseButton.y))
			{
				imgBGno++;
				if (imgBGno > 7)//����ͼ������
					imgBGno = 1;
				LoadMediaData();
			}
			if (ButtonRectSkin.contains(event.mouseButton.x, event.mouseButton.y))
			{
				imgSkinNo++;
				if (imgSkinNo > 6)//Ƥ��������
					imgSkinNo = 1;
				LoadMediaData();
			}
			if (ButtonRectRestart.contains(event.mouseButton.x, event.mouseButton.y))
			{
				Initial();
			}
			if (ButtonRectQuit.contains(event.mouseButton.x, event.mouseButton.y))
			{
				window.close();
				gameOver = false;
				gameQuit = true;
			}


		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
		{
			mouse_right_pressed = true;
			if (isGameOverState == ncNO)
				RButtonDown(Mouse::getPosition(window));//------->����һ�
		}
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
		{
			mouse_right_pressed = false;
		}
		// about mouse move
		if (event.type == sf::Event::MouseMoved)
		{
			MouseMove(Mouse::getPosition(window));
		}
		if (event.type == sf::Event::KeyReleased && event.key.code == Keyboard::T) {
			if (testMode == false) {
				testMode = true;
				for (int i = 0; i < stageHeight; i++) {
					for (int j = 0; j < stageWidth; j++) {
						mGameData[i][j].isPressBackUp = mGameData[i][j].isPress;
						mGameData[i][j].isPress = true;
					}
				}
			}
			else {
				testMode = false;
				for (int i = 0; i < stageHeight; i++) {
					for (int j = 0; j < stageWidth; j++) {
						mGameData[i][j].isPress = mGameData[i][j].isPressBackUp;
					}
				}
			}
		}
	}
}
void Game::MouseMove(Vector2i mPoint)//------->mouse move
{
	int i, j;
	i = (mPoint.x - mCornPoint.x) / gridSize;
	j = (mPoint.y - mCornPoint.y) / gridSize;
	cout << i << "&&" << j << endl;

	// change state out of i&j in array
	for (int line = 0; line < stageHeight; line++)//���п���Ϊ����δ���
	{
		for (int row = 0; row < stageWidth; row++)
		{
			if (mGameData[line][row].mState==ncX)
			{
				mGameData[line][row].mState = mGameData[line][row].backup_for_moveon;
			}
		}
	}
	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)   //����������ʵ�ڷ�Χ��
	{
		cout << "mGameData["<<j<<"]["<<i<<"].mState===="<< mGameData[j][i].mState << endl;
		cout << "mGameData["<<j<<"]["<<i<<"].mStateBackUp===="<< mGameData[j][i].mStateBackUp << endl;
		if (mGameData[j][i].isPress == false&& mGameData[j][i].mState!=ncX)
		{
			cout << "yes!" << endl;
			mGameData[j][i].backup_for_moveon = mGameData[j][i].mState;
			mGameData[j][i].mState = ncX;
			
		}
	}
}
void Game::RButtonDown(Vector2i mPoint)//------->����һ�
{
	int i, j;
	i = (mPoint.x - mCornPoint.x) / gridSize;
	j = (mPoint.y - mCornPoint.y) / gridSize;
	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)//���������ڷ�Χ��
	{
		if (mGameData[j][i].isPress == false)
		{
			mGameData[j][i].isPress = true;
			mGameData[j][i].mStateBackUp = mGameData[j][i].mState;
			mGameData[j][i].mState = ncFLAG;
			mFlagCalc++;
		}
		else
		{
			if (mGameData[j][i].mState == ncFLAG)
			{
				mGameData[j][i].isPress = true;
				mGameData[j][i].mState = ncQ;
				mFlagCalc--;
			}
			else if (mGameData[j][i].mState == ncQ)
			{
				mGameData[j][i].isPress = false;
				mGameData[j][i].mState = mGameData[j][i].mStateBackUp;
			}
			else if (mouse_left_pressed && mouse_right_pressed) {

				for (int k = j - 1; k < j + 2; k++)
					for (int l = i - 1; l < i + 2; l++)//������Χ8������{
					{
						if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth && !(k == j && l == i) && mGameData[k][l].isPress == false)
						{

							mGameData[k][l].backup_for_moveon = mGameData[k][l].mState;
							mGameData[k][l].mState = ncNULL;
							mGameData[k][l].onclick = true;
						}
					}
			}
		}
	}
}

void Game::LButtonDown(Vector2i mPoint)//------->������1��
{
	int i, j;
	i = (mPoint.x - mCornPoint.x) / gridSize;//��ȡ��굱ǰ����Ŀ��λ��
	j = (mPoint.y - mCornPoint.y) / gridSize;

	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)//���������ڷ�Χ��
	{
		if (isGameBegin == false)//�����Ϸδ��ʼ
		{
			isGameBegin = true;//��Ϸ��ʼ
			gameClock.restart();
			MineSet(j, i);//���֮�����������
		}
		if (mGameData[j][i].mState != ncFLAG)//���״̬��������
		{
			if (mGameData[j][i].isPress == false)
			{
				mGameData[j][i].isPress = true;//��ǰ�鱻���
				if (mGameData[j][i].mState == ncMINE || mGameData[j][i].mStateBackUp == ncMINE)//���Ϊ��
				{
					//gameOver = true;
					//MessageBox(NULL, TEXT("Game Over!"), NULL, MB_ICONWARNING | MB_YESNO);
					isGameBegin = false;
					isGameOverState = ncLOSE;
					mGameData[j][i].mState = ncBOMBING;
					unCover();
				}
			}
			else if (mouse_left_pressed && mouse_right_pressed) {

				for (int k = j - 1; k < j + 2; k++)
					for (int l = i - 1; l < i + 2; l++)//������Χ8������{
					{
						if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth &&!( k==j && l==i)&& mGameData[k][l].isPress==false)
						{

							mGameData[k][l].backup_for_moveon = mGameData[k][l].mState;
							mGameData[k][l].mState = ncNULL;
							mGameData[k][l].onclick = true;
						}
					}
			}
		}

		if (mGameData[j][i].mState == ncNULL)//�����ǰ����Ŀ��״̬Ϊ��
			NullClick(j, i);//����δ������Ŀտ�
	}
}
void Game::LButtonDblClk(Vector2i mPoint)//------->������2��
{
	int i, j, k, l, lvl;

	i = (mPoint.x - mCornPoint.x) / gridSize;
	j = (mPoint.y - mCornPoint.y) / gridSize;

	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)//���������ڷ�Χ��
	{
		if (mGameData[j][i].isPress == true)//����ѱ����
		{
			int flag_count=0, mine_count=0;
			for (k = j - 1; k < j + 2; k++)
				for (l = i - 1; l < i + 2; l++)//������Χ8������
					if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth &&!(k == j && l == i) && (mGameData[k][l].isPress==false|| mGameData[k][l].mState==ncFLAG))
					{
						if (mGameData[k][l].mState == ncFLAG) flag_count++;
						if (mGameData[k][l].backup_for_moveon == ncMINE) mine_count++;
						if (mGameData[k][l].mState == ncMINE) mine_count++;
					}
			cout << mine_count << "||" << flag_count << endl;
			if (mine_count <= flag_count) {
				if (mGameData[j][i].mState != ncFLAG)//�����ǰ�鲻������
					for (k = j - 1; k < j + 2; k++)
						for (l = i - 1; l < i + 2; l++)//������Χ8������
							if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth)
							{
								if (mGameData[k][l].mState == ncFLAG)//���״̬������
								{
									if (mGameData[k][l].backup_for_moveon != ncMINE) //���ԭ��״̬������
									{
										//gameOver = true;
										//MessageBox(NULL, TEXT("Game Over!"), NULL, MB_ICONINFORMATION | MB_YESNO);
										//cout << "bug is here???????" << endl;
										//cout << "mGameData[" << k << "][" << l << "].mStateBackUp" << mGameData[k][l].mStateBackUp << endl;;
										isGameOverState = ncLOSE;
										isGameBegin = false;
										//mGameData[j][i].mState = ncBOMBING;
										unCover();
									}

								}
								else {//���״̬��������
									if (mGameData[k][l].isPress == false)
									{
										mGameData[k][l].isPress = true;
										if (mGameData[k][l].mState == ncMINE)//���Ϊ��
										{
											//gameOver = true;
											//MessageBox(NULL, TEXT("Game Over!"), NULL, MB_ICONWARNING | MB_YESNO);
											isGameBegin = false;
											isGameOverState = ncLOSE;
											mGameData[k][l].mState = ncBOMBING;
											unCover();
										}
										if (mGameData[k][l].mState == ncNULL)//���Ϊ�ռ������ҿտ�						
											NullClick(k, l);
									}
								}
							}

			}
		}
	}
}
void Game::NullClick(int j, int i)//���ҿտ�
{
	int k, l;
	for (k = j - 1; k < j + 2; k++)
		for (l = i - 1; l < i + 2; l++)
			if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth)
			{
				if (mGameData[k][l].isPress == false)
				{
					mGameData[k][l].isPress = true; //��ʾΪ�ѵ��
					if (mGameData[k][l].mState == ncNULL) {//���״̬Ϊ��
						NullClick(k, l);//��������ҿտ�
					}
				}
			}
}

void Game::Logic()
{
	Logic_Grid_officialize();
	isWin();
}
void Game::Logic_Grid_officialize() {
	if ((mouse_right_pressed==false)||(mouse_left_pressed==false))
	{
		int i, j;
		for (j = 0; j < stageHeight; j++)//���п���Ϊ����δ���
			for (i = 0; i < stageWidth; i++)
			{
				if ((mGameData[j][i].isPress == false) && (mGameData[j][i].onclick == true)) {
					mGameData[j][i].onclick = false;
					mGameData[j][i].mState = mGameData[j][i].backup_for_moveon;
				}
			}
	}
}
void Game::unCover()
{
	int i, j;

	for (j = 0; j < stageHeight; j++)//���п���Ϊ����δ���
		for (i = 0; i < stageWidth; i++)
		{
			if (mGameData[j][i].isPress == false)
				if (mGameData[j][i].mState == ncMINE)
				{
					mGameData[j][i].isPress = true;
					mGameData[j][i].mState = ncUNFOUND;
				}
		}
}
void Game::isWin()
{
	int i, j, c = 0;
	if (mFlagCalc == mMineNum)//�жϲ���������ǲ��Ƕ�����
	{
		for (i = 0; i < stageWidth; i++)
			for (j = 0; j < stageHeight; j++)
			{
				if (mGameData[j][i].mState == ncFLAG)
					if (mGameData[j][i].mStateBackUp == ncMINE)
						c++;
			}
	}
	else {//�жϲ��ʣ�µĿ��ǲ��Ƕ�����
		for (i = 0; i < stageWidth; i++)
			for (j = 0; j < stageHeight; j++)
			{
				if (mGameData[j][i].isPress == false || mGameData[j][i].mState == ncFLAG) {
					c++;
				}
			}

	}
	if (c == mMineNum)//����������Ӷ����ף���Ϸ����
	{
		isGameBegin = false;
		//gameOver = true;
		//MessageBox(NULL, TEXT("You Win!"), NULL, MB_USERICON | MB_YESNO);
		isGameOverState = ncWIN;
	}
}

void Game::Draw()
{
	//window.clear(Color::Color(255, 0, 255, 255));	//����
	window.clear();	//����
	//Prompt_info(width*GRIDSIZE + GRIDSIZE, GRIDSIZE);

	//���Ʊ���
	sBackground.setPosition(0, 0);
	window.draw(sBackground);
	//������̨
	DrawGrid();
	DrawButton();
	DrawTimer();
	DrawScore();
	if (isGameOverState)
		DrawGameEnd();
	window.display();				//����ʾ�����������ݣ���ʾ����Ļ�ϡ�SFML���õ���˫�������
}

void Game::DrawGrid()
{
	int i, j;
	for (int j = 0; j < stageHeight; j++)
		for (int i = 0; i < stageWidth; i++)
		{
			if ((i + j) < change_time_number)
			{
				if (mGameData[j][i].isPress == true)
				{
					sTiles.setTextureRect(IntRect(mGameData[j][i].mState * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
					sTiles.setPosition(mCornPoint.x + i * GRIDSIZE, mCornPoint.y + j * GRIDSIZE);
				}
				else
				{
					if (mGameData[j][i].mState==ncX)  // draw bright grid
					{
						sTiles.setTextureRect(IntRect(ncX * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
						sTiles.setPosition(mCornPoint.x + i * GRIDSIZE, mCornPoint.y + j * GRIDSIZE);
					}
					else if (mGameData[j][i].onclick == true && mouse_left_pressed && mouse_right_pressed)
					{
						sTiles.setTextureRect(IntRect(ncNULL * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
						sTiles.setPosition(mCornPoint.x + i * GRIDSIZE, mCornPoint.y + j * GRIDSIZE);
					}
					else // draw back grid
					{
						sTiles.setTextureRect(IntRect(ncUNDOWN * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
						sTiles.setPosition(mCornPoint.x + i * GRIDSIZE, mCornPoint.y + j * GRIDSIZE);
					}
				}
			}
			if (change_time_number == counter[i][j]) {
				sTiles.setTextureRect(IntRect(ncUNDOWN * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
				sTiles.setPosition(mCornPoint.x + i * GRIDSIZE, mCornPoint.y + j * GRIDSIZE);
			}
			window.draw(sTiles);
		}
	if (change_time_number < (stageHeight + stageWidth - 1)) { change_time_number++; }
}
void Game::DrawButton()
{
	Vector2i LeftCorner;
	int ButtonWidth = 60;
	int ButtonHeight = 36;
	int detaX;
	detaX = (Window_width - ButtonWidth * 7) / 8;//�ȷֿ��
	LeftCorner.y = Window_height - GRIDSIZE * 3;//ָ���߶�

	//ButtonRectEasy
	LeftCorner.x = detaX;
	sButtons.setTextureRect(IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);							//	���ð�ť��λ������
	ButtonRectEasy.left = LeftCorner.x;											//��¼��ť��λ������
	ButtonRectEasy.top = LeftCorner.y;
	ButtonRectEasy.width = ButtonWidth;
	ButtonRectEasy.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectNormal;
	LeftCorner.x = detaX * 2 + ButtonWidth;
	sButtons.setTextureRect(IntRect(1 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);							//	���ð�ť��λ������
	ButtonRectNormal.left = LeftCorner.x;											//��¼��ť��λ������
	ButtonRectNormal.top = LeftCorner.y;
	ButtonRectNormal.width = ButtonWidth;
	ButtonRectNormal.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectHard;
	LeftCorner.x = detaX * 3 + ButtonWidth * 2;
	sButtons.setTextureRect(IntRect(2 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);							//	���ð�ť��λ������
	ButtonRectHard.left = LeftCorner.x;											//��¼��ť��λ������
	ButtonRectHard.top = LeftCorner.y;
	ButtonRectHard.width = ButtonWidth;
	ButtonRectHard.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectSkin
	LeftCorner.x = detaX * 4 + ButtonWidth * 3;
	sButtons.setTextureRect(IntRect(3 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);							//	���ð�ť��λ������
	ButtonRectSkin.left = LeftCorner.x;											//��¼��ť��λ������
	ButtonRectSkin.top = LeftCorner.y;
	ButtonRectSkin.width = ButtonWidth;
	ButtonRectSkin.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectBG
	LeftCorner.x = detaX * 5 + ButtonWidth * 4;
	sButtons.setTextureRect(IntRect(4 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);							//	���ð�ť��λ������
	ButtonRectBG.left = LeftCorner.x;											//��¼��ť��λ������
	ButtonRectBG.top = LeftCorner.y;
	ButtonRectBG.width = ButtonWidth;
	ButtonRectBG.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectRestart;
	LeftCorner.x = detaX * 6 + ButtonWidth * 5;
	sButtons.setTextureRect(IntRect(5 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);							//	���ð�ť��λ������
	ButtonRectRestart.left = LeftCorner.x;											//��¼��ť��λ������
	ButtonRectRestart.top = LeftCorner.y;
	ButtonRectRestart.width = ButtonWidth;
	ButtonRectRestart.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectQuit;
	LeftCorner.x = detaX * 7 + ButtonWidth * 6;
	sButtons.setTextureRect(IntRect(6 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);							//	���ð�ť��λ������
	ButtonRectQuit.left = LeftCorner.x;											//��¼��ť��λ������
	ButtonRectQuit.top = LeftCorner.y;
	ButtonRectQuit.width = ButtonWidth;
	ButtonRectQuit.height = ButtonHeight;
	window.draw(sButtons);
	
	
}
void Game::DrawScore()
{
	Vector2i LeftCorner;
	LeftCorner.x = Window_width - sCounter.getLocalBounds().width * 1.25;
	LeftCorner.y = sCounter.getLocalBounds().height * 0.5;
	sCounter.setPosition(LeftCorner.x, LeftCorner.y);	//�������������ͼλ��
	window.draw(sCounter);

	int NumSize = sNum.getLocalBounds().height;
	LeftCorner.x = LeftCorner.x + sCounter.getLocalBounds().width - NumSize;
	LeftCorner.y = LeftCorner.y + sCounter.getLocalBounds().height * 0.5 - NumSize * 0.5;

	int mScore = abs(mMineNum - mFlagCalc);
	//���Ƹ�λ��������
	int a = mScore % 10;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));//������ȡ��������
	sNum.setPosition(LeftCorner.x, LeftCorner.y);//�ں�λ��
	window.draw(sNum);
	//����ʮλ��������
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSize;
	if (mMineNum - mFlagCalc >= 0 || a != 0) sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));//������ȡ��������
	else	sNum.setTextureRect(IntRect(10 * NumSize, 0, NumSize, NumSize));//������ȡ��������
	sNum.setPosition(LeftCorner.x, LeftCorner.y);//�ں�λ��
	window.draw(sNum);
	//���ư�λ��������
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSize;
	if (mMineNum - mFlagCalc >= 0 || a != 0)	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));//������ȡ��������
	else	sNum.setTextureRect(IntRect(10 * NumSize, 0, NumSize, NumSize));//������ȡ��������
	sNum.setPosition(LeftCorner.x, LeftCorner.y);//�ں�λ��
	window.draw(sNum);
}
void Game::DrawTimer()
{
	Vector2i LeftCorner;
	LeftCorner.x = sTimer.getLocalBounds().width * 0.25;
	LeftCorner.y = sTimer.getLocalBounds().height * 0.5;
	sTimer.setPosition(LeftCorner.x, LeftCorner.y);	//�������������ͼλ��
	window.draw(sTimer);

	if (isGameBegin)
		mTime = gameClock.getElapsedTime().asSeconds();

	int mScore = mTime;
	if (mScore > 999)
		mScore = 999;

	int NumSize = sNum.getLocalBounds().height;
	LeftCorner.x = LeftCorner.x + sTimer.getLocalBounds().width - NumSize * 1.5;
	LeftCorner.y = LeftCorner.y + sTimer.getLocalBounds().height * 0.5 - NumSize * 0.5;

	//���Ƹ�λ��������
	int a = mScore % 10;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));//������ȡ��������
	sNum.setPosition(LeftCorner.x, LeftCorner.y);//�ں�λ��
	window.draw(sNum);
	//����ʮλ��������
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSize;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));//������ȡ��������
	sNum.setPosition(LeftCorner.x, LeftCorner.y);//�ں�λ��
	window.draw(sNum);
	//���ư�λ��������
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSize;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));//������ȡ��������
	sNum.setPosition(LeftCorner.x, LeftCorner.y);//�ں�λ��
	window.draw(sNum);

}
void Game::DrawGameEnd()
{
	Vector2i LeftCorner;
	int ButtonWidth = 200;//sGameOver.getLocalBounds().width/2;
	int ButtonHeight = sGameOver.getLocalBounds().height;
	LeftCorner.x = (Window_width - ButtonWidth) / 2;//ָ����������
	LeftCorner.y = (Window_height - ButtonHeight) / 2;//ָ����������

	sGameOver.setPosition(LeftCorner.x, LeftCorner.y);							//	���ð�ť��λ������

	if (isGameOverState == ncWIN)
	{
		sGameOver.setTextureRect(IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
	}
	if (isGameOverState == ncLOSE)
	{
		sGameOver.setTextureRect(IntRect(1 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
	}
	window.draw(sGameOver);
}
void Game::Run()
{
	do {

		Initial();

		while (window.isOpen() && gameOver == false)
		{
			Input();

			Logic();

			Draw();
		}


	} while (!gameQuit);
}