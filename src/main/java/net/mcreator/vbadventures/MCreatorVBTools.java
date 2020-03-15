package net.mcreator.vbadventures;

import net.minecraftforge.fml.relauncher.SideOnly;
import net.minecraftforge.fml.relauncher.Side;

import net.minecraft.item.ItemStack;
import net.minecraft.creativetab.CreativeTabs;

@Elementsvbadventures.ModElement.Tag
public class MCreatorVBTools extends Elementsvbadventures.ModElement {
	public MCreatorVBTools(Elementsvbadventures instance) {
		super(instance, 27);
	}

	@Override
	public void initElements() {
		tab = new CreativeTabs("tabvbtools") {
			@SideOnly(Side.CLIENT)
			@Override
			public ItemStack getTabIconItem() {
				return new ItemStack(MCreatorSegrumPickaxe.block, (int) (1));
			}

			@SideOnly(Side.CLIENT)
			public boolean hasSearchBar() {
				return false;
			}
		};
	}
	public static CreativeTabs tab;
}
