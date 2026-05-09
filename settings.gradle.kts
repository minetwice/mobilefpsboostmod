// MinecraftMobileOptimizer/settings.gradle.kts
pluginManagement {
    repositories {
        google()
        mavenCentral()
        gradlePluginPortal()
        maven("https://maven.fabricmc.net/")
    }
}

rootProject.name = "MinecraftMobileOptimizer"
include(":app")
include(":mod")
