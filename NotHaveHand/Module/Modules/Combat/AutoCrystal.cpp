#include "AutoCrystal.h"
//#include "../pch.h"

using namespace std;
AutoCrystal::AutoCrystal() : IModule(0, Category::PLAYER, "Auto put some item in hotbar : Dev by tony skidded ofc") {
	/*
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Normal", 0);
	mode.addEntry("Inventory", 1);
	*/
	registerBoolSetting("Gapple", &gapplehb, gapplehb);
	registerIntSetting("Gapple slot", &gappleSlot, gappleSlot, 1, 9);

	registerBoolSetting("Obsidian", &obsidianhb, obsidianhb);
	registerIntSetting("Obsidian slot", &obsidianSlot, obsidianSlot, 1, 9);

	registerBoolSetting("Crystal", &crystalhb, crystalhb);
	registerIntSetting("Crystal slot", &crystalSlot, crystalSlot, 1, 9);

	registerBoolSetting("Anvil", &anvilhb, anvilhb);
	registerIntSetting("Anvil slot", &anvilSlot, anvilSlot, 1, 9);

	registerBoolSetting("Button", &Buttonhb, Buttonhb);
	registerIntSetting("Button slot", &ButtonSlot, ButtonSlot, 1, 9);

	//registerBoolSetting("Pickaxe", &Pickaxehb, Pickaxehb);
	//registerIntSetting("Pickaxe slot", &PickaxeSlot, PickaxeSlot, 1, 9);

	registerBoolSetting("Sword", &Swordhb, Swordhb);
	registerIntSetting("Sword slot", &SwordSlot, SwordSlot, 1, 9);

	registerBoolSetting("wood", &woodhb, woodhb);
	registerIntSetting("wood slot", &woodSlot, woodSlot, 1, 9);


	registerBoolSetting("No delay", &Nodelay, Nodelay);
}
const char* AutoCrystal::getRawModuleName() {
	return "AutoHotbar";
}

const char* AutoCrystal::getModuleName() {
	return("AutoHorbar");
}


