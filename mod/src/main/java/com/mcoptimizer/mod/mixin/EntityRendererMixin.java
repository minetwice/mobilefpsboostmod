// MinecraftMobileOptimizer/mod/src/main/java/com/mcoptimizer/mod/mixin/EntityRendererMixin.java
package com.mcoptimizer.mod.mixin;

import com.mcoptimizer.mod.FPSBoosterMod;
import net.minecraft.client.render.entity.EntityRenderer;
import net.minecraft.entity.Entity;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Inject;
import org.spongepowered.asm.mixin.injection.callback.CallbackInfoReturnable;

@Mixin(EntityRenderer.class)
public class EntityRendererMixin<T extends Entity> {
    
    @Inject(
        method = "getSquaredDistanceToVisiblePos",
        at = @At("HEAD"),
        cancellable = true
    )
    private void modifyRenderDistance(T entity, CallbackInfoReturnable<Double> cir) {
        if (FPSBoosterMod.getInstance().getOptimizer().isAggressiveMode()) {
            cir.setReturnValue(256.0);
        }
    }
}
