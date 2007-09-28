//////////////////////////////////////////////////////////////////////
// Yet Another Tibia Client
//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//////////////////////////////////////////////////////////////////////

#ifndef __YATC_CREATURE_H__
#define __YATC_CREATURE_H__

#include <string>
#include <map>

#include "thing.h"
#include "enums.h"

class Tile;

class Creature : public Thing
{
public:

	virtual ~Creature(){}

	virtual uint32_t getID() const {return m_id;}
	virtual uint32_t getOrder() const { return 4;}

	virtual Creature* getCreature(){return this;}
	virtual const Creature* getCreature() const {return this;}

	bool isPlayer() { return (m_id & 0x10000000 != 0) && (m_id & 0x20000000 == 0); }
	bool isMonster() { return (m_id & 0x40000000 != 0); }
	bool isNpc() { return (m_id & 0x10000000 != 0) && (m_id & 0x20000000 != 0); }

protected:
	Creature();

public:
	uint32_t m_id;
	std::string m_name;
	uint32_t m_health;
	Direction m_lookdir;

	Outfit_t m_outfit;

	uint32_t m_lightLevel;
	uint32_t m_lightColor;
	uint32_t m_speed;
	uint32_t m_skull;
	uint32_t m_shield;

	friend class Creatures;
};

class Creatures
{
public:
	~Creatures() {}

	static Creatures& getInstance(){
		static Creatures instance;
		return instance;
	}
	void clear();

	Creature* getCreature(uint32_t id);

	Creature* addCreature(uint32_t id);
	void removeCreature(uint32_t id);

	static uint32_t OutfitLookupTable[];

private:

	static int16_t reserveCreature(uint32_t id);
	// 150 is the size for 7.8-8.0 clients
	#define CREATURES_ARRAY 150
	static Creature m_creaturesArray[CREATURES_ARRAY];

	Creatures() {}

	typedef std::map<uint32_t, uint16_t> CreatureMap;
	CreatureMap m_creaturesId;
};

#endif