#include <iostream>
#include "globals.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "player.h"

// ----------------------------------------------------
Player::Player(const char* title, const char* description, Room* room) :
Creature(title, description, room)
{
	type = PLAYER;
}

// ----------------------------------------------------
Player::~Player()
{
}

// ----------------------------------------------------
void Player::Look(const vector<string>& args) const
{
	if(args.size() > 1)
	{
		for(list<Entity*>::const_iterator it = parent->container.begin(); it != parent->container.cend(); ++it)
		{
			if(Same((*it)->name, args[1]) || ((*it)->type == EXIT && Same(args[1], ((Exit*)(*it))->GetNameFrom((Room*)parent))))
			{
				(*it)->Look();
				return;
			}
		}

		if(Same(args[1], "me"))
		{
			cout << "\n" << name << "\n";
			cout << description << "\n";
		}
	}
	else
	{
		parent->Look();
	}
}

// ----------------------------------------------------
bool Player::Go(const vector<string>& args)
{
	
Exit* exit = GetRoom()->GetExit(args[1]);

	if(exit == NULL)
	{
		cout << "\nThere is no exit at '" << args[1] << "'.\n";
		return false;
	}

	list<Entity*> body;
	FindAll(CREATURE, body);

	if(exit->locked && body.size() != NULL)
	{
		      cout << "\nThat exit is locked.\n";
		      return false;
	}
	
	cout << "\nYou take direction " << exit->GetNameFrom((Room*) parent) << "...\n";
	ChangeParentTo(exit->GetDestinationFrom((Room*) parent));
	parent->Look();

	return true;
}


