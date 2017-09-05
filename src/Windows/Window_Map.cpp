#include <Szczur/Map/MapManager.h>
#include <Window_Map.h>
#include <Window_Menu.h>

namespace Szczur {
	Window_Map::Window_Map() {
		MapManager::Init();
		SetActive();
	}
	
	void Window_Map::Refresh() {
		MapManager::DrawBack();
		
		player.Draw();
		
		MapManager::DrawFront();
	}
	
	void Window_Map::OnKeyPress(Input::Key key) {
		if (key == Input::KEY_Escape) new Window_Menu;
	}
	
	void Window_Map::OnLostActive() {
		player.lockMove = true;
	}
	
	void Window_Map::OnGainActive() {
		player.lockMove = false;
	}
}
