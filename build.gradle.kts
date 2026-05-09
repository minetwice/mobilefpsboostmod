// MinecraftMobileOptimizer/build.gradle.kts
plugins {
    id("com.android.application") version "8.5.0" apply false
    id("fabric-loom") version "1.7-SNAPSHOT" apply false
}

allprojects {
    repositories {
        google()
        mavenCentral()
        maven("https://maven.fabricmc.net/")
    }
}
