package net.mcreator.vbadventures;

import net.minecraftforge.fml.relauncher.SideOnly;
import net.minecraftforge.fml.relauncher.Side;
import net.minecraftforge.fml.common.registry.GameRegistry;
import net.minecraftforge.client.model.ModelLoader;
import net.minecraftforge.client.event.ModelRegistryEvent;

import net.minecraft.item.ItemBlock;
import net.minecraft.item.Item;
import net.minecraft.client.renderer.block.model.ModelResourceLocation;
import net.minecraft.block.material.Material;
import net.minecraft.block.SoundType;
import net.minecraft.block.Block;

@Elementsvbadventures.ModElement.Tag
public class MCreatorSegrumOreBlock extends Elementsvbadventures.ModElement {
	@GameRegistry.ObjectHolder("vbadventures:segrumoreblock")
	public static final Block block = null;

	public MCreatorSegrumOreBlock(Elementsvbadventures instance) {
		super(instance, 2);
	}

	@Override
	public void initElements() {
		elements.blocks.add(() -> new BlockCustom());
		elements.items.add(() -> new ItemBlock(block).setRegistryName(block.getRegistryName()));
	}

	@SideOnly(Side.CLIENT)
	@Override
	public void registerModels(ModelRegistryEvent event) {
		ModelLoader.setCustomModelResourceLocation(Item.getItemFromBlock(block), 0, new ModelResourceLocation("vbadventures:segrumoreblock",
				"inventory"));
	}

	public static class BlockCustom extends Block {
		public BlockCustom() {
			super(Material.IRON);
			setRegistryName("segrumoreblock");
			setUnlocalizedName("segrumoreblock");
			setSoundType(SoundType.METAL);
			setHarvestLevel("pickaxe", 5);
			setHardness(5F);
			setResistance(10F);
			setLightLevel(0F);
			setLightOpacity(255);
			setCreativeTab(MCreatorVBOres.tab);
		}
	}
}
