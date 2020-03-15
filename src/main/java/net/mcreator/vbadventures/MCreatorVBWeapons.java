package net.mcreator.vbadventures;

import net.minecraftforge.fml.relauncher.SideOnly;
import net.minecraftforge.fml.relauncher.Side;

import net.minecraft.item.ItemStack;
import net.minecraft.creativetab.CreativeTabs;

@Elementsvbadventures.ModElement.Tag
public class MCreatorVBWeapons extends Elementsvbadventures.ModElement {
	public MCreatorVBWeapons(Elementsvbadventures instance) {
		super(instance, 28);
	}

	@Override
	public void initElements() {
		tab = new CreativeTabs("tabvbweapons") {
			@SideOnly(Side.CLIENT)
			@Override
			public ItemStack getTabIconItem() {
				return new ItemStack(MCreatorSegrumSword.block, (int) (1));
			}

			@SideOnly(Side.CLIENT)
			public boolean hasSearchBar() {
				return false;
			}
		};
	}
	public static CreativeTabs tab;
}
