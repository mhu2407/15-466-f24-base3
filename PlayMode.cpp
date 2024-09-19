#include "PlayMode.hpp"

#include "LitColorTextureProgram.hpp"

#include "DrawLines.hpp"
#include "Mesh.hpp"
#include "Load.hpp"
#include "gl_errors.hpp"
#include "data_path.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <random>

GLuint letters_meshes_for_lit_color_texture_program = 0;
Load< MeshBuffer > letters_meshes(LoadTagDefault, []() -> MeshBuffer const * {
	MeshBuffer const *ret = new MeshBuffer(data_path("letters.pnct"));
	letters_meshes_for_lit_color_texture_program = ret->make_vao_for_program(lit_color_texture_program->program);
	return ret;
});

Load< Scene > letters_scene(LoadTagDefault, []() -> Scene const * {
	return new Scene(data_path("letters.scene"), [&](Scene &scene, Scene::Transform *transform, std::string const &mesh_name){
		Mesh const &mesh = letters_meshes->lookup(mesh_name);

		scene.drawables.emplace_back(transform);
		Scene::Drawable &drawable = scene.drawables.back();

		drawable.pipeline = lit_color_texture_program_pipeline;

		drawable.pipeline.vao = letters_meshes_for_lit_color_texture_program;
		drawable.pipeline.type = mesh.type;
		drawable.pipeline.start = mesh.start;
		drawable.pipeline.count = mesh.count;

	});
});

Load< Sound::Sample > background_drum_sample(LoadTagDefault, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("background-drum-beat.wav"));
});

Load< Sound::Sample > c_note_sample(LoadTagDefault, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("c-note.wav"));
});

Load< Sound::Sample > d_note_sample(LoadTagDefault, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("d-note.wav"));
});

Load< Sound::Sample > e_note_sample(LoadTagDefault, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("e-note.wav"));
});

Load< Sound::Sample > f_note_sample(LoadTagDefault, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("f-note.wav"));
});

Load< Sound::Sample > g_note_sample(LoadTagDefault, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("g-note.wav"));
});

Load< Sound::Sample > a_note_sample(LoadTagDefault, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("a-note.wav"));
});

Load< Sound::Sample > b_note_sample(LoadTagDefault, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("b-note.wav"));
});

PlayMode::PlayMode() : scene(*letters_scene) {
	//get pointers to leg for convenience:
	for (auto &transform : scene.transforms) {
		if (transform.name == "C") c_transform = &transform;
		else if (transform.name == "Text") d_transform = &transform;
		else if (transform.name == "Text.001") e_transform = &transform;
		else if (transform.name == "Text.002") f_transform = &transform;
		else if (transform.name == "Text.003") g_transform = &transform;
		else if (transform.name == "Text.004") a_transform = &transform;
		else if (transform.name == "Text.005") b_transform = &transform;
	}

	c_position = c_transform->position;
	d_position = d_transform->position;
	e_position = e_transform->position;
	f_position = f_transform->position;
	g_position = g_transform->position;
	a_position = a_transform->position;
	b_position = b_transform->position;

	//get pointer to camera for convenience:
	if (scene.cameras.size() != 1) throw std::runtime_error("Expecting scene to have exactly one camera, but it has " + std::to_string(scene.cameras.size()));
	camera = &scene.cameras.front();

	//start music loop playing:
	drum_beat_loop = Sound::loop(*background_drum_sample, 1.0f, 0.0f);

	c_note.button = "c";
	c_note.transform = c_transform;
	c_note.position = c_note.transform->position;
	note_list[0] = &c_note;
	d_note.button = "d";
	d_note.transform = d_transform;
	d_note.position = d_note.transform->position;
	note_list[1] = &d_note;
	e_note.button = "e";
	e_note.transform = e_transform;
	e_note.position = e_note.transform->position;
	note_list[2] = &e_note;
	f_note.button = "f";
	f_note.transform = f_transform;
	f_note.position = f_note.transform->position;
	note_list[3] = &f_note;
	g_note.button = "g";
	g_note.transform = g_transform;
	g_note.position = g_note.transform->position;
	note_list[4] = &g_note;
	a_note.button = "a";
	a_note.transform = a_transform;
	a_note.position = a_note.transform->position;
	note_list[5] = &a_note;
	b_note.button = "b";
	b_note.transform = b_transform;
	b_note.position = b_note.transform->position;
	note_list[6] = &b_note;
}

PlayMode::~PlayMode() {
}

