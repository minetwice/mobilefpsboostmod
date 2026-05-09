// MinecraftMobileOptimizer/build.gradle.kts
plugins {
    id("com.android.application") version "8.3.0" apply false
    id("fabric-loom") version "1.6-SNAPSHOT" apply false
}

allprojects {
    repositories {
        google()
        mavenCentral()
        maven("https://maven.fabricmc.net/")
        maven("https://maven.minecraftforge.net/")
    }
}
