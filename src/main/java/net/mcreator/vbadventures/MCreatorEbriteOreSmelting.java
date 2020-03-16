package net.mcreator.vbadventures;

import net.minecraftforge.fml.common.registry.GameRegistry;
import net.minecraftforge.fml.common.event.FMLInitializationEvent;

import net.minecraft.item.ItemStack;

@Elementsvbadventures.ModElement.Tag
public class MCreatorEbriteOreSmelting extends Elementsvbadventures.ModElement {
	public MCreatorEbriteOreSmelting(Elementsvbadventures instance) {
		super(instance, 38);
	}

	@Override
	public void init(FMLInitializationEvent event) {
		GameRegistry.addSmelting(new ItemStack(MCreatorEbriteOre.block, (int) (1)), new ItemStack(MCreatorEbriteIngot.block, (int) (1)),
				2.0999999999999996F);
	}
}
