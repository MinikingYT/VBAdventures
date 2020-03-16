package net.mcreator.vbadventures;

import net.minecraftforge.fml.relauncher.SideOnly;
import net.minecraftforge.fml.relauncher.Side;

import net.minecraft.item.ItemStack;
import net.minecraft.creativetab.CreativeTabs;

@Elementsvbadventures.ModElement.Tag
public class MCreatorVBAdventureMisc extends Elementsvbadventures.ModElement {
	public MCreatorVBAdventureMisc(Elementsvbadventures instance) {
		super(instance, 64);
	}

	@Override
	public void initElements() {
		tab = new CreativeTabs("tabvbadventuremisc") {
			@SideOnly(Side.CLIENT)
			@Override
			public ItemStack getTabIconItem() {
				return new ItemStack(MCreatorSegrumHandle.block, (int) (1));
			}

			@SideOnly(Side.CLIENT)
			public boolean hasSearchBar() {
				return false;
			}
		};
	}
	public static CreativeTabs tab;
}