// ----------------------------------------------------
bool Player::Take(const vector<string>& args)
{
	


  Creature* targetcreature = (Creature*)parent->Find(args[1], CREATURE);
  list<Entity*> body;
  FindAll(CREATURE, body);

   if (body.size() != NULL)

	      // you have a BODY

   {
      if (targetcreature == NULL)
	      // You're trying to take an object, NOt a CREATURE
	  
      {
		 
	     if(args.size() == 4)
	     {
	    	// cat ?

			 if (body.front()->name == "Cat")
			 {

				 cout << "\nYou have no way to take it. Indeed, there are very few things a cat would be capable to take for its own...\n";
				 return false;
			 }
			 
			 
			 Item* item = (Item*)parent->Find(args[3], ITEM);

		    // we could pick something from a container in our inventory ...
	    	if(item == NULL)
		    	item = (Item*)Find(args[3], ITEM);

	    	if(item == NULL)
	    	{
		    	cout << "\nCannot find '" << args[3] << "' in this room or in your inventory.\n";
		    	return false;
	    	}

	    	Item* subitem = (Item*)item->Find(args[1], ITEM);

	    	if(subitem == NULL)
	    	{
		    	cout << "\n" << item->name << " does not contain '" << args[1] << "'.\n";
	    		return false;
		    }

			if (item->item_type == UNMOVABLE)
			{
				cout << "\nYou can't really take this object. The containitor is too far or shut. \n";
				return false;
			}

	    	cout << "\nYou take " << subitem->name << " from " << item->name << ".\n";
	    	subitem->ChangeParentTo(this);
	     }
	     else if(args.size() == 2)
	     {
			Item* item = (Item*)parent->Find(args[1], ITEM);

			

		   
		    

		    if(item == NULL)
		    {
	    		cout << "\nThere is no item here with that name.\n";
	    		return false;
	    	}
			else if (item->item_type == UNMOVABLE)
			{
				cout << "\nYou can't really take this object. It's too heavy.\n";
				return false;
			}

			// cat ?

			if (body.front()->name == "Cat") 
			{
				if (item->name == "Catfood")
				{
		        cout << "\nThe cat take " << item->name << ".\n";
		        item->ChangeParentTo(this);

				
				cout << "\nThe cat is now very quite. It's time to finally leave this creature and possibly bring it somewhere else...\n";

				



				return false;
				
				}
				else
				{
					cout << "\nYou can't really take this object. You're a cat.\n";
					return false;
				}
			}
			else
			{
				if (body.front()->name == "Girl" && item->name =="Ouija")
				{
				cout << "\nThe girl is relly TOO SCARED to grab this evil object by herself !\n";
				return false;
				}
				else
				{
			    cout << "\nYou take " << item->name << ".\n";
			    item->ChangeParentTo(this);
				}

			
			}
	     }
	     return false;
   
      }
	  else
		  // POSSESSION FAILED !! (you try to take a creature : but you already have a body)
		  
	  {
		  cout << "\nYou're already possessing the " << body.front()->name << ". You can't possess more than one creature at once.\n";
		  return false;
	  }

	  
   } else 

	     // you don't have a body 
   {
	   if (targetcreature != NULL)
		   // try to take creature
	      {

		   if (targetcreature->name == "Girl")
		   {
			   cout << "\nYou can't possess the Girl. This person is apparently able to SEE YOU, and seems scared to death !\n";
		   return false;
		   }
		   if (targetcreature->name == "Demon")
		   {
			   cout << "\nThere is NO WAY you can possess this TERRIFYING BEAST !\n";
		   return false;
		   }

			  if (targetcreature->IsAlive() == true)
			  // POSSESSION SUCCESSFUL !!
			  {
			  cout << "\nYou possess " << targetcreature->name << ".\n";
			  targetcreature->ChangeParentTo(this);
			  cout << "Life Points of " << targetcreature->name << ": " << targetcreature->hit_points << "\n";
			  
			  
			      // take creature's hit points!!
			  
			      this->hit_points = targetcreature->hit_points;

				  // take creature's belongings !!
			      list<Entity*> items;
			      targetcreature->FindAll(ITEM, items);

			      if (items.size() > 0)
			      {
				    cout << "\nYou have now access to the " << targetcreature->name << "'s belongings:\n";

				    for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
				    {
					  Item* i = (Item*)(*it);
					  cout << "You find: " << i->name << "\n";
					  i->ChangeParentTo(this);
				    }
			      }
			   

			  }
			  else
			  // POSSESSION FAILED !! (the body is a corpse)
			  {
				  cout << "\n" << targetcreature->name << " is DEAD. You can't possess corpses.\n";
			  }
	      }
	   else
		   // try to take an object without a body
	       {
		   cout << "\n You're just a wandering soul. You can't take anything without a body.\n";
	       }
   }

   cout << "\n";

	  
   
   
   
 
 
  
  

return false;
}
// ----------------------------------------------------
void Player::Inventory() const {
	// Objects
	
	list<Entity*> items;
	FindAll(ITEM, items);

	if (items.size() == 0) {
		cout << "\nYou do not own any item.\n";
	}
	else {
		cout << "\n+ Here's your worldly possessions: +\n";

		for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it) {
			if (*it == weapon)
				cout << "\n" << (*it)->name << " (as weapon)";
			else if (*it == armour)
				cout << "\n" << (*it)->name << " (as armour)";
			else
				cout << "\n" << (*it)->name;
		}
	}
	cout << "\n";

	// Possessed humans

	list<Entity*> humans;
	FindAll(CREATURE, humans);

	if (humans.size() == 0) {
		cout << "\nYou're not possessing anyone.\n";
	}
	else {
		cout << "\n" << humans.front()->name << " (POSSESSED)";
		}
	
	cout << "\n";



}

