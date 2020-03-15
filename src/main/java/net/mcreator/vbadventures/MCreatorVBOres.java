package net.mcreator.vbadventures;

import net.minecraftforge.fml.relauncher.SideOnly;
import net.minecraftforge.fml.relauncher.Side;

import net.minecraft.item.ItemStack;
import net.minecraft.creativetab.CreativeTabs;

@Elementsvbadventures.ModElement.Tag
public class MCreatorVBOres extends Elementsvbadventures.ModElement {
	public MCreatorVBOres(Elementsvbadventures instance) {
		super(instance, 29);
	}

	@Override
	public void initElements() {
		tab = new CreativeTabs("tabvbores") {
			@SideOnly(Side.CLIENT)
			@Override
			public ItemStack getTabIconItem() {
				return new ItemStack(MCreatorSegrumIngot.block, (int) (1));
			}

			@SideOnly(Side.CLIENT)
			public boolean hasSearchBar() {
				return false;
			}
		};
	}
	public static CreativeTabs tab;
}
