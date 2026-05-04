package com.rampurhat.mobileboost;
import net.fabricmc.api.ClientModInitializer;
import net.fabricmc.fabric.api.client.event.lifecycle.v1.ClientTickEvents;
public class MobileBoost implements ClientModInitializer {
    public void onInitializeClient(){
        BoostAPI.autoTuneForPhone(System.getProperty("ro.product.model",""));
        BoostAPI.enableNativeMath();
        Ultra200Mode.enable200();
        ClientTickEvents.END_CLIENT_TICK.register(c -> {
            if(c.world!=null && c.player!=null && c.player.age%120==0){ AfkFix.tick(); ThermalControl.check(); }
        });
    }
}