void AutoCrystal::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	/*
	if (!player->canOpenContainerScreen() && mode.getSelectedValue() == 0) return;
	if (player->canOpenContainerScreen() && mode.getSelectedValue() == 1) return;
	*/ // Ncc

	/*
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	int realslot = crystalSlot - 1;
	C_ItemStack* wtf = inv->getItemStack(realslot);
	if (wtf->item != nullptr) {
		if (wtf->getItem()->itemId != 637) {
			for (int n = 0; n < 36; n++) {
				C_ItemStack* stack = inv->getItemStack(n);
				if (stack->item != nullptr) {
					if (stack->getItem()->itemId == 637) {
						inv->swapSlots(n, realslot);
						break;
					}
				}
			}
		}
	}
	else
	{
		for (int n = 0; n < 36; n++) {
			C_ItemStack* stack = inv->getItemStack(n);
			if (stack->item != nullptr) {
				if (stack->getItem()->itemId == 637) {
					inv->swapSlots(n, realslot);
					break;
				}
			}
		}
	}
	*/
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	int realgappleSlot = gappleSlot - 1;
	int realobsidianSlot = obsidianSlot - 1;
	int realcrystalSlot = crystalSlot - 1;
	int realanvilSlot = anvilSlot - 1;
	int realButtonSlot = ButtonSlot - 1;
	int realSwordSlot = SwordSlot - 1;
	int realwoodSlot = woodSlot - 1;
	//int realPickaxeSlot = SwordSlot - 1;

	dagapple = false;
	daob = false;
	dacry = false;
	daanvil = false;
	dabut = false;
	daSword = false;
	dawood = false;
	//daPickaxe = false;

	for (int n = 0; n < 36; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (gapplehb) {
			if (!dagapple) {
				C_ItemStack* gappleitem = inv->getItemStack(realgappleSlot);
				if (gappleitem->item != nullptr) {
					if (gappleitem->getItem()->itemId != 259) {
						if (stack->item != nullptr) {
							if (stack->getItem()->itemId == 259) {
								if (!Nodelay) {
									inv->swapSlots(n, realgappleSlot);
								}
								else
								{
									inv->setItem(realgappleSlot, *stack);
									inv->removeItem(n, stack->count);
								}

								//inv->swapSlots(n, realgappleSlot);
								dagapple = true;
							}
						}
					}
				}
				else
				{
					if (stack->item != nullptr) {
						if (stack->getItem()->itemId == 259) {
							if (!Nodelay) {
								inv->swapSlots(n, realgappleSlot);
							}
							else
							{
								inv->setItem(realgappleSlot, *stack);
								inv->removeItem(n, stack->count);
							}

							//inv->swapSlots(n, realgappleSlot);
							dagapple = true;
						}
					}
				}
			}
		}

		if (obsidianhb) {
			if (!daob) {
				C_ItemStack* obsidianitem = inv->getItemStack(realobsidianSlot);
				if (obsidianitem->item != nullptr) {
					if (obsidianitem->getItem()->itemId != 49) {
						if (stack->item != nullptr) {
							if (stack->getItem()->itemId == 49) {
								if (!Nodelay) {
									inv->swapSlots(n, realobsidianSlot);
								}
								else
								{
									inv->setItem(realobsidianSlot, *stack);
									inv->removeItem(n, stack->count);
								}

								//inv->swapSlots(n, realobsidianSlot);
								daob = true;
							}
						}
					}
				}
				else
				{
					if (stack->item != nullptr) {
						if (stack->getItem()->itemId == 49) {
							if (!Nodelay) {
								inv->swapSlots(n, realobsidianSlot);
							}
							else
							{
								inv->setItem(realobsidianSlot, *stack);
								inv->removeItem(n, stack->count);
							}

							//inv->swapSlots(n, realobsidianSlot);
							daob = true;
						}
					}
				}
			}
		}

		if (crystalhb) {
			if (!dacry) {
				C_ItemStack* crystalitem = inv->getItemStack(realcrystalSlot);
				if (crystalitem->item != nullptr) {
					if (crystalitem->getItem()->itemId != 637) {
						if (stack->item != nullptr) {
							if (stack->getItem()->itemId == 637) {
								if (!Nodelay) {
									inv->swapSlots(n, realcrystalSlot);
								}
								else
								{
									inv->setItem(realcrystalSlot, *stack);
									inv->removeItem(n, stack->count);
								}

								//inv->setItem(realcrystalSlot, *stack);
								//inv->removeItem(n, n);
								//inv->swapSlots(n, realcrystalSlot);
								dacry = true;
							}
						}
					}
				}
				else
				{
					if (stack->item != nullptr) {
						if (stack->getItem()->itemId == 637) {
							if (!Nodelay) {
								inv->swapSlots(n, realcrystalSlot);
							}
							else
							{
								inv->setItem(realcrystalSlot, *stack);
								inv->removeItem(n, stack->count);
							}

							//inv->setItem(realcrystalSlot, *stack);
							//inv->removeItem(n, n);
							//inv->swapSlots(n, realcrystalSlot);
							dacry = true;
						}
					}
				}
			}
		}
		if (anvilhb) {
			if (!daanvil) {
				C_ItemStack* anvilitem = inv->getItemStack(realanvilSlot);
				if (anvilitem->item != nullptr) {
					if (anvilitem->getItem()->itemId != 145) {
						if (stack->item != nullptr) {
							if (stack->getItem()->itemId == 145) {
								if (!Nodelay) {
									inv->swapSlots(n, realanvilSlot);
								}
								else
								{
									inv->setItem(realanvilSlot, *stack);
									inv->removeItem(n, stack->count);
								}

								//inv->swapSlots(n, realobsidianSlot);
								daanvil = true;
							}
						}
					}
				}
				else
				{
					if (stack->item != nullptr) {
						if (stack->getItem()->itemId == 145) {
							if (!Nodelay) {
								inv->swapSlots(n, realanvilSlot);
							}
							else
							{
								inv->setItem(realanvilSlot, *stack);
								inv->removeItem(n, stack->count);
							}

							//inv->swapSlots(n, realobsidianSlot);
							daanvil = true;
						}
					}
				}
			}
		}
		if (Buttonhb) {
			if (!dabut) {
				C_ItemStack* Buttonitem = inv->getItemStack(realButtonSlot);
				if (Buttonitem->item != nullptr) {
					if (Buttonitem->getItem()->itemId != 77) {
						if (stack->item != nullptr) {
							if (stack->getItem()->itemId == 77) {
								if (!Nodelay) {
									inv->swapSlots(n, realButtonSlot);
								}
								else
								{
									inv->setItem(realButtonSlot, *stack);
									inv->removeItem(n, stack->count);
								}

								//inv->swapSlots(n, realobsidianSlot);
								dabut = true;
							}
						}
					}
				}
				else
				{
					if (stack->item != nullptr) {
						if (stack->getItem()->itemId == 77) {
							if (!Nodelay) {
								inv->swapSlots(n, realButtonSlot);
							}
							else
							{
								inv->setItem(realButtonSlot, *stack);
								inv->removeItem(n, stack->count);
							}

							//inv->swapSlots(n, realobsidianSlot);
							dabut = true;
						}
					}
				}
			}
		}
		if (Swordhb) {
			if (!daSword) {
				C_ItemStack* Sworditem = inv->getItemStack(realSwordSlot);
				if (Sworditem->item != nullptr) {
					if (Sworditem->getItem()->itemId != 316) {
						if (stack->item != nullptr) {
							if (stack->getItem()->itemId == 316) {
								if (!Nodelay) {
									inv->swapSlots(n, realSwordSlot);
								}
								else
								{
									inv->setItem(realSwordSlot, *stack);
									inv->removeItem(n, stack->count);
								}

								//inv->swapSlots(n, realobsidianSlot);
								daSword = true;
							}
						}
					}
				}
				else
				{
					if (stack->item != nullptr) {
						if (stack->getItem()->itemId == 316) {
							if (!Nodelay) {
								inv->swapSlots(n, realSwordSlot);
							}
							else
							{
								inv->setItem(realSwordSlot, *stack);
								inv->removeItem(n, stack->count);
							}

							//inv->swapSlots(n, realobsidianSlot);
							daSword = true;
						}
					}
				}
			}
		}
		if (woodhb) {
			if (!dawood) {
				C_ItemStack* wooditem = inv->getItemStack(realwoodSlot);
				if (wooditem->item != nullptr) {
					if (wooditem->getItem()->itemId != 5) {
						if (stack->item != nullptr) {
							if (stack->getItem()->itemId == 5) {
								if (!Nodelay) {
									inv->swapSlots(n, realwoodSlot);
								}
								else
								{
									inv->setItem(realwoodSlot, *stack);
									inv->removeItem(n, stack->count);
								}

								//inv->swapSlots(n, realobsidianSlot);
								dawood = true;
							}
						}
					}
				}
				else
				{
					if (stack->item != nullptr) {
						if (stack->getItem()->itemId == 5) {
							if (!Nodelay) {
								inv->swapSlots(n, realwoodSlot);
							}
							else
							{
								inv->setItem(realwoodSlot, *stack);
								inv->removeItem(n, stack->count);
							}

							//inv->swapSlots(n, realobsidianSlot);
							dawood = true;
						}
					}
				}
			}
		}


	}
}
