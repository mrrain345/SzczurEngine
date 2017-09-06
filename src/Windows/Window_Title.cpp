#include <Windows/Window_Title.h>
#include <Windows/Window_Map.h>
#define _USE_MATH_DEFINES
#include <cmath>

namespace Szczur {
	static int x, y, width, height;
	static float start_x;
	static float start_y;
	static float end_x;
	static float end_y;

	Window_Title::Window_Title() {
		SetActive();
		
		option = 0;
		options_count = 4;
		
		options[0] = sf::String(L"Nowa Gra");
		options[1] = sf::String(L"Wczytaj Grę");
		options[2] = sf::String(L"Ustawienia");
		options[3] = sf::String(L"Wyjdź");
		
		width = 280;
		height = options_count * 32 + 32;
		x = (Game::Width() - width) / 2;
		y = Game::Height() - height - 64;
		
		start_x = x;
		start_y = y;
		end_x = 32;
		end_y = Game::Height() - height - 32;
	}
	
	void Window_Title::Refresh() {
		content.Fill(Color(128, 128, 128));
		content.FillRect(sf::IntRect(x, y, width, height), Color(66, 66, 66));
		
		content.FillRect(sf::IntRect(x + 16,  y + 16 + option*32, width - 32, 32), Color::White);
		
		for (int i = 0; i < options_count; i++) {
			if (i == option) content.textColor = Color::Black;
			if (i == 1) content.textColor = Color(128, 128, 128);
			content.DrawText(Vector2(x + 16, y + 16 + i*32), options[i], 24);
			content.textColor = Color::White;
		}
	}
	
	static float anim_linear(float x) { return x; }
	static float anim_cos(float x) { return -cos(x*(M_PI/2))+1; }
	static float anim_cos2(float x) { return (-cos(x*M_PI)+1)/2; }
	static float anim_asin(float x) { return asin(x); }
	
	static int animMode = 0;
	static float time = 0;
	
	void Window_Title::Update() {
		if (animMode == 0) return;
		if (animMode == 1) time += Time::RealDeltaTime()*4;
		if (animMode == 3) time -= Time::RealDeltaTime()*4;
		
		x = content.Animation(start_x, end_x, anim_cos, time);
		y = content.Animation(start_y, end_y, anim_cos, time);
		
		if (animMode == 1) {
			if (time > 1) {
				animMode = 2;
				time = 1;
				x = end_x;
				y = end_y;
			}
			Game::Refresh();
		}
		
		if (animMode == 3) {
			if (time < 0) {
				animMode = 0;
				time = 0;
				x = start_x;
				y = start_y;
			}
			Game::Refresh();
		}
	}
	
	void Window_Title::OnKeyPress(Input::Key key) {
		if (key == Input::KEY_Up && option > 0) {
			option--;
			if (option == 1) option--;
			Game::Refresh();
		}
		
		if (key == Input::KEY_Down && option < options_count-1) {
			option++;
			if (option == 1) option++;
			Game::Refresh();
		}
		
		if (key == Input::KEY_Return) {
			if (option == 0) { new Window_Map; Close(); }
			if (option == 2 && animMode == 0) { time = 0; animMode = 1; }
			if (option == 2 && animMode == 2) { time = 1; animMode = 3; }
			if (option == options_count-1) Game::Close();
		}
	}
}
