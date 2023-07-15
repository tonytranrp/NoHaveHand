#include "CrystalAuraWTA.h"

CrystalAuraWTA::CrystalAuraWTA() : IModule(0x0, Category::COMBAT, "CrystalAura by rea") {
	registerIntSetting("range", &range, range, 1, 10);
	registerBoolSetting("autoplace", &autoplace, autoplace);
	//registerBoolSetting("onlyCrystal", &crystalCheck, crystalCheck);
	//registerBoolSetting("LockY", &yLock, yLock);
	registerIntSetting("delay", &delay, delay, 0, 20);
	registerBoolSetting("onClick", &isClick, isClick);
	//	registerBoolSetting("Multi", &doMultiple, doMultiple);
	registerBoolSetting("Silent", &silent, silent);
	registerBoolSetting("Render", &renderCA, renderCA);
	registerBoolSetting("Old render", &oldrdca, &oldrdca);
	registerBoolSetting("notarget", &notarget, notarget);
}
int crystalDelay = 0;
int crystalDelay2 = 0;
int crystalDelay3 = 0;

CrystalAuraWTA::~CrystalAuraWTA() {
}

const char* CrystalAuraWTA::getModuleName() {
	return ("CrystalAuraWTA");
}
static std::vector<C_Entity*> targetList7;

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

void findEntity3(C_Entity* currentEntity, bool isRegularEntity) {
	static auto CrystalAuraWTAMod = moduleMgr->getModule<CrystalAuraWTA>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 71)  // crystal
		return;

	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 319)
		return;
	if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
		return;
	if (currentEntity->getEntityTypeId() == 64)  // item
		return;
	if (currentEntity->getEntityTypeId() == 69)  // xp_orb
		return;
	if (currentEntity->getEntityTypeId() == 80)  // arrow
		return;

	if (!TargetUtil::isValidTarget(currentEntity))
		return;

	//how hard is it to play fair? add back the badman check if its hard

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < CrystalAuraWTAMod->range) {
		targetList7.push_back(currentEntity);
		sort(targetList7.begin(), targetList7.end(), CompareTargetEnArray());
	}
}

bool checkTargCollision(vec3_t* block, C_Entity* ent) {
	std::vector<vec3_t*> corners;
	corners.clear();

	corners.push_back(new vec3_t(ent->aabb.lower.x, ent->aabb.lower.y, ent->aabb.lower.z));
	corners.push_back(new vec3_t(ent->aabb.lower.x, ent->aabb.lower.y, ent->aabb.upper.z));
	corners.push_back(new vec3_t(ent->aabb.upper.x, ent->aabb.lower.y, ent->aabb.upper.z));
	corners.push_back(new vec3_t(ent->aabb.upper.x, ent->aabb.lower.y, ent->aabb.lower.z));
	int n = 0;
	if (!corners.empty())
		for (auto corner : corners) {
			//	DrawUtils::drawText(DrawUtils::worldToScreen(*corners[n]), &std::to_string(n + 1), MC_Color(1.f, 1.f, 1.f));
			//DrawUtils::setColor(1.f, 0.f, 0.f, 1.f);
			//if (g_Data.getLocalPlayer()->region->getBlock(vec3_ti(corners[n]->x, corners[n]->y - 0.5f, corners[n]->z))->toLegacy()->blockId != 0) {
			//DrawUtils::drawBox(vec3_t(floor(corners[n]->x), floor(corners[n]->y - 0.5f), floor(corners[n]->z)), g_Data.getLocalPlayer()->region->getBlock(vec3_ti(corners[n]->x, corners[n]->y - 0.5f, corners[n]->z))->toLegacy()->aabb.upper, 2.f);
			//	DrawUtils::drawBox(vec3_t(floor(corners[n]->x), floor(corners[n]->y - 0.5f), floor(corners[n]->z)), vec3_t(floor(corners[n]->x) + 1.f, floor(corners[n]->y - 0.5f) + 1.f, floor(corners[n]->z) + 1.f), 2.f);
			n++;

			if ((floor(corner->x) == floor(block->x)) && (floor(corner->y) == floor(block->y)) && (floor(corner->z) == floor(block->z))) {
				//	DrawUtils::setColor(1.f, 0.f, 0.f, 0.5f);
				//	DrawUtils::drawBox(block->floor(), {floor(block->x) + 1.f, floor(block->y) + 1.f, floor(block->z) + 1.f}, 0.7f, false);
				return true;
				//	}
			}
		}

	return false;
}

