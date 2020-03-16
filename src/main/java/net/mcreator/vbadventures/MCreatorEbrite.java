package net.mcreator.vbadventures;

import net.minecraftforge.oredict.OreDictionary;
import net.minecraftforge.fml.common.event.FMLInitializationEvent;

import net.minecraft.item.ItemStack;

@Elementsvbadventures.ModElement.Tag
public class MCreatorEbrite extends Elementsvbadventures.ModElement {
	public MCreatorEbrite(Elementsvbadventures instance) {
		super(instance, 57);
	}

	@Override
	public void init(FMLInitializationEvent event) {
		OreDictionary.registerOre("ebrite", new ItemStack(MCreatorEbriteIngot.block, (int) (1)));
		OreDictionary.registerOre("ebrite", new ItemStack(MCreatorEbritePickaxe.block, (int) (1)));
		OreDictionary.registerOre("ebrite", new ItemStack(MCreatorEbriteOreBlock.block, (int) (1)));
		OreDictionary.registerOre("ebrite", new ItemStack(MCreatorEbriteOre.block, (int) (1)));
		OreDictionary.registerOre("ebrite", new ItemStack(MCreatorEbriteAxe.block, (int) (1)));
		OreDictionary.registerOre("ebrite", new ItemStack(MCreatorEbriteSword.block, (int) (1)));
		OreDictionary.registerOre("ebrite", new ItemStack(MCreatorEbriteShovel.block, (int) (1)));
		OreDictionary.registerOre("ebrite", new ItemStack(MCreatorEbriteHoe.block, (int) (1)));
		OreDictionary.registerOre("ebrite", new ItemStack(MCreatorEbriteArmor.helmet, (int) (1)));
		OreDictionary.registerOre("ebrite", new ItemStack(MCreatorEbriteArmor.body, (int) (1)));
		OreDictionary.registerOre("ebrite", new ItemStack(MCreatorEbriteArmor.legs, (int) (1)));
		OreDictionary.registerOre("ebrite", new ItemStack(MCreatorEbriteArmor.boots, (int) (1)));
		OreDictionary.registerOre("ebrite", new ItemStack(MCreatorEbriteHandle.block, (int) (1)));
	}
}
