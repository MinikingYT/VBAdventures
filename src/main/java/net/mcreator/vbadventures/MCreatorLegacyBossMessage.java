package net.mcreator.vbadventures;

import net.minecraftforge.fml.common.FMLCommonHandler;

import net.minecraft.util.text.TextComponentString;
import net.minecraft.server.MinecraftServer;

@Elementsvbadventures.ModElement.Tag
public class MCreatorLegacyBossMessage extends Elementsvbadventures.ModElement {
	public MCreatorLegacyBossMessage(Elementsvbadventures instance) {
		super(instance, 71);
	}

	public static void executeProcedure(java.util.HashMap<String, Object> dependencies) {
		{
			MinecraftServer mcserv = FMLCommonHandler.instance().getMinecraftServerInstance();
			if (mcserv != null)
				mcserv.getPlayerList().sendMessage(new TextComponentString("The Legacy has begun!"));
		}
	}
}
