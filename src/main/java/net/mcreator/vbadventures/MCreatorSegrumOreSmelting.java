package net.mcreator.vbadventures;

import net.minecraftforge.fml.common.registry.GameRegistry;
import net.minecraftforge.fml.common.event.FMLInitializationEvent;

import net.minecraft.item.ItemStack;

@Elementsvbadventures.ModElement.Tag
public class MCreatorSegrumOreSmelting extends Elementsvbadventures.ModElement {
	public MCreatorSegrumOreSmelting(Elementsvbadventures instance) {
		super(instance, 14);
	}

	@Override
	public void init(FMLInitializationEvent event) {
		GameRegistry.addSmelting(new ItemStack(MCreatorSegrumOre.block, (int) (1)), new ItemStack(MCreatorSegrumIngot.block, (int) (1)),
				1.6099999999999999F);
	}
}
