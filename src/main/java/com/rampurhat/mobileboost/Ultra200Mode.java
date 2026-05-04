package com.rampurhat.mobileboost;
public class Ultra200Mode {
    public static void enable200(){
        BoostAPI.setRenderDistance(11);
        System.setProperty("sodium.resolution_scale","0.35");
    }
}