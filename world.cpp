#include <iostream>
#include "globals.h"
#include "entity.h"
#include "creature.h"
#include "item.h"
#include "exit.h"
#include "room.h"
#include "player.h"
#include "world.h"

// ----------------------------------------------------
World::World()
{
	tick_timer = clock();
	youWin = false;

	// Rooms ----
	Room* cemetery = new Room("Cemetery", "You are surrounded by tombs. You feel cold and lost.");
	Room* mausoleum = new Room("Mausoleum", "You're within the hall of an imposing Family Tomb");
	Room* hall = new Room("House's Hall", "You are inside the great hall of a huge gothic house.");
	Room* ceiling = new Room("Ceiling", "You reached the top of the house, a very large and dusty roof space.");
	Room* kitchen = new Room("Kitchen", "An old fashion kitchen.");
	Room* crypt = new Room("Crypt", "A spectral huge Vault. You feel an evil, terrifying presence...");
	Room* library = new Room("Library", "An impressive victorian library.");
	Room* dungeon = new Room("Dungeon", "A terrible, scaring place. You can feel the presence of other lost souls. ");
	
	
	Exit* mausoleumtocemetery = new Exit("south", "north", "Stone Path", cemetery, mausoleum);
	Exit* cemeterytohall = new Exit("south", "north", "Stone Path", hall, cemetery);
	Exit* halltoceiling = new Exit("down", "up", "Staircase to Ceiling", ceiling, hall);
	Exit* halltolibrary = new Exit("west", "east", "Door to Library", library, hall);
	Exit* halltokitchen = new Exit("west", "east", "Door to Kitchen", hall, kitchen);
	Exit* kitchentocrypt = new Exit("down", "up", "Staircase to Crypt", kitchen, crypt);
	Exit* mausoleumtodungeon = new Exit("west", "east", "Staircase to Crypt", crypt, dungeon);

	
	mausoleumtocemetery->locked = true;
	kitchentocrypt->locked = true;
	mausoleumtodungeon->locked = true;

	entities.push_back(mausoleum);
	entities.push_back(cemetery);
	entities.push_back(hall);
	entities.push_back(ceiling);
	entities.push_back(kitchen);
	entities.push_back(crypt);
	entities.push_back(library);
	entities.push_back(dungeon);


	entities.push_back(mausoleumtocemetery);
	entities.push_back(cemeterytohall);
	entities.push_back(halltoceiling);
	entities.push_back(halltolibrary);
	entities.push_back(halltokitchen);
	entities.push_back(kitchentocrypt);
	entities.push_back(mausoleumtodungeon);

	


	// Creatures ----
	Creature* butler = new Creature("Butler", "It's Alfred, the house Butler.", hall);
	Creature* girl = new Creature("Girl", "A little scared girl.", ceiling);
	Creature* cat = new Creature("Cat", "A beatiful black cat.", kitchen);
	Creature* exorcist = new Creature("Exorcist", "This misterious man seems to be on a sacred mission.", cemetery);
	Creature* demon = new Creature("Demon", "Two glowing and frightening yellow eyes are now looking at you !", crypt);

	
	// Hit_Points ----
	
	cat->hit_points = 3;
	girl->hit_points = 5;
	butler->hit_points = 20;
	exorcist->hit_points = 150;
	demon->hit_points = 300;
	


	entities.push_back(cat);
	entities.push_back(girl);
	entities.push_back(butler);
	entities.push_back(exorcist);
	entities.push_back(demon);


	// Items -----
	
	Item* glassbowl = new Item("Glassbowl", "a very large and heavy ball of glass. There's something inside, maybe food ?", kitchen, UNMOVABLE);
	Item* catfood = new Item("Catfood", "I think I know who could appreciate this...", glassbowl);
	Item* quitecat = new Item("Quitecat", "The cat can be now taken somewhere else or DELIVERED to someone...", catfood, SPECIAL);
	Item* ouija = new Item("Ouija", "A spirit board marked with letters and numbers. It can be used to communicate with the dead.", library, SPECIAL);
	
	Item* redkey = new Item("Redkey", "An old rusty key, it seems once was painted of RED", butler);
	Item* whitekey = new Item("Whitekey", "An old rusty key, it seems once was painted of WHITE", ouija);
	Item* greykey = new Item("Greykey", "An old rusty key, it seems once was painted of GREY", quitecat);
	Item* book = new Item("Book", "A huge, dusty tome. You can see an inscription saying ''Spells''. It also seems it contain something more.", library);
	
	Item* chandelier = new Item("Chandelier", "A sophisticated, old fashion chandelier enterely made of thin glass...It'd be a pity if someone...", hall, UNMOVABLE);
	Item* soul = new Item("Yoursoul", "It's your only way out to escape from this hell on earth...", demon);
	
	
	
	

	
	Item* holywater = new Item("Holywater", "A flask of holy water", mausoleum, ARMOUR);
	holywater->min_value = 9;
	holywater->max_value = 10;
	exorcist->AutoEquip();

	Item* claws = new Item("Claws", "They won't leave you any escape...", demon, WEAPON);
	claws->min_value = 15;
	claws->max_value = 20;
	demon->AutoEquip();

	Item* glass = new Item("Glass", "A very sharped fragment of glass", chandelier, WEAPON);
	glass->min_value = 15;
	glass->max_value = 20;

	Item* cross = new Item("Cross", "A shiny gold cross pendant.", exorcist, ARMOUR);
	cross->min_value = 5;
	cross->max_value = 10;
	exorcist->AutoEquip();
	
	Item* sword = new Item("Sword", "A mighty medieval sword. You can recognize a Latin inscription that reads ''+ In Spiritum Sanctum +''" , mausoleum, WEAPON);
	sword->min_value = 30;
	sword->max_value = 40;
	exorcist->AutoEquip();

	Item* axe = new Item("Axe", "A glorious medieval battle axe. This beatiful weapon doesn't fear anybody !", dungeon, WEAPON);
	sword->min_value = 30;
	sword->max_value = 50;
	exorcist->AutoEquip();


	// Item-Keys -----
	kitchentocrypt->key = redkey;
	mausoleumtocemetery->key = whitekey;
	mausoleumtodungeon->key = greykey;

	
	entities.push_back(redkey);
	entities.push_back(whitekey);
	entities.push_back(cross);
	entities.push_back(ouija);
	entities.push_back(glass);
	entities.push_back(soul);
	entities.push_back(holywater);
	entities.push_back(sword);
	entities.push_back(glassbowl);
	entities.push_back(catfood);
	entities.push_back(quitecat);
	entities.push_back(greykey);
	entities.push_back(book);
	entities.push_back(chandelier);
	entities.push_back(claws);
	

	// Player ----
	player = new Player("Ghost", "You are DEAD, just a perishable entity trapped in the void.", cemetery);
	player->hit_points = 1;
	entities.push_back(player);
}

