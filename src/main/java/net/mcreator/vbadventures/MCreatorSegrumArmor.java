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
public class MCreatorSegrumArmor extends Elementsvbadventures.ModElement {
	@GameRegistry.ObjectHolder("vbadventures:segrumarmorhelmet")
	public static final Item helmet = null;
	@GameRegistry.ObjectHolder("vbadventures:segrumarmorbody")
	public static final Item body = null;
	@GameRegistry.ObjectHolder("vbadventures:segrumarmorlegs")
	public static final Item legs = null;
	@GameRegistry.ObjectHolder("vbadventures:segrumarmorboots")
	public static final Item boots = null;

	public MCreatorSegrumArmor(Elementsvbadventures instance) {
		super(instance, 11);
	}

	@Override
	public void initElements() {
		ItemArmor.ArmorMaterial enuma = EnumHelper.addArmorMaterial("SEGRUMARMOR", "vbadventures:segrum", 35, new int[]{5, 14, 12, 5}, 21,
				(net.minecraft.util.SoundEvent) net.minecraft.util.SoundEvent.REGISTRY.getObject(new ResourceLocation("")), 0f);
		elements.items.add(() -> new ItemArmor(enuma, 0, EntityEquipmentSlot.HEAD).setUnlocalizedName("segrumarmorhelmet")
				.setRegistryName("segrumarmorhelmet").setCreativeTab(MCreatorVBArmors.tab));
		elements.items.add(() -> new ItemArmor(enuma, 0, EntityEquipmentSlot.CHEST).setUnlocalizedName("segrumarmorbody")
				.setRegistryName("segrumarmorbody").setCreativeTab(MCreatorVBArmors.tab));
		elements.items.add(() -> new ItemArmor(enuma, 0, EntityEquipmentSlot.LEGS).setUnlocalizedName("segrumarmorlegs")
				.setRegistryName("segrumarmorlegs").setCreativeTab(MCreatorVBArmors.tab));
		elements.items.add(() -> new ItemArmor(enuma, 0, EntityEquipmentSlot.FEET).setUnlocalizedName("segrumarmorboots")
				.setRegistryName("segrumarmorboots").setCreativeTab(MCreatorVBArmors.tab));
	}

	@SideOnly(Side.CLIENT)
	@Override
	public void registerModels(ModelRegistryEvent event) {
		ModelLoader.setCustomModelResourceLocation(helmet, 0, new ModelResourceLocation("vbadventures:segrumarmorhelmet", "inventory"));
		ModelLoader.setCustomModelResourceLocation(body, 0, new ModelResourceLocation("vbadventures:segrumarmorbody", "inventory"));
		ModelLoader.setCustomModelResourceLocation(legs, 0, new ModelResourceLocation("vbadventures:segrumarmorlegs", "inventory"));
		ModelLoader.setCustomModelResourceLocation(boots, 0, new ModelResourceLocation("vbadventures:segrumarmorboots", "inventory"));
	}
}
