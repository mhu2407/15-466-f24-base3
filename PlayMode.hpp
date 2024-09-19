#include "Mode.hpp"

#include "Scene.hpp"
#include "Sound.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//----- game state -----

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} c, d, e, f, g, a, b;

	struct Letter {
		std::string button;
		std::shared_ptr< Sound::PlayingSample > play_noise;
		Scene::Transform *transform = nullptr;
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		bool going_up = true;
	} c_note, d_note, e_note, f_note, g_note, a_note, b_note;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;

	//hexapod leg to wobble:
	Scene::Transform *c_transform = nullptr;
	Scene::Transform *d_transform = nullptr;
	Scene::Transform *e_transform = nullptr;
	Scene::Transform *f_transform = nullptr;
	Scene::Transform *g_transform = nullptr;
	Scene::Transform *a_transform = nullptr;
	Scene::Transform *b_transform = nullptr;

	glm::vec3 c_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 d_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 e_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 f_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 g_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 a_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 b_position = glm::vec3(0.0f, 0.0f, 0.0f);

	Letter *note_list[7];

	// pointer to background drum beat sound
	std::shared_ptr< Sound::PlayingSample > drum_beat_loop;
	uint32_t points = 0;
	bool key_hit = false;
	bool game_over = false;
	float time = 0;
	uint32_t note_index = 0;
	//camera:
	Scene::Camera *camera = nullptr;

};
