#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<ctime>
#include<SFML/Audio.hpp>
#include<iostream>
#include <vector>
using namespace sf;
using namespace std;
int z = 0;

// What shuold i do 
/*
1 - make new animation for sonic (done)
2 - make dynamic jump 
3 - add UI (done)
4 - add the map (done)
5 - coin and enmies 
6 - save progrss , add Resume
7 - Health and score 
8 - end gui and next level 
9 - new level
10- add new character 
*/
struct Player {
private:
	short width = 90, hight = 110  , idle_animation_x = 85 , walk_animation_x = 87;
	short limit_X = 0, limit_Y = 0  , dimensions_for_jump = 78 ;
	short idle_animation_y = 0, speed_animation_y = 2, walk_animation_y = 1,x = 0 , time1 = 0;
	float  jump_animation_y = 4.3f ;

public:
	Texture player_spread_sheet;
	Sprite player;
	float speed_x = 5.f, speed_y = 5.f;
	Player() {};
	void walk_animation(RenderWindow& window) {
		speed_x = 3.f;
		if (Keyboard::isKeyPressed(Keyboard::A))
			player.setTextureRect(IntRect(walk_animation_x * x, hight * walk_animation_y, -walk_animation_x, hight));
		else if (Keyboard::isKeyPressed(Keyboard::D))
		player.setTextureRect(IntRect(walk_animation_x * x, hight * walk_animation_y, walk_animation_x, hight));
		time1++;
		if (time1 > 3)
		{
			++x %= 9;
			time1 = 0;
		}
	}
	void Idle_animation(RenderWindow& window) {
			player.setTextureRect(IntRect(idle_animation_x * x, hight * idle_animation_y, idle_animation_x, hight));
			time1++;
			if (time1 > 10)
			{
				++x %= 6;
				time1 = 0;
			}
	}
	void speed_animation(RenderWindow& window) {
		speed_x = 6.f;
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			player.setTextureRect(IntRect(width * x, hight * speed_animation_y, -width, hight));
		}
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			player.setTextureRect(IntRect(width * x, hight * speed_animation_y, width, hight));
		}	
		time1++;
		if (time1 > 10)
		{
			++x %= 9;
			time1 = 0;
		}
	}
	void jump_animation(RenderWindow& window) {
		player.setTextureRect(IntRect(dimensions_for_jump * x, dimensions_for_jump * jump_animation_y, dimensions_for_jump, dimensions_for_jump));
		++x %= 6;
	}
	void display(RenderWindow& window) {
		window.draw(player);
	}
	void move(RenderWindow & window, float& game_speed_x, float& game_speed_y) {
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			player.move(-speed_x, 0);
		}

		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			player.move(speed_x, 0);
		}
		// this to update the whole game speed
		game_speed_x = speed_x;
		game_speed_y = speed_y;
	}
};
void sonic_animation(RenderWindow& window, Player& sonic, float& x, float pos);
void sonic_intilization(RenderWindow& window, Player& sonic );
void jump(Player& sonic, float frame, float max_hight, float& x, float pos);
void UI(RenderWindow& window, Text& play, Text& exit, Sprite& mouse, RectangleShape& background, int& click, int& time1, int& time2, int & pos);
void UI_intializtion(RenderWindow& window, Text& play, Text& exit, Texture & Mouse, Sprite& mouse, Texture & back, RectangleShape& backgroundForUI, Font& font);
void map_intilization
(RenderWindow& window, Sprite& flag, Sprite  Catus[5], Sprite spritesbackground[10], Sprite spritesground[20], Sprite spritesstblock[5], Sprite spritesndblock[5], Texture& Flag, Texture& Ground,
	Sprite& ground, Texture& Ndblock, Sprite& ndblock, Texture& Stblock, Sprite& stblock, Texture& Cactus, Sprite& cactus, Texture& Background, Sprite& background);