// ----------------------------------------------------
World::~World()
{
	for(list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete *it;

	entities.clear();
}

// ----------------------------------------------------
bool World::Tick(vector<string>& args)
{
	bool ret = true;

	if(args.size() > 0 && args[0].length() > 0)
		ret = ParseCommand(args);

	GameLoop();

	return ret;
}

// ----------------------------------------------------
void World::GameLoop()
{
	clock_t now = clock();

	if((now - tick_timer) / CLOCKS_PER_SEC > TICK_FREQUENCY)
	{
		for(list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
			(*it)->Tick();

		tick_timer = now;
	}
}

// ----------------------------------------------------
bool World::isDead()
{
	if (player->hit_points <= 0)
	{
		return true;
	}
	return false;
}

// ----------------------------------------------------
bool World::ParseCommand(vector<string>& args)
{
	bool ret = true;

	switch(args.size())
	{
		case 1: // commands with no arguments ------------------------------
		{
			if(Same(args[0], "look") || Same(args[0], "l"))
			{
				player->Look(args);
			}
			else if(Same(args[0], "north") || Same(args[0], "n"))
			{
				(args.size() == 1) ? args.push_back("north") : args[1] = "north";
				player->Go(args);
			}
			else if(Same(args[0], "south") || Same(args[0], "s"))
			{
				(args.size() == 1) ? args.push_back("south") : args[1] = "south";
				player->Go(args);
			}
			else if(Same(args[0], "east") || Same(args[0], "e"))
			{
				(args.size() == 1) ? args.push_back("east") : args[1] = "east";
				player->Go(args);
			}
			else if(Same(args[0], "west") || Same(args[0], "w"))
			{
				(args.size() == 1) ? args.push_back("west") : args[1] = "west";
				player->Go(args);
			}
			else if(Same(args[0], "up") || Same(args[0], "u"))
			{
				(args.size() == 1) ? args.push_back("up") : args[1] = "up";
				player->Go(args);
			}
			else if(Same(args[0], "down") || Same(args[0], "d"))
			{
				(args.size() == 1) ? args.push_back("down") : args[1] = "down";
				player->Go(args);
			}
			else if(Same(args[0], "stats") || Same(args[0], "st"))
			{
				player->Stats();
			}
			else if(Same(args[0], "inventory") || Same(args[0], "i"))
			{
				player->Inventory();
			}
			else if(Same(args[0], "scream"))
			{
				player->Scream(args);
			}
			else
				ret = false;
			break;
		}
		case 2: // commands with one argument ------------------------------
		{
			if(Same(args[0], "look") || Same(args[0], "l"))
			{
				player->Look(args);
			}
			else if(Same(args[0], "scream"))
			{
				player->Scream(args);
			}
			else if(Same(args[0], "go"))
			{
				player->Go(args);
			}
			else if(Same(args[0], "take") || Same(args[0], "pick"))
			{
				player->Take(args);
			}
			else if(Same(args[0], "drop") || Same(args[0], "put"))
			{
				player->Drop(args);
			}
			else if(Same(args[0], "equip") || Same(args[0], "eq"))
			{
				player->Equip(args);
			}
			else if(Same(args[0], "unequip") || Same(args[0], "uneq"))
			{
				player->UnEquip(args);
			}
			else if(Same(args[0], "examine") || Same(args[0], "ex"))
			{
				player->Examine(args);
			}
			else if(Same(args[0], "attack") || Same(args[0], "at"))
			{
				player->Attack(args);
			}
			else if(Same(args[0], "loot") || Same(args[0], "lt"))
			{
				youWin = player->Loot(args);
			}
			else
				ret = false;
			break;
		}
		case 3: // commands with two arguments ------------------------------
		{
			break;
		}
		case 4: // commands with three arguments ------------------------------
		{
			if(Same(args[0], "unlock") || Same(args[0], "unlk"))
			{
				player->UnLock(args);
			}
			else if(Same(args[0], "lock") || Same(args[0], "lk"))
			{
				player->Lock(args);
			}
			else if(Same(args[0], "take") || Same(args[0], "pick"))
			{
				player->Take(args);
			}
			else if(Same(args[0], "drop") || Same(args[0], "put"))
			{
				player->Drop(args);
			}
			else if (Same(args[0], "give"))
			{
				player->Give(args);
			}
			else
				ret = false;
			break;
		}
		default:
		ret =  false;
	}

	return ret;
}