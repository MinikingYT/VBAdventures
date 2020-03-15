package net.mcreator.vbadventures;

import net.minecraftforge.fml.relauncher.SideOnly;
import net.minecraftforge.fml.relauncher.Side;

import net.minecraft.item.ItemStack;
import net.minecraft.init.Blocks;
import net.minecraft.creativetab.CreativeTabs;

@Elementsvbadventures.ModElement.Tag
public class MCreatorVBArmors extends Elementsvbadventures.ModElement {
	public MCreatorVBArmors(Elementsvbadventures instance) {
		super(instance, 26);
	}

	@Override
	public void initElements() {
		tab = new CreativeTabs("tabvbarmors") {
			@SideOnly(Side.CLIENT)
			@Override
			public ItemStack getTabIconItem() {
				return new ItemStack(Blocks.AIR, (int) (1));
			}

			@SideOnly(Side.CLIENT)
			public boolean hasSearchBar() {
				return false;
			}
		};
	}
	public static CreativeTabs tab;
}