bool PlayMode::handle_event(SDL_Event const &evt, glm::uvec2 const &window_size) {

	if (evt.type == SDL_KEYDOWN) {
		if (evt.key.keysym.sym == SDLK_c) {
			c.downs += 1;
			c.pressed = true;
			Sound::play(*c_note_sample, 1.0f, 0.0f);
			if (!game_over && (note_list[note_index]->button == "c")) {
				key_hit = true;
			} else if (!game_over) game_over = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_d) {
			d.downs += 1;
			d.pressed = true;
			Sound::play(*d_note_sample, 1.0f, 0.0f);
			if (!game_over && (note_list[note_index]->button == "d")) {
				key_hit = true;
			} else if (!game_over) game_over = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_e) {
			e.downs += 1;
			e.pressed = true;
			Sound::play(*e_note_sample, 1.0f, 0.0f);
			if (!game_over && (note_list[note_index]->button == "e")) {
				key_hit = true;
			} else if (!game_over) game_over = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_f) {
			f.downs += 1;
			f.pressed = true;
			Sound::play(*f_note_sample, 1.0f, 0.0f);
			if (!game_over && (note_list[note_index]->button == "f")) {
				key_hit = true;
			} else if (!game_over) game_over = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_g) {
			g.downs += 1;
			g.pressed = true;
			Sound::play(*g_note_sample, 1.0f, 0.0f);
			if (!game_over && (note_list[note_index]->button == "g")) {
				key_hit = true;
			} else if (!game_over) game_over = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_a) {
			a.downs += 1;
			a.pressed = true;
			Sound::play(*a_note_sample, 1.0f, 0.0f);
			if (!game_over && (note_list[note_index]->button == "a")) {
				key_hit = true;
			} else if (!game_over) game_over = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_b) {
			b.downs += 1;
			b.pressed = true;
			Sound::play(*b_note_sample, 1.0f, 0.0f);
			if (!game_over && (note_list[note_index]->button == "b")) {
				key_hit = true;
			} else if (!game_over) game_over = true;
			return true;
		} else if (!game_over) game_over = true;

	} else if (evt.type == SDL_KEYUP) {
		if (evt.key.keysym.sym == SDLK_c) {
			c.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_d) {
			d.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_e) {
			e.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_f) {
			f.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_g) {
			g.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_a) {
			a.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_b) {
			b.pressed = false;
			return true;
		} 
	}

	return false;
}

void PlayMode::update(float elapsed) {
	std::random_device seed;
	std::mt19937 rng(seed());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6);

	time += elapsed;
	if ((time > 1.0f) && !game_over) {
		if (key_hit) {
			key_hit = false;
			points += 1;
			time = 0;
			note_index = dist6(rng);
		} else {
			game_over = true;
		}
	}

	if (game_over) {
		drum_beat_loop->stop(0.5f);
	}
	
	float speed = 1.0f;
	float distance = 0.2f;
	if (note_list[note_index]->going_up) {
		note_list[note_index]->transform->position.z += speed * elapsed;
	} else {
		note_list[note_index]->transform->position.z -= speed * elapsed;
	}
	if (note_list[note_index]->transform->position.z > note_list[note_index]->position.z + distance) {
		note_list[note_index]->going_up = false;
	} else if (note_list[note_index]->transform->position.z < note_list[note_index]->position.z) {
		note_list[note_index]->going_up = true;
	}

	//reset button press counters:
	c.downs = 0;
	d.downs = 0;
	e.downs = 0;
	f.downs = 0;
	g.downs = 0;
	a.downs = 0;
	b.downs = 0;
}

void PlayMode::draw(glm::uvec2 const &drawable_size) {
	//update camera aspect ratio for drawable:
	camera->aspect = float(drawable_size.x) / float(drawable_size.y);

	//set up light type and position for lit_color_texture_program:
	// TODO: consider using the Light(s) in the scene to do this
	glUseProgram(lit_color_texture_program->program);
	glUniform1i(lit_color_texture_program->LIGHT_TYPE_int, 1);
	glUniform3fv(lit_color_texture_program->LIGHT_DIRECTION_vec3, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f,-1.0f)));
	glUniform3fv(lit_color_texture_program->LIGHT_ENERGY_vec3, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 0.95f)));
	glUseProgram(0);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f); //1.0 is actually the default value to clear the depth buffer to, but FYI you can change it.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); //this is the default depth comparison function, but FYI you can change it.

	scene.draw(*camera);

	{ //use DrawLines to overlay some text:
		glDisable(GL_DEPTH_TEST);
		float aspect = float(drawable_size.x) / float(drawable_size.y);
		DrawLines lines(glm::mat4(
			1.0f / aspect, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		));

		if (game_over) {
			constexpr float H = 0.09f;
			std::string final_score = "Final score: " + std::to_string(points);
			lines.draw_text(final_score,
				glm::vec3(-aspect + 0.1f * H, -1.0 + 0.1f * H, 0.0),
				glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
				glm::u8vec4(0x00, 0x00, 0x00, 0x00));
			float ofs = 2.0f / drawable_size.y;
			lines.draw_text(final_score,
				glm::vec3(-aspect + 0.1f * H + ofs, -1.0 + + 0.1f * H + ofs, 0.0),
				glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
				glm::u8vec4(0xff, 0xff, 0xff, 0x00));
		}

	}
	GL_ERRORS();
}
