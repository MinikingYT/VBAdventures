package net.mcreator.vbadventures;

import net.minecraftforge.fml.relauncher.SideOnly;
import net.minecraftforge.fml.relauncher.Side;
import net.minecraftforge.fml.common.registry.GameRegistry;
import net.minecraftforge.common.util.EnumHelper;
import net.minecraftforge.client.model.ModelLoader;
import net.minecraftforge.client.event.ModelRegistryEvent;

import net.minecraft.item.ItemStack;
import net.minecraft.item.ItemSpade;
import net.minecraft.item.Item;
import net.minecraft.client.renderer.block.model.ModelResourceLocation;

import java.util.Set;
import java.util.HashMap;

@Elementsvbadventures.ModElement.Tag
public class MCreatorSegrumShovel extends Elementsvbadventures.ModElement {
	@GameRegistry.ObjectHolder("vbadventures:segrumshovel")
	public static final Item block = null;

	public MCreatorSegrumShovel(Elementsvbadventures instance) {
		super(instance, 8);
	}

	@Override
	public void initElements() {
		elements.items.add(() -> new ItemSpade(EnumHelper.addToolMaterial("SEGRUMSHOVEL", 5, 802, 10f, 1f, 32)) {
			{
				this.attackSpeed = -3f;
			}

			public Set<String> getToolClasses(ItemStack stack) {
				HashMap<String, Integer> ret = new HashMap<String, Integer>();
				ret.put("spade", 5);
				return ret.keySet();
			}
		}.setUnlocalizedName("segrumshovel").setRegistryName("segrumshovel").setCreativeTab(MCreatorVBTools.tab));
	}

	@SideOnly(Side.CLIENT)
	@Override
	public void registerModels(ModelRegistryEvent event) {
		ModelLoader.setCustomModelResourceLocation(block, 0, new ModelResourceLocation("vbadventures:segrumshovel", "inventory"));
	}
}
