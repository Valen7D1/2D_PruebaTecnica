#include <string>

#include "Components/Entity.h"
#include "Components/collider.h"
#include "World.h"
#include "Components/controller.h"
#include "Components/movement.h"


using namespace std;

Player* player = nullptr;

void PlayersInput(GLFWwindow* window)
{
	vec2 InputVector = vec2(0.f, 0.f);
	bool FireInput = false;
	
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		InputVector.x -= 1.f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		InputVector.x += 1.f;
	}
	
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		FireInput = true;
	}

	if (player) // set player input on tick
	{
		player->SetPlayerInput(InputVector, FireInput);
	}
}

int main() {
	
	glfwInit();
	
	World* manager = World::GetWorld();
	
	const char* title = "P2_Gonzalo_Valenti";
	
	GLFWwindow* window = glfwCreateWindow(static_cast<int>(manager->Width), static_cast<int>(manager->Height), title, nullptr, nullptr);
	glfwMakeContextCurrent(window);
	lgfx_setup2d(static_cast<int>(manager->Width), static_cast<int>(manager->Height));
	manager->m_Window = window;
	
	manager->PlayerTex = Sprite::loadImage("data/player.png");
	manager->EnemyTex = Sprite::loadImage("data/enemy.png");
	manager->ProjectileTex = Sprite::loadImage("data/bullet.png");
	manager->ExplosionTex = Sprite::loadImage("data/explosion.png");
	manager->Health = Sprite::loadImage("data/player.png");



	manager->Init();
	player = manager->MyPlayer;
	
	double time = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		lgfx_clearcolorbuffer(0, 0, 0);
		double const currentTime = glfwGetTime();
		double const DeltaTime = currentTime - time;
		time = currentTime;

		PlayersInput(window);
		manager->Update(static_cast<float>(DeltaTime));
		//glfwSetWindowTitle(window, ("Mouse: (" + std::to_string(player->m_Movement->m_Direction.x) + ", "+ std::to_string(player->m_Movement->m_Direction.y) + ")").c_str());
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		
	}

	glfwTerminate();

	return 0;
}