void GameWorld(RenderWindow& window, Sprite& flag, Sprite Catus[5], Sprite Block1[10], Sprite Block2[10], Sprite backgroundArr[10], Sprite& ground, Sprite& background);
void CameraView(RenderWindow& window, View& camera, Player& sonic, Text& text0, Text& text02, Text& text03 ,float & x);
void coinDraw(RenderWindow& window, View& camera, vector <Sprite>& coins, Sprite& coin, Player& sonic);
int main (void){

	Player sonic;
	RenderWindow window(VideoMode(1200, 800), "SONIC");
	window.setFramerateLimit(60);

	View camera;
	camera.setCenter(Vector2f(350.f, 200.f));
	camera.setSize(Vector2f(800.f, 400.f));

	Font font;
	font.loadFromFile("Font/font.ttf");
	Text play , exit;
	Texture Mouse;
	RectangleShape backgroundForUI;
	Texture back;
	Sprite mouse;

	// GAME WORLD
	Sprite flag , Catus[5] , Block1[10],Block2[10],backgroundArr[10],Ground[20],ground, background ;
	Texture GroundT, flagT, ndb, stb, catus , backgroundT;
	Sprite Ndb, Stb, catSprite;
	map_intilization(window, flag, Catus, backgroundArr, Ground, Block1,
		Block2,flagT,GroundT,ground,ndb,Ndb,stb,Stb,catus,catSprite, backgroundT,background);
	// coin and Enmies

	Sprite coin;
	Texture coinT;
	coinT.loadFromFile("Tex/coins1.PNG");
	coin.setTexture(coinT);
	coin.setPosition(300, 400);
	coin.setScale(0.2f, 0.2f);
	coin.setTextureRect(IntRect(128 * 0, 0 * 128, 128, 128));
	vector<Sprite>coins;

	// GUI
	UI_intializtion(window, play, exit, Mouse, mouse, back, backgroundForUI, font);
	float x = 0 , pos1 = sonic.player.getPosition().y;
	int time1 = 0, time2= 0 , pos = 0;
	int count = 0;
	sonic_intilization(window, sonic);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}
		window.clear(Color::Black);
		if (count == 0) {
			UI(window, play, exit, mouse, backgroundForUI, count, time1, time2,pos);
		}
		else if (count == 1) {

			CameraView(window, camera, sonic, play, exit, play ,x);
			GameWorld(window, flag, Catus, Block1, Block2, backgroundArr, ground, background);
			coinDraw(window, camera, coins, coin, sonic);
			window.draw(coin);
			sonic_animation( window , sonic, x , window.getSize().x/2 );
			sonic.display(window);
		}
		window.display();
	}
}
void sonic_intilization(RenderWindow & window,Player& sonic ){
	sonic.player_spread_sheet.loadFromFile("Tex/sonic.png");
	float x, y;
	sonic.player.setTexture(sonic.player_spread_sheet);
	float speed_x = 0.5f, speed_y = 0.5f;
	sonic.player.scale(0.5f, 0.5f);
	sonic.player.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	cout << sonic.player.getPosition().x << " " << sonic.player.getPosition().y << endl;
}
void sonic_animation(RenderWindow& window, Player& sonic, float& x, float pos) {
	if (Keyboard :: isKeyPressed(Keyboard::LShift) || Keyboard::isKeyPressed(Keyboard::A) ||
	Keyboard::isKeyPressed(Keyboard::D )|| Keyboard::isKeyPressed(Keyboard::Space))
	{
		if (Keyboard::isKeyPressed(Keyboard::LShift))
			sonic.speed_animation(window);
		if (Keyboard::isKeyPressed(Keyboard::D))
			sonic.walk_animation(window);
		if (Keyboard::isKeyPressed(Keyboard::A))
			sonic.walk_animation(window);
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			sonic.jump_animation(window);
			jump(sonic, 5.f, 140, x, pos);
		}
	}
	else sonic.Idle_animation(window);
	float  y = 0, z = 0;
	sonic.move(window, y , z);
	window.draw(sonic.player);
}
/*****************************/
bool isBottom = true , top = false;
/****************************/
void jump(Player & sonic,float frame, float max_hight, float & x , float  pos)
{

	if (isBottom && !top) {
		x += frame;
	}
	if (x >= max_hight) {
		top = true;
		isBottom = false;
	}
	if (!isBottom && top) {
		x -= frame;
	}
	if (x <= 0) {
		isBottom = true, top = false;
	}

}
void UI_intializtion(RenderWindow & window,Text & play, Text & exit, Texture & Mouse,Sprite & mouse, Texture & back, RectangleShape & backgroundForUI, Font & font ) {
	String name1 = "PLAY", name2 = "EXIT";
	Mouse.loadFromFile("Tex/mouse.png");
	mouse.setTexture(Mouse);
	mouse.setScale(0.08f, 0.08f);
	/********/
	play.setFont(font);
	play.setCharacterSize(24);
	play.setFillColor(Color::Black);
	play.setStyle(Text::Bold);
	play.setString("PLAY");
	/*******/
	exit.setFont(font);
	exit.setCharacterSize(24);
	exit.setFillColor(Color::Black);
	exit.setStyle(Text::Bold);
	exit.setString(name2);
	backgroundForUI.setSize(Vector2f((float)window.getSize().x, (float)window.getSize().y));
	back.loadFromFile("Tex/background.jpg");
	backgroundForUI.setTexture(&back);
	play.setPosition(window.getPosition().x / 2 + 100, window.getSize().y / 4.5);
	exit.setPosition(window.getPosition().x / 2 + 100, window.getSize().y - 200);
}
void UI(RenderWindow& window, Text& play, Text& exit, Sprite& mouse, RectangleShape& background, int& click, int& time1, int& time2, int & pos) {
	// draw
	window.draw(background);
	window.draw(mouse);
	window.draw(play);
	window.draw(exit);
    // this two switch between play and exit
	if (time1 < 10)
		time1++;
	if (time2 < 10)
		time2++;
	if (Keyboard::isKeyPressed(Keyboard::Up) && time1 >= 10 || Keyboard::isKeyPressed(Keyboard::Down) && time1 >= 10) {
		pos++;
		time1 = 0;
	}
	if (pos % 2 == 0) {
		play.setFillColor(Color::Red);
		exit.setFillColor(Color::Black);
	}
	if (pos % 2 == 1) {
		play.setFillColor(Color::Black);
		exit.setFillColor(Color::Red);
	}
	if (Keyboard::isKeyPressed(Keyboard::Enter) && pos % 2 == 1 && time2 >= 10) {
		window.close();
		time2 = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Enter) && pos % 2 == 0 && time2 >= 10) {
		click++;
		time2 = 0;
	}
	mouse.setPosition((float)Mouse::getPosition().x, (float)Mouse::getPosition().y);
	if (mouse.getGlobalBounds().intersects(exit.getGlobalBounds())) {
		exit.setFillColor(Color::Red);
		play.setFillColor(Color::Black);
	}
	if (mouse.getGlobalBounds().intersects(play.getGlobalBounds())) {
		play.setFillColor(Color::Red);
		exit.setFillColor(Color::Black);
	}
	if (mouse.getGlobalBounds().intersects(exit.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
		click++;
	}
	if (mouse.getGlobalBounds().intersects(play.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
		window.close();
	}
	window.setMouseCursorVisible(true);
}
void map_intilization
      (RenderWindow& window, Sprite& flag, Sprite  Catus[5], Sprite spritesbackground[10], Sprite spritesground[20],Sprite spritesstblock[5], Sprite spritesndblock[5],Texture& Flag, Texture & Ground,
		                  Sprite &ground,Texture & Ndblock , Sprite & ndblock , Texture & Stblock , Sprite & stblock , Texture & Cactus , Sprite & cactus , Texture & Background , Sprite & background)
{
	//Background for GAME
	Background.loadFromFile("Tex/background.JPEG");
	background.setTexture(Background);
	background.setScale(0.5f, 0.6f);
	background.setPosition(-50.f, 0.f);
	for (int i = 0; i < 10; i++) {
		spritesbackground[i] = background;
		spritesbackground[i].setPosition(-50.f + ((float)i * 565), 0);
	}

	//ground
	Ground.loadFromFile("Tex/ground.PNG");
	ground.setTexture(Ground);
	ground.setScale(0.5f, 0.6f);
	ground.setPosition(-50, 343);
	for (int i = 0; i < 20; i++) {
		spritesground[i] = ground;
		spritesground[i].setPosition(-50 + ((float)i * 410), 343);
	}

	//First Block 
	Stblock.loadFromFile("Tex/firstblock.PNG");
	stblock.setTexture(Stblock);
	stblock.setScale(0.5, 0.5);
	for (int i = 0; i < 5; i++) {
		spritesstblock[i] = stblock;
		spritesstblock[i].setPosition(300 + ((float)i * 1000), 223);
	}

	//second block 
	Ndblock.loadFromFile("Tex/secondblock.PNG");
	ndblock.setTexture(Ndblock);
	ndblock.setScale(0.35f, 0.35f);
	for (int i = 0; i < 5; i++) {
		spritesndblock[i] = ndblock;
		spritesndblock[i].setPosition(850 + ((float)i * 1000), 170);
	}

	//Cactus
	Cactus.loadFromFile("Tex/cactus.PNG");
	cactus.setTexture(Cactus);
	cactus.setScale(0.23f, 0.23f);
	for (int i = 0; i < 5; i++) {
		Catus[i] = cactus;
		Catus[i].setPosition(350 + ((float)i * 1000), 235);
	}
	//Flag
	Flag.loadFromFile("Tex/flag.PNG");
	flag.setTexture(Flag);
	flag.setScale(0.5, 0.5);
	flag.setPosition(5200, 127);

}
bool once2 = true;
void GameWorld(RenderWindow& window, Sprite& flag, Sprite Catus[5], Sprite Block1[10], Sprite Block2[10], Sprite backgroundArr[10], Sprite& ground, Sprite& background) {

	if (once2) {
		for (int i = 0; i < 10; i++) {
			window.draw(backgroundArr[i]);
		}
		window.draw(background);
		window.draw(ground);

		for (int i = 0; i < 5; i++) {
			window.draw(Block1[i]);
		}

		for (int i = 0; i < 5; i++) {
			window.draw(Block2[i]);
		}

		for (int i = 0; i < 5; i++) {
			window.draw(Catus[i]);
		}
		window.draw(flag);
	}
	//once2 = false;
}
void CameraView(RenderWindow& window, View& camera, Player& sonic, Text& text0, Text& text02, Text& text03 ,float & x) {
	window.setView(camera);
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		camera.move(sonic.speed_x, 0.f);
	/*	text0.move(sonic.speed_x, 0.f);
		text02.move(sonic.speed_x, 0.f);
		text03.move(sonic.speed_x, 0.f);*/

	}
	else if (Keyboard::isKeyPressed(Keyboard::A) && camera.getCenter().x *2 >window.getSize().x/2 + 100 ) {
		camera.move(Vector2f(-sonic.speed_x, 0.f));
	/*	text0.move(-sonic.speed_x, 0.f);
		text02.move(-sonic.speed_x, 0.f);
		text03.move(-sonic.speed_x, 0.f);*/
	}
	sonic.player.setOrigin(sonic.player.getGlobalBounds().width, 200 + x);
}
bool once = true;
void coinDraw(RenderWindow & window,View & camera ,vector <Sprite> & coins , Sprite & coin , Player & sonic) {
	if (once)
	for (int i = 0 , k = 0; i < 5200; i += 100,k++) {
		cout << k << endl;
		coins.push_back(coin);
		coins[k].setPosition(i, 300);
		coins[k].setScale(0.2f, 0.2f);
		window.draw(coins[k]);
	}
	once = false;

}
