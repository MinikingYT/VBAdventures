package net.mcreator.vbadventures;

import net.minecraftforge.fml.relauncher.SideOnly;
import net.minecraftforge.fml.relauncher.Side;
import net.minecraftforge.fml.common.registry.GameRegistry;
import net.minecraftforge.common.util.EnumHelper;
import net.minecraftforge.client.model.ModelLoader;
import net.minecraftforge.client.event.ModelRegistryEvent;

import net.minecraft.util.ResourceLocation;
import net.minecraft.item.ItemArmor;
import net.minecraft.item.Item;
import net.minecraft.inventory.EntityEquipmentSlot;
import net.minecraft.client.renderer.block.model.ModelResourceLocation;

@Elementsvbadventures.ModElement.Tag
public class MCreatorEbriteArmor extends Elementsvbadventures.ModElement {
	@GameRegistry.ObjectHolder("vbadventures:ebritearmorhelmet")
	public static final Item helmet = null;
	@GameRegistry.ObjectHolder("vbadventures:ebritearmorbody")
	public static final Item body = null;
	@GameRegistry.ObjectHolder("vbadventures:ebritearmorlegs")
	public static final Item legs = null;
	@GameRegistry.ObjectHolder("vbadventures:ebritearmorboots")
	public static final Item boots = null;

	public MCreatorEbriteArmor(Elementsvbadventures instance) {
		super(instance, 49);
	}

	@Override
	public void initElements() {
		ItemArmor.ArmorMaterial enuma = EnumHelper.addArmorMaterial("EBRITEARMOR", "vbadventures:ebrite", 40, new int[]{8, 18, 20, 8}, 27,
				(net.minecraft.util.SoundEvent) net.minecraft.util.SoundEvent.REGISTRY.getObject(new ResourceLocation("")), 0f);
		elements.items.add(() -> new ItemArmor(enuma, 0, EntityEquipmentSlot.HEAD).setUnlocalizedName("ebritearmorhelmet")
				.setRegistryName("ebritearmorhelmet").setCreativeTab(MCreatorVBArmors.tab));
		elements.items.add(() -> new ItemArmor(enuma, 0, EntityEquipmentSlot.CHEST).setUnlocalizedName("ebritearmorbody")
				.setRegistryName("ebritearmorbody").setCreativeTab(MCreatorVBArmors.tab));
		elements.items.add(() -> new ItemArmor(enuma, 0, EntityEquipmentSlot.LEGS).setUnlocalizedName("ebritearmorlegs")
				.setRegistryName("ebritearmorlegs").setCreativeTab(MCreatorVBArmors.tab));
		elements.items.add(() -> new ItemArmor(enuma, 0, EntityEquipmentSlot.FEET).setUnlocalizedName("ebritearmorboots")
				.setRegistryName("ebritearmorboots").setCreativeTab(MCreatorVBArmors.tab));
	}

	@SideOnly(Side.CLIENT)
	@Override
	public void registerModels(ModelRegistryEvent event) {
		ModelLoader.setCustomModelResourceLocation(helmet, 0, new ModelResourceLocation("vbadventures:ebritearmorhelmet", "inventory"));
		ModelLoader.setCustomModelResourceLocation(body, 0, new ModelResourceLocation("vbadventures:ebritearmorbody", "inventory"));
		ModelLoader.setCustomModelResourceLocation(legs, 0, new ModelResourceLocation("vbadventures:ebritearmorlegs", "inventory"));
		ModelLoader.setCustomModelResourceLocation(boots, 0, new ModelResourceLocation("vbadventures:ebritearmorboots", "inventory"));
	}
}
