#include <iostream>
#include <GL/freeglut.h>

#include "MyRectangle.h"
#include "MyPolygon.h"
#include <vector>
#include <string>
#include <ctime>


using namespace std;

const int GAME_LOGIC_REFRESH_TIME = 10;

const double wall_position_x = 30.3;
const double wall_position_y = 22.5;

int life_points = 10;
int player_points = 0;
int total_game_time = 0;
bool game_over = false;

int spawn_enemies_interval = 3000;
int enemies_move_interval = 100;

int game_stage_interval = 5000;
int game_stage_number = 0;

// game objects

MyPolygon player_obj(0.6, 0.5, 0.8);

vector<MyRectangle> missles;


vector<MyRectangle> walls;
vector<MyRectangle> enemies;

/* helper functions for settings options and parameters */
void InitGLUTScene(char* window_name)
{
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(40, 40);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow(window_name);

	glClearColor(0.05, 0.05, 0.05, 1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
}

void gameLogic(int value)
{
	// check player collision with walls
	for (int i = 0; i < walls.size(); i++)
	{
		if(player_obj.Collision(walls[i]))
		{
			cout << "Kolizja ze sciana: " << i << endl;
		}
	}
	// check player collision with enemies
	for (auto itr = enemies.begin(); itr != enemies.end();)
	{
		if (player_obj.Collision(*itr))
		{
			itr = enemies.erase(itr);
			if (life_points > 0)
			{
				life_points--;
			}
		}
		else
		{
			itr++;
		}
	}

	// check missles collision with enemies
	for (auto itr_missle = missles.begin(); itr_missle != missles.end();)
	{
		for (auto itr_enemy = enemies.begin(); itr_enemy != enemies.end();)
		{
			if (itr_missle == missles.end())
			{
				break;
			}
			if (itr_missle->Collision(*itr_enemy))	
			{
				itr_enemy = enemies.erase(itr_enemy);
				itr_missle = missles.erase(itr_missle);
				player_points++;
			}
			else
			{
				itr_enemy++;
			}
		}
		if (itr_missle == missles.end())
		{
			break;
		}
		itr_missle++;
	}
	// check enemies collision with bottom wall
	for (auto itr_enemy = enemies.begin(); itr_enemy != enemies.end();)
	{
		if (itr_enemy->Collision(walls[1]))
		{
			itr_enemy = enemies.erase(itr_enemy);
			if (life_points > 0)
			{
				life_points--;
			}
		}
		else
		{
			itr_enemy++;
		}
	} 
	// check missles co llisions with top wall
	for (auto itr_missle = missles.begin(); itr_missle != missles.end();)
	{
		if (itr_missle->Collision(walls[0]))
		{
			itr_missle = missles.erase(itr_missle);
		}
		else
		{
			itr_missle++;
		}
	}

	// check game ending
	if (life_points <= 0)
	{
		
		game_over = true;
	}
	glutTimerFunc(GAME_LOGIC_REFRESH_TIME, gameLogic, 1);
}

void resize(int width, int height)
{
	glutReshapeWindow(800, 600);						// Seeting window size. (800-600)
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	gluLookAt(0, 0, 45, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

void idle()
{
	glutPostRedisplay();
}

void keyboard(unsigned char key_pressed, int mouse_x, int mouse_y)
{
	if (!game_over)
	{
		double distance = 2.0;
		switch (key_pressed)
		{

		case 'a':
			if (!player_obj.Collision(walls[2]))
			{
				player_obj.Move(-distance, 0.0);
			}
			break;
		case 'd':
			if (!player_obj.Collision(walls[3]))
			{
				player_obj.Move(distance, 0.0);
			}
			break;
			// shoot
		case ' ':
			MyRectangle missle(0.7, 1.4, 1, 0, 0);
		
			missle.SetPosition(player_obj.GetPositionX(), player_obj.GetPositionY());
			missles.push_back(missle);
			break;
		}
	}
}

void drawText(void * font, string s, float x, float y, float z, float red, float green, float blue) {
	unsigned int i;
	glColor3f(red, green, blue);
	glRasterPos3f(x, y, z);

	for (i = 0; i < s.length(); i++)
		glutBitmapCharacter(font, s[i]);
}

void display()
{
	// clear the scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	string game_stage = "GAME STAGE: ";
	game_stage.append(to_string(game_stage_number));
	string points = "POINTS: ";
	points.append(to_string(player_points));
	string life = "LIFE: ";
	life.append(to_string(life_points));
	// string
	drawText(GLUT_BITMAP_HELVETICA_18, game_stage, -25, 20.5, 0, 1, 0.5, 0);
	drawText(GLUT_BITMAP_HELVETICA_18, points, -10,20.5,0,0.2,0.8,0.3);
	drawText(GLUT_BITMAP_HELVETICA_18, life, 0, 20.5, 0, 1, 0.2, 0);

	if (!game_over)
	{
		// player
		player_obj.Draw();

		// walls
		for (auto itr = walls.begin(); itr != walls.end(); itr++)
		{
			itr->Draw();
		}

		// enemies
		for (auto itr = enemies.begin(); itr != enemies.end(); itr++)
		{
			itr->Draw();
		}

		// missles
		for (auto itr = missles.begin(); itr != missles.end(); itr++)
		{
			itr->Draw();
		}
	}
	else
	{
		drawText(GLUT_BITMAP_HELVETICA_18, "GAME OVER", -5, 0, 0, 1, 0, 0);
	}
	glPopMatrix();

	glutSwapBuffers();
}


void passiveMouseMotion(int mouse_x, int mouse_y)
{
	double windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	double windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

	double mx = ((double)mouse_x - windowWidth / 2) / windowWidth * 54;
	player_obj.SetPosition(mx, -21);
}
void SetCallbackFunctions()
{
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(passiveMouseMotion);
	glutTimerFunc(GAME_LOGIC_REFRESH_TIME, gameLogic, 0);
}

void SetObjectsPositions()
{
	// player
	player_obj.SetPosition(0, -20);

	// walls
	MyRectangle top_wall(60, 0.5, 0.5, 0.5, 0.5);
	top_wall.SetPosition(0, wall_position_y-3);
	walls.push_back(top_wall);

	MyRectangle bottom_wall(60, 0.5, 0.5, 0.5, 0.5);
	bottom_wall.SetPosition(0, -wall_position_y);
	walls.push_back(bottom_wall);

	MyRectangle left_wall(1, 44.5, 0.5, 0.5, 0.5);
	left_wall.SetPosition(-wall_position_x, 0);
	walls.push_back(left_wall);

	MyRectangle right_wall(1, 44.5, 0.5, 0.5, 0.5);
	right_wall.SetPosition(wall_position_x, 0);
	walls.push_back(right_wall);
}

void spawn_enemies()
{
	
	float red, green, blue;
	for (int i = -25; i < 25; i += 5)
	{
		int random_number = (rand() % 100);
		
		if (random_number >= 30)
		{
			if (game_stage_number < 3)
			{
				red = 0;
				green = 0;
				blue = 1;
			}
			else if (game_stage_number < 6)
			{
				red = 1;
				green = 0.5;
				blue = 0;
			}
			else if (game_stage_number < 9)
			{
				red = 1;
				green = 0;
				blue = 0;
			}
			else
			{
				red = 1;
				green = 1;
				blue = 1;
			}
			MyRectangle enemy(3, 3, red, green, blue);
			enemy.SetPosition(i, 17);
			enemies.push_back(enemy);
		}
	}
}

void spawn_enemies_timer(int time_ms)
{
	spawn_enemies();
	if (!game_over)

	{
		glutTimerFunc(spawn_enemies_interval, spawn_enemies_timer, spawn_enemies_interval);
	}
}

void enemies_move()
{
	
	for (auto itr = enemies.begin(); itr != enemies.end(); itr++)
	{
		itr->Move(0, -0.2);
	}
}

void enemies_move_timer(int time_ms)
{
	enemies_move();

	if (!game_over)
	{
		glutTimerFunc(enemies_move_interval, enemies_move_timer, enemies_move_interval);
	}
}

void missle_move()
{
	
	for (auto itr = missles.begin(); itr != missles.end(); itr++)
	{
		itr->Move(0, 0.7);
	}
}
void missle_move_timer(int time_ms)
{
	missle_move();

	if (!game_over)
	{
		glutTimerFunc(time_ms, missle_move_timer, time_ms);
	}
}


void total_game_time_timer(int time_ms)
{
	total_game_time += time_ms;
	
	if (!(spawn_enemies_interval == 500 && enemies_move_interval == 10))
	{
		game_stage_number = total_game_time / game_stage_interval;
		cout << "GAME STAGE: " << game_stage_number << endl;
	}

	if (spawn_enemies_interval > 500)
	{
		spawn_enemies_interval -= 500;	// 3000 at start
	}
	if (enemies_move_interval > 10)
	{
		enemies_move_interval -= 10;	// 100 at start
	}

	if (!game_over)
	{
		glutTimerFunc(time_ms, total_game_time_timer, time_ms);
	}
}
int main(int argc, char *argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);
	InitGLUTScene("Gra");

	SetCallbackFunctions();
	SetObjectsPositions();

	enemies_move_timer(enemies_move_interval);
	spawn_enemies_timer(spawn_enemies_interval);

	missle_move_timer(5);
	total_game_time_timer(game_stage_interval);

	glutMainLoop();
	return 0;
}
