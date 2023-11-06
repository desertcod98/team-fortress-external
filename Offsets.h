#pragma once

namespace offsets {
	static int entitylist_ptr = 0x005DBED8;

	//from entitylist base
	static int player_ptr = 0x20;
	static int first_entity_ptr = 0x34;
	static int entity_ptr_offset = 0x14;


	//from entity base
	static int entity_health = 0xF4;
	static int entity_name = 0xFB4;
	static int entity_coords = 0x2B8;
	static int entity_team = 0x22C; //1 is spectator, 2 and 3 are teams
	static int entity_is_dead = 0xB84; //TODO check if correct

	//view matrix
	static int view_matrix = 0x59FD80; 
}