bool checkSurrounded2(C_Entity* ent) {
	vec3_t entPos = ent->getPos()->floor();
	entPos.y -= 1;

	std::vector<vec3_ti*> blockChecks;
	blockChecks.clear();

	if (blockChecks.empty()) {
		blockChecks.push_back(new vec3_ti(entPos.x, entPos.y, entPos.z + 1));
		blockChecks.push_back(new vec3_ti(entPos.x, entPos.y, entPos.z - 1));
		blockChecks.push_back(new vec3_ti(entPos.x + 1, entPos.y, entPos.z));
		blockChecks.push_back(new vec3_ti(entPos.x - 1, entPos.y, entPos.z));
	}

	for (auto blocks : blockChecks) {
		if (!checkTargCollision(&blocks->toVector3(), ent)) {
			return false;
		}
	}
	return true;
}

struct PlacementScore {
	vec3_t* position;
	int score;

	PlacementScore(vec3_t* pos, int scr) : position(pos), score(scr) {}
};

bool compareScores(const PlacementScore& score1, const PlacementScore& score2) {
	return score1.score > score2.score;
}

std::vector<vec3_t*> getGucciPlacement2(C_Entity* ent) {
	vec3_t entPos = ent->getPos()->floor();
	entPos.y -= 1;
	std::vector<PlacementScore> placementScores;

	for (int dz = -1; dz <= 1; dz++) {
		for (int dx = -1; dx <= 1; dx++) {
			vec3_ti checkPos(entPos.x + dx, entPos.y, entPos.z + dz);
			auto blkID = g_Data.getLocalPlayer()->region->getBlock(checkPos)->toLegacy()->blockId;
			auto blkIDL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(checkPos.x, checkPos.y - 1, checkPos.z))->toLegacy()->blockId;
			auto blkIDLL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(checkPos.x, checkPos.y - 2, checkPos.z))->toLegacy()->blockId;
			auto blkIDLLL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(checkPos.x, checkPos.y - 3, checkPos.z))->toLegacy()->blockId;
			auto blkIDLLLL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(checkPos.x, checkPos.y - 4, checkPos.z))->toLegacy()->blockId;

			int score = 0;
			if (blkID == 0 && blkIDL == 0 && (blkIDLL == 49 || blkIDLL == 7))
				score += 4;
			else if (blkID == 0 && (blkIDL == 7 || blkIDL == 49))
				score += 3;
			else if (blkID == 0 && blkIDL == 0 && blkIDLL == 0 && (blkIDLLL == 7 || blkIDLLL == 49))
				score += 2;
			else if (blkID == 0 && blkIDL == 0 && blkIDLL == 0 && blkIDLLL == 0 && (blkIDLLLL == 7 || blkIDLLLL == 49))
				score += 1;

			if (score > 0)
				placementScores.emplace_back(new vec3_t(checkPos.x, checkPos.y - score, checkPos.z), score);
		}
	}

	if (placementScores.empty()) {
		for (int dz = -2; dz <= 2; dz++) {
			for (int dx = -2; dx <= 2; dx++) {
				int y = entPos.y;
				vec3_ti checkPos(entPos.x + dx, y, entPos.z + dz);
				auto blk = g_Data.getLocalPlayer()->region->getBlock(checkPos)->toLegacy()->blockId;
				auto lBlk = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(checkPos.x, checkPos.y - 1, checkPos.z))->toLegacy()->blockId;

				if (blk == 0 && (lBlk == 49 || lBlk == 7))
					placementScores.emplace_back(new vec3_t(checkPos.x, y, checkPos.z), 1);
			}
		}
	}

	std::sort(placementScores.begin(), placementScores.end(), compareScores);

	std::vector<vec3_t*> finalBlocks;
	for (const auto& placement : placementScores)
		finalBlocks.push_back(placement.position);

	return finalBlocks;
}



bool hasPlaced = false;
void CrystalAuraWTA::onEnable() {
	crystalDelay = 0;
	hasPlaced = false;
}
vec3_t espPosLower;
vec3_t espPosUpper;
vec3_t crystalPos;
std::vector<vec3_t*> placeArr;
//std::vector<vec3_t*> hitArr;

