/*
  Tibia CLient
  Copyright (C) 2019 Saiyans King

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef __FILE_CREATURE_h_
#define __FILE_CREATURE_h_

#include "thing.h"
#include "thingManager.h"
#include "animator.h"

class ThingType;
class Tile;
class Creature : public Thing
{
	public:
		Creature();

		static double speedA, speedB, speedC;

		virtual Creature* getCreature() {return this;}
		virtual const Creature* getCreature() const {return this;}

		virtual bool isCreature() {return true;}

		bool isPlayer() {return (m_type == CREATURETYPE_PLAYER);}
		bool isMonster() {return (m_type == CREATURETYPE_MONSTER || m_type == CREATURETYPE_SUMMON_OWN || m_type == CREATURETYPE_SUMMON_OTHERS);}
		bool isNPC() {return (m_type == CREATURETYPE_NPC);}

		void preMove(const Position& fromPos, const Position& toPos);
		void move(const Position& fromPos, const Position& toPos, Tile* oldTile, Tile* newTile, bool preMove = false);
		void stopMove();

		void addToDrawnTile(Tile* tile);
		void resetDrawnTile();
		void removeFromDrawnTile();

		void updateFrameGroup(Uint8 frameGroup);
		void update();
		void render(Sint32 posX, Sint32 posY, bool visible_tile);
		void renderInformations(Sint32 posX, Sint32 posY, Sint32 drawX, Sint32 drawY, float scale, bool visible);

		void addTimedSquare(Uint8 color);
		void removeTimedSquare();
		void showStaticSquare(Uint8 color);
		void hideStaticSquare();

		SDL_INLINE void setId(Uint32 cid) {m_id = cid;}
		void setName(const std::string name);
		void setHealth(Uint8 health);
		void turnDirection(Direction direction);
		void setOutfit(Uint16 lookType, Uint16 lookTypeEx, Uint8 lookHead, Uint8 lookBody, Uint8 lookLegs, Uint8 lookFeet, Uint8 lookAddons, Uint16 lookMount);
		SDL_INLINE void setSpeed(Uint16 speed) {m_speed = speed;}
		SDL_INLINE void setHelpers(Uint16 helpers) {m_helpers = helpers;}
		void setSkull(Uint8 skull);
		void setShield(Uint8 shield);
		SDL_INLINE void setUnpassable(bool unpassable) {m_unpassable = unpassable;}
		SDL_INLINE void setLight(Uint16 light[2]) {m_light[0] = light[0]; m_light[1] = light[1];}
		void setEmblem(Uint8 emblem);
		void setType(Uint8 type);
		void setIcon(Uint8 icon);
		SDL_INLINE void setLocalCreature(bool localCreature) {m_isLocalCreature = localCreature;}
		SDL_FORCE_INLINE Uint32 getId() {return m_id;}
		SDL_FORCE_INLINE std::string& getName() {return m_name;}
		SDL_FORCE_INLINE Uint8 getHealth() {return m_health;}
		SDL_FORCE_INLINE Uint16 getSpeed() {return m_speed;}
		SDL_FORCE_INLINE Uint8 getSkull() {return m_skull;}
		SDL_FORCE_INLINE Uint8 getShield() {return m_shield;}
		SDL_FORCE_INLINE bool isUnpassable() {return m_unpassable;}
		SDL_FORCE_INLINE Uint8 getEmblem() {return m_emblem;}
		SDL_FORCE_INLINE Uint8 getType() {return m_type;}
		
		SDL_FORCE_INLINE bool isWalking() {return m_walking;}
		SDL_FORCE_INLINE bool isPreWalking() {return m_preWalking;}
		SDL_FORCE_INLINE Sint32 getWalkOffsetX() {return m_walkOffsetX;}
		SDL_FORCE_INLINE Sint32 getWalkOffsetY() {return m_walkOffsetY;}
		SDL_FORCE_INLINE Direction getDirection() {return m_direction;}
		SDL_FORCE_INLINE Direction getWalkDirection() {return m_walkDirection;}

		Sint32 getOffsetX(bool checkPreWalk = false);
		Sint32 getOffsetY(bool checkPreWalk = false);
		Sint32 getStepDuration(bool ignoreDiagonal);

	protected:
		std::string m_name;
		ThingType* m_thingType;
		ThingType* m_mountType;
		Animator* m_outfitAnimator[ThingFrameGroup_Last];
		Animator* m_mountAnimator[ThingFrameGroup_Last];
		Animation m_outfitAnimation[ThingFrameGroup_Last];
		Animation m_mountAnimation[ThingFrameGroup_Last];

		Tile* m_tile;
		Tile* m_walkTile;
		Tile* m_drawnTile;

		Uint32 m_nameLen;
		Uint32 m_updateTime;
		Uint32 m_walkStartTime;
		Uint32 m_walkEndTime;
		Uint32 m_walkTime;
		Uint32 m_timedSquareStartTime;
		Uint32 m_shieldTime;

		Sint32 m_walkedPixels;
		Sint32 m_walkOffsetX;
		Sint32 m_walkOffsetY;

		Sint32 m_shieldX;
		Sint32 m_shieldY;
		Sint32 m_skullX;
		Sint32 m_skullY;
		Sint32 m_typeX;
		Sint32 m_typeY;
		Sint32 m_iconX;
		Sint32 m_iconY;
		Sint32 m_emblemX;
		Sint32 m_emblemY;

		Uint32 m_id;
		Uint32 m_outfit;

		Uint16 m_light[2];
		Uint16 m_speed;
		Uint16 m_helpers;

		Uint8 m_lookAddons;
		Uint8 m_health;
		Uint8 m_skull;
		Uint8 m_shield;
		Uint8 m_emblem;
		Uint8 m_type;
		Uint8 m_icon;

		Uint8 m_timedSquareRed;
		Uint8 m_timedSquareGreen;
		Uint8 m_timedSquareBlue;
		Uint8 m_staticSquareRed;
		Uint8 m_staticSquareGreen;
		Uint8 m_staticSquareBlue;
		Uint8 m_red;
		Uint8 m_green;
		Uint8 m_blue;

		Direction m_direction;
		Direction m_turnDirection;
		Direction m_walkDirection;

		Uint8 m_outfitAnim;
		Uint8 m_mountAnim;
		Uint8 m_currentFrame;
		Uint8 m_animationFrame;

		bool m_walking;
		bool m_preWalking;
		bool m_isLocalCreature;
		bool m_unpassable;
		bool m_showTimedSquare;
		bool m_showStaticSquare;
		bool m_showShield;
};

#endif /* __FILE_CREATURE_h_ */