// ----------------------------------------------------
bool Player::Drop(const vector<string>& args)
{
	Creature* targetcreature = (Creature*)Find(args[1], CREATURE);
	if (targetcreature == NULL)
		// if NO CREATURE
	{
		if (args.size() == 2)
		{
			Item* item = (Item*)Find(args[1], ITEM);

			if (item == NULL)
			{
				cout << "\nThere is no item on you with that name.\n";
				return false;
			}

			cout << "\nYou drop " << item->name << "...\n";
			item->ChangeParentTo(parent);

			return true;
		}
		else if (args.size() == 4)
		{
			Item* item = (Item*)Find(args[1], ITEM);

			if (item == NULL)
			{
				cout << "\nCan not find '" << args[1] << "' in your inventory.\n";
				return false;
			}

			Item* container = (Item*)parent->Find(args[3], ITEM);

			if (container == NULL)
			{
				container = (Item*)Find(args[3], ITEM);
				cout << "\nCan not find '" << args[3] << "' in your inventory or in the room.\n";
				return false;
			}

			cout << "\nYou put " << item->name << " into " << container->name << ".\n";
			item->ChangeParentTo(container);

			return true;
		}
	}

	// you DROP THE CREATURE

	cout << "\nYou abandon the body of the " << targetcreature->name << " which collapses to the ground...\nThe " << targetcreature->name << " finally wakes up in a state of total confusion, believing it was only a dream.\n";
	targetcreature->ChangeParentTo(parent);
	targetcreature->hit_points = this->hit_points;
	targetcreature->weapon = NULL;
	targetcreature->armour = NULL;

	// back to GHOST state
	this->hit_points = 1;

	// you lose all creature's belongings

	list<Entity*> items;
	FindAll(ITEM, items);

	if (items.size() > 0)
	{
		cout << "\nYou lose all the " << targetcreature->name << "'s belongings:\n";

		for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
		{
			Item* i = (Item*)(*it);
			cout << "You give back: " << i->name << "\n";
			i->ChangeParentTo(targetcreature);

			

			if (targetcreature->name == "Cat" && i->name =="Catfood")
			{
				// The Cat Creature disappears...
				targetcreature->ChangeParentTo(NULL);
									
							Item* subitem = (Item*)i->Find(ITEM);

							// Now it's a quite cat OBJECT...

							cout << "\n The cat is very QUITE now, it will accept to be taken anywhere or to ANYONE...\n";
							subitem->ChangeParentTo(parent);
							i->ChangeParentTo(NULL);
							return true;
						


					

				








			}

		}
	}




	return false;
}

// ----------------------------------------------------
bool Player::Equip(const vector<string>& args)
{
	Item* item = (Item*)Find(args[1], ITEM);

	if(item == NULL)
	{
		cout << "\nCannot find '" << args[1] << "' is not in your inventory.\n";
		return false;
	}

	switch(item->item_type)
	{
		case WEAPON:
		weapon = item;
		break;

		case ARMOUR:
		armour = item;
		break;

		default:
		cout << "\n" << item->name << " cannot be equipped.\n";
		return false;
	}
		
	cout << "\nYou equip " << item->name << "...\n";

	return true;
}

// ----------------------------------------------------
bool Player::UnEquip(const vector<string>& args)
{
	if(!IsAlive())
		return false;

	Item* item = (Item*)Find(args[1], ITEM);

	if(item == NULL)
	{
		cout << "\n" << item->name << " is not in your inventory.\n";
		return false;
	}

	if(item == weapon)
		weapon = NULL;
	else if(item == armour)
		armour = NULL;
	else
	{
		cout << "\n" << item->name << " is not equipped.\n";
		return false;
	}

	cout << "\nYou un-equip " << item->name << "...\n";

	return true;
}

// ----------------------------------------------------
bool Player::Examine(const vector<string>& args) const
{
	Creature* target = (Creature*)parent->Find(args[1], CREATURE);
	if (target == NULL)
	
	//Not a creature
	{
	  







		Item* target = (Item*)parent->Find(args[1], ITEM);

		if (target == NULL)
		{

			Item* item = (Item*)Find(args[1], ITEM);

			if (item == NULL)
			{
				if (Same(args[1], "me"))
				{
					cout << "\n" << name << "\n";
					cout << description << "\n";
					return true;
				}
				else
				{
					cout << "\n '" << args[1] << "' not found in your inventory or nerby.\n";
					return false;
				}
			}
			else
			{

				if (target->name == "Catfood")
				{
					cout << "\n This is just food for cats.\n";
					return false;
				}


				item->Look();
				return true;
			}

		}

		if (target->name == "Catfood")
		{
			cout << "\n This is just food for cats.\n";
			return false;
		}
		if (target->name == "Ouija")
		{
			cout << "\n A spirit board marked with letters and numbers. It can be used to communicate with the dead. \n";
			return false;
		}
		if (target->name == "Quitecat")
		{
			cout << "\n The cat can be now taken somewhere else or DELIVERED to someone... \n";
			return false;
		}




		target->Look();
		return true;
	}

	//A creature

	target->Inventory();
	target->Stats();



	return true;
}


