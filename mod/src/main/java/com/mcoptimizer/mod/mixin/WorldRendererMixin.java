// MinecraftMobileOptimizer/mod/src/main/java/com/mcoptimizer/mod/mixin/WorldRendererMixin.java
package com.mcoptimizer.mod.mixin;

import com.mcoptimizer.mod.FPSBoosterMod;
import net.minecraft.client.render.WorldRenderer;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.ModifyVariable;

@Mixin(WorldRenderer.class)
public class WorldRendererMixin {
    
    @ModifyVariable(
        method = "render",
        at = @At("HEAD"),
        ordinal = 0,
        argsOnly = true
    )
    private boolean modifyRenderBlockOutline(boolean renderBlockOutline) {
        if (FPSBoosterMod.getInstance().getOptimizer().isAggressiveMode()) {
            return false;
        }
        return renderBlockOutline;
    }
}
