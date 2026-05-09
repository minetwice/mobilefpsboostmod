package com.mcoptimizer.mod.mixin;

import net.minecraft.client.MinecraftClient;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Inject;
import org.spongepowered.asm.mixin.injection.callback.CallbackInfo;

@Mixin(MinecraftClient.class)
public class MinecraftMixin {

    @Inject(method = "run", at = @At("HEAD"))
    private void onRun(CallbackInfo ci) {
        System.out.println("[MC Optimizer] Minecraft client starting with optimizations");
    }

    @Inject(method = "tick", at = @At("HEAD"))
    private void onTick(CallbackInfo ci) {
        // Optional: Add per-tick optimizations if needed
    }
}
