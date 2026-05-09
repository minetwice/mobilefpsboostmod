// MinecraftMobileOptimizer/build.gradle.kts
plugins {
    id("com.android.application") version "8.7.0" apply false
    id("fabric-loom") version "1.9.2" apply false
}

allprojects {
    repositories {
        google()
        mavenCentral()
        maven("https://maven.fabricmc.net/")
    }
}