void findCr() {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if (stack->getItem()->itemId == 637) {  // select crystal
				supplies->selectedHotbarSlot = n;
				//return true;
				return;
			}
		}
	}
	//return false;
}
void CrystalAuraWTA::onTick(C_GameMode* gm) {
	{
		if (g_Data.getLocalPlayer() == nullptr) return;
		if (isClick && !g_Data.isRightClickDown()) return;

		//	if (g_Data.getLocalPlayer()->getSelectedItemId() == 259) return;

		targetList7.clear();

		g_Data.forEachEntity(findEntity3);
		//hitArr.clear();
		//placeArr.clear();

		if (autoplace)
			if ((crystalDelay >= this->delay) && !(targetList7.empty())) {
				crystalDelay = 0;
				if (!checkSurrounded2(targetList7[0])) {
					std::vector<vec3_t*> gucciPositions = getGucciPlacement2(targetList7[0]);

					auto supplies = g_Data.getLocalPlayer()->getSupplies();
					auto inv = supplies->inventory;
					slotCA = supplies->selectedHotbarSlot;
					C_ItemStack* item = supplies->inventory->getItemStack(0);

					//615 = normal id for crystal || 616 = crystal id for nukkit servers
					if (!gucciPositions.empty()) {
					
						if (g_Data.getLocalPlayer()->getSelectedItemId() == 637) {
							placeArr.clear();
							for (auto place : gucciPositions) {
								int slotab = 0;
								C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
								C_Inventory* inv = supplies->inventory;
								slotab = supplies->selectedHotbarSlot;
								for (int n = 0; n < 9; n++) {
									C_ItemStack* stack = inv->getItemStack(n);
									if (stack->item != nullptr) {
										if (stack->getItem()->itemId == 637) { // itemid == 146
											supplies->selectedHotbarSlot = n;
											break;
										}
									}
								}
								//								if (hasPlaced && !doMultiple) break;
								if (targetList7.empty()) return;
								gm->buildBlock(&vec3_ti(place->x, place->y - 1, place->z), 2);
								gm->buildBlock(&vec3_ti(place->x, place->y, place->z), 2);
								gm->buildBlock(&vec3_ti(place->x, place->y + 1, place->z), 2);
								placeArr.push_back(new vec3_t(place->x, place->y - 1, place->z));
								hasPlaced = true;
								supplies->selectedHotbarSlot = slotab;
							}
						}
						
					}

					gucciPositions.clear();
				}
			}
			else if (!targetList7.empty()) {
				crystalDelay++;
			}

		//if (crystalDelay2 >= 20) {
		//		hasPlaced = false;
		//}

		g_Data.forEachEntity([](C_Entity* ent, bool b) {
			if (targetList7.empty()) return;
			int id = ent->getEntityTypeId();
			int range = moduleMgr->getModule<CrystalAuraWTA>()->range;
			if (id == 71 && g_Data.getLocalPlayer()->getPos()->dist(*ent->getPos()) <= range) {
				g_Data.getCGameMode()->attack(ent);
				hasPlaced = false;

				if (!moduleMgr->getModule<NoSwing>()->isEnabled())
					g_Data.getLocalPlayer()->swingArm();
			}
			});  //*/
	}
}

void CrystalAuraWTA::onDisable() {
	crystalDelay = 0;
	hasPlaced = false;
}
/*
*
* //this right here is stuff i was working on but havent been bothered to finish*/

//*/
void CrystalAuraWTA::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (renderCA) {
		auto interfacrColor = ColorUtil::interfaceColor(1);
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		if (localPlayer != nullptr && GameData::canUseMoveKeys()) {
			if (!targetList7.empty()) {
				if (!placeArr.empty()) {
					for (auto postt : placeArr) {
						DrawUtils::drawwtf(*postt, 0.5f);
						DrawUtils::setColor(interfacrColor.r, interfacrColor.g, interfacrColor.b, 1.f);
						if (!oldrdca) {
							DrawUtils::drawBox(postt->floor().add(0.f, 0.999f, 0.f), vec3_t(floor(postt->x) + 1.f, floor(postt->y) + 1.f, floor(postt->z) + 1.f), 0.5f, true);
						}
						else
						{
							DrawUtils::drawBox(postt->floor(), vec3_t(floor(postt->x) + 1.f, floor(postt->y) + 1.f, floor(postt->z) + 1.f), 0.5f, true);
						}
					}
				}
			}
			/*
			if (!hitArr.empty()) {
				for (auto postt : hitArr) {
					DrawUtils::setColor(interfacrColor.r, interfacrColor.g, interfacrColor.b, 1.f);
					DrawUtils::drawBox(postt->floor(), vec3_t(floor(postt->x) + 1.f, floor(postt->y) + 1.f, floor(postt->z) + 1.f), 0.5f, true);
				}
			}  //*/
		}
	}

}