// ----------------------------------------------------
bool Player::Attack(const vector<string>& args)
{
	if (this->weapon == NULL)
	{
		cout << "\n" << " You can't attack without a weapon equipped.\n";
		return false;
	}

	Creature* target = (Creature*)parent->Find(args[1], CREATURE);

	if (target == NULL)
	{
		cout << "\n" << args[1] << " is not here.";
		return false;
	}

	combat_target = target;
	cout << "\nYou jump to attack " << target->name << "!\n";
	return true;
}

// ----------------------------------------------------
bool Player::Loot(const vector<string>& args)
{
  list<Entity*> body;
  FindAll(CREATURE, body);

  if (body.size() != NULL)
  {
	  Creature* target = (Creature*)parent->Find(args[1], CREATURE);

	  if (target == NULL)
	  {
		  cout << "\n" << args[1] << " is not here.\n";
		  return false;
	  }

	  if (target->IsAlive() == true)
	  {
		  cout << "\n" << target->name << " cannot be looted until it is killed.\n";
		  return false;
	  }

	  list<Entity*> items;
	  target->FindAll(ITEM, items);

	  if (items.size() > 0)
	  {
		  cout << "\nYou loot " << target->name << "'s corpse:\n";

		  for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
		  {
			  Item* i = (Item*)(*it);
			  cout << "You find: " << i->name << "\n";
			  i->ChangeParentTo(this);
			  if (i->name == "Yoursoul")
			  {
				  this->hit_points == 3000;
				  cout << "\nYOU WIN !!! GOOD ENDING\n";
				  return true;
			  }
		  }
	  }
	  else
		  cout << "\nYou loot " << target->name << "'s corpse, but find nothing there.\n";
  }
  else
  {
	  cout << "\nYou're made of pure spirit. You can't loot anyone in such state.\n";
  }

return false;
}

// ----------------------------------------------------
bool Player::Lock(const vector<string>& args)
{
	if(!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetExit(args[1]);

	if(exit == NULL)
	{
		cout << "\nThere is no exit at '" << args[1] << "'.\n";
		return false;
	}

	if(exit->locked == true)
	{
		cout << "\nThat exit is already locked.\n";
		return false;
	}

	Item* item = (Item*)Find(args[3], ITEM);

	if(item == NULL)
	{
		cout << "\nItem '" << args[3] << "' not found in your inventory.\n";
		return false;
	}

	if(exit->key != item)
	{
		cout << "\nItem '" << item->name << "' is not the key for " << exit->GetNameFrom((Room*)parent) << ".\n";
		return false;
	}

	cout << "\nYou lock " << exit->GetNameFrom((Room*)parent) << "...\n";

	exit->locked = true;

	return true;
}

// ----------------------------------------------------
bool Player::UnLock(const vector<string>& args)
{
	if(!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetExit(args[1]);

	if(exit == NULL)
	{
		cout << "\nThere is no exit at '" << args[1] << "'.\n";
		return false;
	}

	if(exit->locked == false)
	{
		cout << "\nThat exit is not locked.\n";
		return false;
	}

	Item* item = (Item*)Find(args[3], ITEM);

	if(item == NULL)
	{
		cout << "\nKey '" << args[3] << "' not found in your inventory.\n";
		return false;
	}

	if(exit->key != item)
	{
		cout << "\nKey '" << item->name << "' is not the key for " << exit->GetNameFrom((Room*)parent) << ".\n";
		return false;
	}

	cout << "\nYou unlock " << exit->GetNameFrom((Room*)parent) << "...\n";

	exit->locked = false;

	return true;
}
// ----------------------------------------------------
bool Player::Scream(const vector<string>& args)
{
	
		cout << "\nYou emit a creepy and unhuman SCREAM...Seems coming from the deep...And it can clearly BREAK GLASSES\n";
		
		list<Entity*> items;
		parent->FindAll(ITEM, items);

		if (items.size() > 0)
		{
			
			int specialItemCount = 0;
			for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
			{
				Item* i = (Item*)(*it);
				
				if (i->item_type == UNMOVABLE)
				{
					Item* subitem = (Item*)i->Find(ITEM);

				cout << "A " << subitem->name << " fall on the ground...\n";
				subitem->ChangeParentTo(parent);
				i->ChangeParentTo(NULL);
				return true;
				}
			
				if (i->item_type == SPECIAL)
				{
					
					cout << "A " << i->name << " is present...\n";
					
					if(parent->name == "Ceiling")
					{

					specialItemCount++;
					if (specialItemCount >= 2) 
					
					    {
						std::cout << "Two special elements finally co-exist for the invocation...!\n";
						Item* subitem = (Item*)i->Find(ITEM);
						cout << "A " << subitem->name << " fall on the ground...\n";
						subitem->ChangeParentTo(parent);

					    return true;
					    }
					}
				}




			
			}
			
		}
		
		
			cout << "No one can hear your scream here...\n";
		
		
		return false;




	
	
	


	
}

// ----------------------------------------------------
bool Player::Give(const vector<string>& args)
{
	list<Entity*> body;
	FindAll(CREATURE, body);
	Creature* elementcreature = (Creature*)Find(args[1], CREATURE);

	if (body.size() == NULL)
	{
		cout << "\nYou can't really do this operation without a body !!.\n";
		return false;
	}
	else if (body.front()->name == "Cat")
	{
		cout << "\nYou're a cat ! A cat cannot give any object to anyone !!.\n";
		return false;
	}

	if (elementcreature == NULL && body.size() != NULL)
		// if first element is NO CREATURE and you have a body, search for the item...

	{


		Item* item = (Item*)Find(args[1], ITEM);

		if (item == NULL)
		{
			cout << "\n '" << args[1] << "' not found in your inventory.\n";
			return false;
		}

		Creature* targetcreature = (Creature*)parent->Find(args[3], CREATURE);

		if (targetcreature == NULL)
		{
			cout << "\n '" << args[3] << "' is not in this room.\n";
			return false;
		}

		// you can give something to someone...
		
		

		
		// proceed to give...
		// unequip weapons and armours...






		    if (item == weapon)
			{
			weapon = NULL; 
			}
			else if (item == armour)
			{
			armour = NULL;}
		    
			// proceed to give...

			if (targetcreature->name == "Cat")
			{
				if (item->name == "Catfood")
			    {
				// The Cat Creature disappears...
				targetcreature->ChangeParentTo(NULL);

				Item* subitem = (Item*)item->Find(ITEM);

				// Now it's a quite cat OBJECT...

				cout << "\n The cat is very QUITE now, it will accept to be taken anywhere or to ANYONE...\n";
				subitem->ChangeParentTo(parent);
				item->ChangeParentTo(NULL);
				return true;
			    }
				else
				{
					cout << "\nyou can't give anything to the cat...\n";
					return false;
				}

			}
			
			if (targetcreature->name == "Girl")
			{
				if (item->name == "Quitecat")
				{
					cout << "\n The girl is very happy to get her cat. However she will leave him take a walk around the room...\n";
					item->ChangeParentTo(parent);
					return true;
				}
				if (item->name == "Ouija")
				{
					cout << "\n The girl is scared...but she still want to help you. So she will drop the Ouija to the center of the room...Get ready to communicate...\n";
					item->ChangeParentTo(parent);
					return true;
				}
			}
			else 
			{




			item->ChangeParentTo(targetcreature);
			
			cout << "\nYou give '" << item->name << "' to the " << targetcreature->name << ".\n";
			
			return false;
			}
	}

	// if creature...

	cout << "\nYou can't give your body to anyone !\n";


	return true;
}